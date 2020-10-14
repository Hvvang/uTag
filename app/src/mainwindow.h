#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>

#include "FileInfo.h"
#include <QPixmap>
#include <QAction>
#include <QMenuBar>

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QString sPath = "/", QWidget *parent = nullptr);
    ~MainWindow();

private:
    void ui_fileBrowserUpdate(QString sPath);
    void ui_tagsTableUpdate(QString sPath);
    void ui_coverImageUpdate(QPixmap pix);
    void createMenus();
    void openFile();

signals:
    void itemChanged(const QModelIndex &index);

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_tableView_clicked(const QModelIndex &index);
//    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QSortFilterProxyModel *proxyModel;

};
#endif // MAINWINDOW_H
