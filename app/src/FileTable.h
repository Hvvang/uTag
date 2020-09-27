#ifndef FILETABLE_H
#define FILETABLE_H

#include <QTableView>
#include <QtCore>
#include <QAbstractTableModel>
#include <QVector>
#include "FileInfo.h"

class FileTable : public QAbstractTableModel {
    Q_OBJECT

public:
    FileTable(QWidget *parent = nullptr);
    FileTable(QString& sPath, QWidget *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    // bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
private:
    QVector<FileInfo> files;
};

#endif // FILETABLE_H
