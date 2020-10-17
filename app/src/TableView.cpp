#include "TableView.h"
#include "FileTable.h"


TableView::TableView(QWidget *parent) :
    QTableView(parent) {}

void TableView::commitData(QWidget *editor) {
    QAbstractItemView::commitData(editor);
    auto value = this->model()->data(this->currentIndex(), Qt::EditRole);

    auto currCol = this->currentIndex().column();
    auto currRow = this->currentIndex().row();

    if (QFileInfo(model()->data(model()->index(this->currentIndex().row(), 4)).toString()).isWritable()) {
        QModelIndexList selection = this->selectionModel()->selectedRows();
        for(int i = 0; i < selection.count(); ++i) {
            auto row = selection.at(i).row();
            if (row != currRow) {
                QModelIndex idx = model()->index(row, currCol);
                if (QFileInfo(model()->data(model()->index(row, 4)).toString()).isWritable())
                    this->model()->setData(idx, value, Qt::EditRole);
            }
        }
    }
}

