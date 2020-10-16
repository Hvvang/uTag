#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "errordialog.h"
#include "FileTable.h"
#include <QFileDialog>
#include "CommandEdit.h"

MainWindow::MainWindow(QString sPath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dirmodel(new QFileSystemModel)
    , proxyModel(new QSortFilterProxyModel)
    , undoStack(new QUndoStack) {
    ui->setupUi(this);
    QPixmap pix(defaultCoverImage);

    ui->Lyrics->installEventFilter(this);
    ui->coverImage->installEventFilter(this);
    ui->tableView->installEventFilter(this);
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
    ui->Lyrics->clear();
    ui->Lyrics->setFocusPolicy(Qt::NoFocus);
    ui->coverImage->setEnabled(false);
    ui_coverImageUpdate(QPixmap(defaultCoverImage));
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    auto selection = ui->tableView->selectionModel()->selectedRows();
    ui->treeView->hide();
    ui->Lyrics->hide();
    if (!selection.empty()) {
        QModelIndex fPath = ui->tableView->model()->index(selection.last().row(), 4, QModelIndex());
        QString sPath = ui->tableView->model()->data(fPath).toString();
        FileInfo file((FileInfo(sPath)));
        QPixmap pix = file.getCover();

        ui->Lyrics->setPlainText(file.getLyrics());
        ui_coverImageUpdate(pix);
        ui->Lyrics->setFocusPolicy(Qt::StrongFocus);
        ui->coverImage->setEnabled(true);
    } else {
        ui->Lyrics->clear();
        ui->Lyrics->setFocusPolicy(Qt::NoFocus);
        ui->coverImage->setEnabled(false);
        ui_coverImageUpdate(QPixmap(defaultCoverImage));
    }
}

void MainWindow::ui_fileBrowserUpdate(QString sPath) {
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->index(sPath));
    for (int i = 1; i < dirmodel->columnCount(); ++i)
        ui->treeView->hideColumn(i);
}

void MainWindow::ui_tagsTableUpdate(QString sPath) {
    FileTable *tablemodel = new FileTable(undoStack, sPath);
    proxyModel->setSourceModel(tablemodel);
    ui->tableView->setModel(proxyModel);
}

void MainWindow::ui_coverImageUpdate(QPixmap pix) {
    QPalette palette;
    if (pix.isNull()) {
       pix = QPixmap(defaultCoverImage);
    }
    palette.setBrush(ui->coverImage->backgroundRole(), QBrush(pix.scaled(ui->coverImage->width(), ui->coverImage->height(), Qt::KeepAspectRatio)));
    ui->coverImage->setFlat(true);
    ui->coverImage->setAutoFillBackground(true);
    ui->coverImage->setPalette(palette);
}

void MainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    QAction *saveAct = new QAction(tr("&Save"), this);
    fileMenu->addAction(saveAct);
    // connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    QAction *undoAct = undoStack->createUndoAction(this, tr("&Undo"));
    undoAct->setShortcuts(QKeySequence::Undo);
    editMenu->addAction(undoAct);
    // connect(undoAct, &QAction::triggered, this, &MainWindow::undoFile);

    QAction *redoAct = undoStack->createRedoAction(this, tr("&Redo"));
    redoAct->setShortcuts(QKeySequence::Redo);
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

void MainWindow::openFile() {
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "~/Desktop",
                                                        QFileDialog::ShowDirsOnly |
                                                        QFileDialog::DontResolveSymlinks);
    QPixmap pix(defaultCoverImage);
    ui_fileBrowserUpdate(dirName);
    ui_tagsTableUpdate(dirName);
    ui_coverImageUpdate(pix);
}

// Handler for mouse pressed on button that stores audio album cover image,
// that allow user to change it
// *using QFileDialog user get path to image file
// *than change cover using method from FileInfo class
// *than convert image to QPixmap and update ui.
void MainWindow::on_coverImage_clicked() {
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (selection.count()) {
        QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "~/Desktop",
                                                         tr("Images (*.png *.xpm *.jpg *.jpeg)"));

        QPixmap pix;
        // Multiple rows can be selected
        for(int i = 0; i < selection.count() && !imagePath.isEmpty(); ++i) {
            QModelIndex index = selection.at(i);
            QModelIndex fPath = ui->tableView->model()->index(index.row(), 4, QModelIndex());
            QString sPath = ui->tableView->model()->data(fPath).toString();
            FileInfo file((FileInfo(sPath)));

            file.setCover(imagePath);
            if (!pix) {
                pix = file.getCover();
                ui_coverImageUpdate(pix);
            }
        }
    }
}

void MainWindow::lyricsUpdate() {
     auto currRow = ui->tableView->currentIndex().row();
     if (currRow != -1) {
         auto index = ui->tableView->model()->index(currRow, 4);
         QString fPath = ui->tableView->model()->data(index).toString();
         FileInfo *file = new FileInfo(fPath);
         QString prevValue = file->getLyrics();
         QString nextValue = ui->Lyrics->toPlainText();

         file->setLyrics(nextValue);

         undoStack->push(new LyricsEdit(ui->Lyrics, ui->tableView, file, prevValue, nextValue));
     }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->Lyrics) {
//        qDebug() << event->type();

        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Escape) {

                lyricsUpdate();
//                ui->tableView->setFocus();
                return true;
            }
        }

        if (event->type() == QEvent::FocusOut) {
//            lyricsUpdate();
//            ui->tableView->setFocus();
        }

    }
    if (object == ui->tableView) {
//        qDebug() << event->type();
//        if (event->type() == QEvent::FocusOut) {
//            lyricsUpdate();
//            ui->tableView->setFocus();
//        }

    }
    return false;
}
