#include "Preferences.h"
#include "ui_Preferences.h"

Preferences::Preferences(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Preferences) {
    ui->setupUi(this);
    readSettings();
}

Preferences::~Preferences() {
   delete ui;
}

void Preferences::writeSettings() {
    settings = new QSettings("Moose Soft", "Clipper");

    settings->beginGroup("MainWindow");
    settings->setValue("showBrowser", ui->browserSetting->currentIndex());
    settings->setValue("showCover", ui->coverSetting->currentIndex());
    settings->setValue("showLyrics", ui->LyricsSetting->currentIndex());
    settings->endGroup();
}

void Preferences::readSettings() {
    QSettings settings("Moose Soft", "Clipper");

    settings.beginGroup("MainWindow");
    ui->browserSetting->setCurrentIndex(settings.value("showBrowser").toInt());
    ui->coverSetting->setCurrentIndex(settings.value("showCover").toInt());
    ui->LyricsSetting->setCurrentIndex(settings.value("showLyrics").toInt());
    settings.endGroup();
}

void Preferences::reject() {
    QDialog::reject();
}

void Preferences::accept() {
    writeSettings();
    QDialog::accept();
}
