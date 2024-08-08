#ifndef APP_H
#define APP_H

#include <QString>
#include "constants.h"
#include "downloader.h"
#include "settings.h"
#include "utils.h"

class App
{
public:
    App();
    QString appDir;
    QString docDir;
    Settings *appSettings;
    Constants *appConstants;
    QVector<QString> mruProjects;
    bool processRunning;
};

#endif // APP_H
