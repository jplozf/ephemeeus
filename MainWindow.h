#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QClipboard>
#include <QCloseEvent>
#include <QCompleter>
#include <QDesktopWidget>
#include <QFile>
#include <QGuiApplication>
#include <QHash>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QSettings>
#include <QShortcut>
#include <QSpacerItem>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTimer>

#include "Meeus.h"
#include "Varget.h"
#include "app.h"
#include "downloader.h"
#include "qobjectdefs.h"
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QApplication* a, QWidget* parent = nullptr);
  ~MainWindow();
  App* app;
  void closeEvent(QCloseEvent*);
  void saveSettings();
  void readSettings();
  void initUI();
  Ui::MainWindow* ui;
  void setTheme();

 private:
  QApplication* a;
  void showMessage(const QString& message, int timeout = -1);
  void out(QString txt);
  void refresh();
  Meeus* meeus;
  QSqlDatabase db;
  Varboard *vb;

  private slots:
  void slotDoExit();
  void on_actionRefresh_triggered();
  void on_btnClearConsole_clicked();
  void on_btnRefresh_clicked();
  void on_txtLocation_editingFinished();
};
#endif  // MAINWINDOW_H
