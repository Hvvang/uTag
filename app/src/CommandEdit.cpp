#include "CommandEdit.h"

CommandEdit::CommandEdit(FileTable *model, const QModelIndex &index, const QVariant &prev,
                         const QVariant &next, QUndoCommand *parent)
    : QUndoCommand(parent)
    , index(index)
    , prev(prev)
    , next(next) {
    this->model = model;
}

void CommandEdit::undo() {
    this->model->setData(index, prev);
}

void CommandEdit::redo() {
    this->model->redoData(index, next);
}
