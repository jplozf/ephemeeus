#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIODevice>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPair>
#include <QPushButton>
#include <QStandardPaths>
#include <QString>
#include <QVariant>
#include <QWidget>

#include "constants.h"
#include "utils.h"

class MainWindow;

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();
    QMap<QString, QVariant> defaults;
    QMap<QString, QVariant> settings;
    QVariant get(QString param);
    QPushButton *btnTemplatesCutomizing;
    void write();
    void read();
    void form(MainWindow *w);
    void handleTextChanged(MainWindow *w, QLabel *lbl, QLineEdit *txt);
};

#endif // SETTINGS_H
