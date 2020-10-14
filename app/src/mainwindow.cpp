#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "errordialog.h"
#include "FileTable.h"

MainWindow::MainWindow(QString sPath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dirmodel(new QFileSystemModel)
    , proxyModel(new QSortFilterProxyModel) {
    ui->setupUi(this);
    QPixmap pix(defaultCoverImage);

    createMenus();
    ui_fileBrowserUpdate(sPath);
    ui_tagsTableUpdate(sPath);
    ui_coverImageUpdate(pix);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index) {
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui_tagsTableUpdate(sPath);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    // QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    //
    // // Multiple rows can be selected
    // for(int i=0; i< selection.count(); i++) {
    //     QModelIndex index = selection.at(i);
    //     qDebug() << index.row();
    // }

    QModelIndex fPath = ui->tableView->model()->index(index.row(), 4, QModelIndex());

    QString sPath = ui->tableView->model()->data(fPath).toString();
    FileInfo file((FileInfo(sPath)));
    QPixmap pix = file.getCover();

    ui_coverImageUpdate(pix);
}

// void MainWindow::on_tableView_doubleClicked(const QModelIndex &index) {
    // openPersistentEditor(index);
    // qDebug() << index;
    // std::cout << "1" << std::endl;
// }

void MainWindow::ui_fileBrowserUpdate(QString sPath) {
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->index(sPath));
    for (int i = 1; i < dirmodel->columnCount(); ++i)
        ui->treeView->hideColumn(i);
}

void MainWindow::ui_tagsTableUpdate(QString sPath) {
    FileTable *tablemodel = new FileTable(sPath);
    proxyModel->setSourceModel(tablemodel);
    ui->tableView->setModel(proxyModel);
}

void MainWindow::ui_coverImageUpdate(QPixmap pix) {
    QPalette palette;
    palette.setBrush(ui->coverImage->backgroundRole(), QBrush(pix.scaled(ui->coverImage->width(), ui->coverImage->height(), Qt::KeepAspectRatio)));

    ui->coverImage->setFlat(true);
    ui->coverImage->setAutoFillBackground(true);
    ui->coverImage->setPalette(palette);
}

void MainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    // connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    QAction *saveAct = new QAction(tr("&Save"), this);
    fileMenu->addAction(saveAct);
    // connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    QAction *undoAct = new QAction(tr("&Undo"), this);
    editMenu->addAction(undoAct);
    // connect(undoAct, &QAction::triggered, this, &MainWindow::undoFile);

    QAction *redoAct = new QAction(tr("&Redo"), this);
    editMenu->addAction(redoAct);
    // connect(redoAct, &QAction::triggered, this, &MainWindow::redoFile);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAct = new QAction(tr("&About"), this);
    helpMenu->addAction(aboutAct);
    // connect(aboutAct, &QAction::triggered, this, &MainWindow::aboutFile);

    QAction *termsAct = new QAction(tr("&Terms of use"), this);
    helpMenu->addAction(termsAct);
    // connect(termsAct, &QAction::triggered, this, &MainWindow::termsFile);

    helpMenu->addSeparator();

    QAction *guideAct = new QAction(tr("&Guide"), this);
    helpMenu->addAction(guideAct);
    // connect(guideAct, &QAction::triggered, this, &MainWindow::guideFile);
}
