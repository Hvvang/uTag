#include "TableView.h"
#include "FileTable.h"


TableView::TableView(QWidget *parent) :
    QTableView(parent) { }

void TableView::commitData(QWidget *editor) {
    QAbstractItemView::commitData(editor);
    auto value = this->model()->data(this->currentIndex(), Qt::EditRole);

    auto currCol = this->currentIndex().column();
    auto currRow = this->currentIndex().row();

    QModelIndexList selection = this->selectionModel()->selectedRows();

    for(int i = 0; i < selection.count(); ++i) {
        auto row = selection.at(i).row();
        if (row != currRow) {
            QModelIndex idx = model()->index(row, currCol);
            this->model()->setData(idx, value, Qt::EditRole);
        }
    }
}
