#include "CommandEdit.h"

TableEdit::TableEdit(FileTable *model, const QModelIndex &index, const QVariant &prev,
                         const QVariant &next, QUndoCommand *parent)
    : QUndoCommand(parent)
    , index(index)
    , prev(prev)
    , next(next) {
    this->model = model;
}

void TableEdit::undo() {
    this->model->setData(index, prev);
}

void TableEdit::redo() {
    this->model->redoData(index, next);
}

LyricsEdit::LyricsEdit(QPlainTextEdit *widget, QTableView *table, FileInfo *file,
                       const QString &prev, const QString &next, QUndoCommand *parent)
    : QUndoCommand(parent)
    , index(table->currentIndex())
    , prev(prev)
    , next(next) {
    this->widget = widget;
    this->table = table;
    this->model = table->model();
    this->file = file;
}

void LyricsEdit::undo() {
    if (index.row() == table->currentIndex().row() && model == table->model()) {
        widget->setPlainText(prev);
    }
    file->setLyrics(prev);
}

void LyricsEdit::redo() {
    if (index.row() == table->currentIndex().row() && model == table->model()) {
        widget->setPlainText(prev);
    }
    file->setLyrics(next);
}
