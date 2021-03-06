#include "FileTable.h"
#include "CommandEdit.h"
#include "errordialog.h"

FileTable::FileTable(QWidget *parent)
    : QAbstractTableModel(parent) {
}

FileTable::FileTable(QUndoStack *undoStack, QString& sPath, QWidget *parent)
    : QAbstractTableModel(parent) {
    this->undoStack = undoStack;
    QDir *d = new QDir(sPath);
    QFileInfoList sl = d->entryInfoList(QStringList() << "*.mp3" << "*.flac" << "*.waw" << "*.ogg" << "*.ape");

    for (const auto& it : sl) {
        files.push_back(FileInfo(it.filePath(), it.isReadable()));
    }
}

int FileTable::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : files.size();
}

int FileTable::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 5;
}

QVariant FileTable::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= files.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const auto &file = files.at(index.row());

        if (!file.isValid()) {
            if (index.column() != 4)
                return "-";
        }
        switch (index.column()) {
            case 0:
                return file.getArtist();
            case 1:
                return file.getTitle();
            case 2:
                return file.getAlbum();
            case 3:
                return file.getGenre();
            case 4:
                return file.getFilePath();
            default:
                break;
        }
    }
    return QVariant();
}

FileInfo *FileTable::fileData(const QModelIndex &index) {
    const int row = index.row();
    const auto path = this->data(this->index(row, 4), Qt::DisplayRole).toString();
    return new FileInfo(path);
}

QVariant FileTable::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Artist");
            case 1:
                return tr("Title");
            case 2:
                return tr("Album");
            case 3:
                return tr("Genre");
            case 4:
                return tr("Path");
            default:
                break;
        }
    }
    return QVariant();
}

bool FileTable::setData(const QModelIndex &index, const QVariant &value, int role) {
     if (index.isValid() && role == Qt::EditRole) {
         const int row = index.row();
         auto file = files.value(row);
         QVariant prevValue;

         if (QFileInfo(file.getFilePath()).isWritable()) {
             switch (index.column()) {
                 case 0:
                     prevValue = QVariant(file.getArtist());
                     file.setArtist(value.toString());
                     break;
                 case 1:
                     prevValue = QVariant(file.getTitle());
                     file.setTitle(value.toString());
                     break;
                 case 2:
                     prevValue = QVariant(file.getAlbum());
                     file.setAlbum(value.toString());
                     break;
                 case 3:
                     prevValue = QVariant(file.getGenre());
                     file.setGenre(value.toString());
                     break;
                 default:
                     return false;
             }
             if (prevValue != value)
                this->undoStack->push(new TableEdit(this, index, prevValue, value));
             emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
         } else {
             ErrorDialog dialog("Not enough permission!");
          }

         return true;
     }
     return false;
 }

bool FileTable::redoData(const QModelIndex &index, const QVariant &value, int role) {
     if (index.isValid() && role == Qt::EditRole) {
         const int row = index.row();
         auto file = files.value(row);
         QVariant prevValue;

         if (QFileInfo(file.getFilePath()).isWritable()) {
             switch (index.column()) {
                 case 0:
                     prevValue = QVariant(file.getArtist());
                     file.setArtist(value.toString());
                     break;
                 case 1:
                     prevValue = QVariant(file.getTitle());
                     file.setTitle(value.toString());
                     break;
                 case 2:
                     prevValue = QVariant(file.getAlbum());
                     file.setAlbum(value.toString());
                     break;
                 case 3:
                     prevValue = QVariant(file.getGenre());
                     file.setGenre(value.toString());
                     break;
                 default:
                     return false;
             }
             emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
         } else {
             ErrorDialog dialog("Not enough permission!");
         }
         return true;
     }
     return false;
 }

Qt::ItemFlags FileTable::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    if (index.column() == 4)
        return QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
