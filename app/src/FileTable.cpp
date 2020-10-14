#include "FileTable.h"

FileTable::FileTable(QWidget *parent)
    : QAbstractTableModel(parent) {
}

FileTable::FileTable(QString& sPath, QWidget *parent)
    : QAbstractTableModel(parent) {
    QDir *d = new QDir(sPath);
    QFileInfoList sl = d->entryInfoList(QStringList() << "*.mp3" << "*.flac" << "*.waw" << "*.ogg");

    for (const auto& it : sl) {
      if (it.permissions() & QFileDevice::ReadOwner) {
          files.push_back(FileInfo(it.filePath()));
      }
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

 bool FileTable::setData(const QModelIndex &index, const QVariant &value, int role)
 {
     if (index.isValid() && role == Qt::EditRole) {
         const int row = index.row();
         auto file = files.value(row);

         switch (index.column()) {
             case 0:
                 file.setArtist(value.toString());
                 break;
             case 1:
                 file.setTitle(value.toString());
                 break;
             case 2:
                 file.setAlbum(value.toString());
                 break;
             case 3:
                 file.setGenre(value.toString());
                 break;
             default:
                 return false;
         }
         emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
         return true;
     }
     return false;
 }

 Qt::ItemFlags FileTable::flags(const QModelIndex &index) const {
     if (!index.isValid())
         return Qt::ItemIsEnabled;

     return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
 }
