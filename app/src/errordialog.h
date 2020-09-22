#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QVariant>

class ErrorDialog : public QDialog {
    Q_OBJECT

public:
    ErrorDialog(QWidget *parent = nullptr);
    ~ErrorDialog();

private:

};

#endif // ERRORDIALOG_H
