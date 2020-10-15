#ifndef FILETABLE_H
#define FILETABLE_H

#include <QTableView>
#include <QtCore>
#include <QAbstractTableModel>
#include <QVector>
#include "FileInfo.h"
#include <QUndoStack>


class FileTable : public QAbstractTableModel {
    Q_OBJECT

public:
    FileTable(QWidget *parent = nullptr);
    FileTable(QUndoStack *undoStack, QString& sPath, QWidget *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool redoData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QVector<FileInfo> files;
public:
    QUndoStack *undoStack;
};

#endif // FILETABLE_H
