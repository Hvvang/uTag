#include "mainwindow.h"
#include <QApplication>
#include "errordialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./tag.png"));
    if (!QDir(argv[1]).exists() && argv[1]) {
        ErrorDialog error("Invalid folder path");
    } else {
        MainWindow w((QString(argv[1])));
        w.show();
        return a.exec();
    }
}
