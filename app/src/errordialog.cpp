#include "errordialog.h"

ErrorDialog::ErrorDialog(const char *message, QWidget *parent) {
    QMessageBox::warning(parent, tr("Error"),
            tr(message), QMessageBox::Ok);

}
