#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QClipboard>
#include <QCloseEvent>
#include <QCompleter>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QFile>
#include <QFileDialog>
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

#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QTemporaryFile>
#include <QVariant>
#include <QWidget>
#include "DlgInputLocation.h"
#include "Meeus.h"
#include "app.h"
#include "downloader.h"
#include "qobjectdefs.h"
#include "ui_MainWindow.h"

class Varget;
class Varboard;

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
  QDir appDir;
  void closeEvent(QCloseEvent*);
  void saveSettings();
  void readSettings();
  void initUI();
  Ui::MainWindow* ui;
  void setTheme();
  void showMessage(const QString &message, int timeout = -1);

  private:
  QApplication* a;
  void out(QString txt);
  void refresh();
  Meeus* meeus;
  QSqlDatabase db;
  Varboard *vb;
  QString appTitle;
  QString vbdFileName;

  private slots:
  void slotDoExit();
  void on_actionRefresh_triggered();
  void on_btnClearConsole_clicked();
  void on_btnRefresh_clicked();
  void on_txtLocation_editingFinished();
  void on_actionOpen_triggered();
  void on_actionHelp_triggered();
  void on_btnAddVarget_clicked();
  void on_cbxVargets_currentIndexChanged(int index);
  void on_actionSave_triggered();
  void on_btnAddLabel_clicked();
  void on_btnAddTitle_clicked();
  void on_actionSave_as_triggered();
  void on_btnExportLog_clicked();
};

class MainWindow;
class Varboard;
// class MainWindow;

typedef QString (Meeus::*callback_function)(void);
void clearLayout(QLayout *layout);

class Varget : public QWidget
{
    Q_OBJECT
public:
    explicit Varget(App *a,
                    int Order,
                    QString Label,
                    Meeus *m,
                    QString Function,
                    Varboard *vb,
                    QWidget *parent = nullptr);
    void Refresh();
    int Order;
    QString Label;
    QString Help;
    QString Value;
    QString Function;
    Meeus *m;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QPushButton *btnDelete;
    Varboard *vb;
    QString css;
    QLabel *lblOrder;

private:
    void compute();

    callback_function pFunc;
    QLineEdit *txtValue;

private slots:
    void on_clicked_button_down();
    void on_clicked_button_up();
    void on_clicked_button_delete();

signals:
};

class Varboard
{
public:
    QVector<Varget *> vargets;
    static QMap<QString, callback_function> aFunc;
    int addVarget(QString Label, Meeus *m, QString Function, QWidget *parent = nullptr);
    void pack();
    explicit Varboard(App *a, MainWindow *mw, Ui::MainWindow *ui);
    void Refresh();
    int SaveJSON(QString name);
    int LoadJSON(QString name, Meeus *m);
    void Clear();
    MainWindow *mw;

private:
    App *a;
    Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
