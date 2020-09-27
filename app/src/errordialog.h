#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QVariant>

QT_BEGIN_NAMESPACE
namespace Ui { class ErrorDialog; }
QT_END_NAMESPACE


class ErrorDialog : public QDialog {
    Q_OBJECT

public:
    ErrorDialog(QWidget *parent = nullptr);
    ~ErrorDialog();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
