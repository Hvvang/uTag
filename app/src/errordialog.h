#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

class ErrorDialog : public QMessageBox {
    Q_OBJECT
public:
    ErrorDialog(const char *message, QWidget *parent = nullptr);
};

#endif // ERRORDIALOG_H
