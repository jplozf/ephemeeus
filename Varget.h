#ifndef VARGET_H
#define VARGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QVariant>
#include <QWidget>
#include "MainWindow.h"
#include "Meeus.h"
#include "app.h"
#include "ui_MainWindow.h"

class Varboard;
class MainWindow;

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
    int SaveFile(QString name);
    int LoadFile(QString name, Meeus *m);
    void Clear();
    MainWindow *mw;

private slots:

private:
    App *a;
    Ui::MainWindow *ui;
};

#endif // VARGET_H
