#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QSysInfo>
#include <any>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils.h"

class Constants
{
public:
    Constants();
    int getInt(QString param);
    bool getBool(QString param);
    QString getQString(QString param);
    QString aboutText;
    QString consoleText;
    QMap<QString, QVariant> constants;
    QMap<QString, QStringList> theme;

private:
    QString setAbout();
    QString setConsole();
};

#endif // CONSTANTS_H
