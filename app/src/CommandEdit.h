#ifndef COMMANDEDIT_H
#define COMMANDEDIT_H

#include <QUndoCommand>
#include <QTableView>
#include <QVariant>
#include "FileTable.h"

class CommandEdit : public QUndoCommand {
public:
    CommandEdit(FileTable *model, const QModelIndex &index, const QVariant &prev,
                const QVariant &next, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    QModelIndex index;
    FileTable *model;
    const QVariant prev;
    const QVariant next;
};
//! [0]

#endif // COMMANDEDIT_H
