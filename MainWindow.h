#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QClipboard>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QFile>
#include <QGuiApplication>
#include <QHash>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QSettings>
#include <QShortcut>
#include <QTimer>

#include "app.h"
#include "qobjectdefs.h"
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *a, QWidget *parent = nullptr);
    ~MainWindow();
    App *app;
    void closeEvent(QCloseEvent *);
    void saveSettings();
    void readSettings();
    void initUI();
    Ui::MainWindow *ui;
    void setTheme();

private:
    QApplication *a;
    void showMessage(const QString &message, int timeout = -1);

private slots:
    void slotDoExit();
};
#endif // MAINWINDOW_H
