#include "mainwindow.h"
#include "FileInfo.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPixmap>

MainWindow::MainWindow(QString sPath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QPixmap pix("/Users/huanghe/Desktop/uTag/default-album-artwork.png");
    int w = ui->label_7->width();
    int h = ui->label_7->height();
    ui->label_7->setPixmap(pix);

    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);

    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->index(sPath));
    for (int i = 1; i < dirmodel->columnCount(); ++i)
        ui->treeView->hideColumn(i);

    filemodel = new QFileSystemModel(this);
    filemodel->setRootPath(sPath);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setNameFilters(QStringList() << "*.mp3" << "*.flac" << "*.waw" << "*.ogg"); // "^(?:.*\/)?((.+)(\.mp3|\.flac|\.waw|\.ogg))$"
    filemodel->setNameFilterDisables(false);
    ui->listView->setModel(filemodel);
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index) {
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));

}

void MainWindow::updateTags(FileInfo file) {
    file.setArtist(ui->lineEdit_1->text().toStdString());
}

void MainWindow::on_listView_clicked(const QModelIndex &index) {
    std::string filePath = filemodel->fileInfo(index).absoluteFilePath().toStdString();
    QFile::Permissions perm = filemodel->permissions(index);

    // QDir d = filemodel->fileInfo(index).absoluteDir();
    //
    // QFileInfoList sl = d.entryInfoList(QStringList() << "*.mp3" << "*.flac" << "*.waw" << "*.ogg");
    // // std::cout << "model:" << '\n';
    // for (const auto& it : sl) {
    //     files.insert(std::pair<std::string, FileInfo>(,100));
    //     std::cout << it.toStdString() << std::endl;
    // }

    if (perm & QFileDevice::ReadOwner) {

        FileInfo file(filePath);
        file.setCover("/Users/huanghe/Desktop/data2/download.jpeg");
        ui->lineEdit_1->setText(QString::fromStdString(file.getArtist()));
        ui->lineEdit_2->setText(QString::fromStdString(file.getTitle()));
        ui->lineEdit_3->setText(QString::fromStdString(file.getAlbum()));
        ui->lineEdit_4->setText(QString::fromStdString(file.getGenre()));
        ui->lineEdit_5->setText(QString::fromStdString(file.getFilePath()));
    } else {
        std::cout << "hasn't perm : ";
        std::cout << "perm = " << perm << '\n';
    }
}
