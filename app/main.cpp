#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w((QString(argv[1])));
    w.show();
    return a.exec();
}
