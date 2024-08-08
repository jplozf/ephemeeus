#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QCryptographicHash>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QSaveFile>
#include <QString>
#include <QUrl>
#include <QUuid>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class Downloader
{
public:
    static void downloadFile(const QString &url, const QString &target);
    static QList<QStringList> getFilesFromIndex(const QString &url);
    static QString getMD5FromLocalFile(const QString &file);
    static bool isFileModified(const QString &file);
};

#endif // DOWNLOADER_H
