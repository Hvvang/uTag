#include "errordialog.h"
 #include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent)
    : ui(new Ui::ErrorDialog) {
    ui->setupUi(this);
    QPixmap pix("/Users/huanghe/Desktop/uTag/error.png");
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(pix);
}

ErrorDialog::~ErrorDialog() {
   delete ui;
}
