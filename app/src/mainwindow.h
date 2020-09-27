#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <QStringList>
#include <QVariant>

#include "FileInfo.h"
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QString sPath = "/", QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);
    // void on_listView_clicked(const QModelIndex &index);

    void updateTags(FileInfo file);

private:
    std::map<std::string, FileInfo> files;
    FileInfo *f;
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;

};
#endif // MAINWINDOW_H
