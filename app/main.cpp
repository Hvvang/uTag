#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./tag.png"));
    MainWindow w((QString(argv[1])));
    w.show();
    return a.exec();
}
