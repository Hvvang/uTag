#include "mainwindow.h"
#include "errordialog.h"
#include "FileTable.h"
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

    FileTable *tablemodel = new FileTable(sPath);
    ui->tableView->setModel(tablemodel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index) {
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    // ui->listView->setRootIndex(filemodel->setRootPath(sPath));

    FileTable *tablemodel = new FileTable(sPath);
    ui->tableView->setModel(tablemodel);
}

void MainWindow::updateTags(FileInfo file) {
    file.setArtist(ui->lineEdit_1->text());
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    // std::string filePath = filemodel->fileInfo(index).absoluteFilePath().toStdString();
    // QFile::Permissions perm = filemodel->permissions(index);

//     // QDir d = filemodel->fileInfo(index).absoluteDir();
//     //
//     // QFileInfoList sl = d.entryInfoList(QStringList() << "*.mp3" << "*.flac" << "*.waw" << "*.ogg");
//     // // std::cout << "model:" << '\n';
//     // for (const auto& it : sl) {
//     //     files.insert(std::pair<std::string, FileInfo>(,100));
//     //     std::cout << it.toStdString() << std::endl;
//     // }
//
    // if (perm & QFileDevice::ReadOwner) {

        // FileInfo file(filemodel->fileInfo(index).absoluteFilePath());
        // file.setCover("/Users/huanghe/Desktop/data2/download.jpeg");
        // ui->lineEdit_1->setText(file.getArtist());
        // ui->lineEdit_2->setText(file.getTitle());
        // ui->lineEdit_3->setText(file.getAlbum());
        // ui->lineEdit_4->setText(file.getGenre());
        // ui->lineEdit_5->setText(file.getFilePath());
    // } else {
        ErrorDialog ed(this);
        ed.exec();
    // }
}
