#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QtCore>
#include "FileTable.h"

class TableView : public QTableView {
    Q_OBJECT

public:
    TableView(QWidget *parent = nullptr);
    void commitData(QWidget *editor) override;

};

#endif // TABLEVIEW_H
