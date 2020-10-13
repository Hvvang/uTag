#include "CoverImage.h"
#include "FileInfo.h"

CoverImage::CoverImage(QString imagePath, QWidget *parent) :
    QPushButton(parent) {

    FileInfo file((FileInfo(sPath)));
    QPixmap pix = file.getCover();
    QPalette palette;
    palette.setBrush(ui->pushButton->backgroundRole(), QBrush(pix.scaled(ui->pushButton->width(), ui->pushButton->height(), Qt::KeepAspectRatio)));

    this->setAttribute(Qt::WA_HOVER, true);
    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(palette);
}

void CoverImage::enterEvent(QEvent * event) {
    qDebug() << Q_FUNC_INFO << this->objectName();
    QWidget::enterEvent(event);
}

void CoverImage::leaveEvent(QEvent * event) {
    qDebug() << Q_FUNC_INFO << this->objectName();
    QWidget::leaveEvent(event);
}
