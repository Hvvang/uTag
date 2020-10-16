#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class Preferences; }
QT_END_NAMESPACE

class Preferences : public QDialog {
    Q_OBJECT

public:
    Preferences(QWidget *parent = nullptr);
    ~Preferences();

    QSettings *getSettings() { return settings; };

    void accept() override;
    void reject() override;

private:
    void readSettings();
    void writeSettings();


private:
    Ui::Preferences *ui;
    QSettings *settings;
};

#endif // PREFERENCES_H
