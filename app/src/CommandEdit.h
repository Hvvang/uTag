#ifndef COMMANDEDIT_H
#define COMMANDEDIT_H

#include <QUndoCommand>
#include <QTableView>
#include <QVariant>
#include "FileTable.h"
#include "FileInfo.h"
#include <QPlainTextEdit>
#include <QPushButton>
#include "mainwindow.h"

class TableEdit : public QUndoCommand {
public:
    TableEdit(FileTable *model, const QModelIndex &index, const QVariant &prev,
                const QVariant &next, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    QModelIndex index;
    FileTable *model;
    const QVariant prev;
    const QVariant next;
};

class LyricsEdit : public QUndoCommand {
public:
    LyricsEdit(QPlainTextEdit *widget, QTableView *table, FileInfo *file,
               const QString &prev, const QString &next, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    QModelIndex index;
    QAbstractItemModel *model;
    QTableView *table;
    FileInfo *file;
    QPlainTextEdit *widget;
    const QString prev;
    const QString next;
};

#endif // COMMANDEDIT_H
