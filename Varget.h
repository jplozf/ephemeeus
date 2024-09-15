#ifndef VARGET_H
#define VARGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QVariant>
#include <QWidget>
#include "Meeus.h"
#include "app.h"
#include "ui_MainWindow.h"

typedef QString (Meeus::*callback_function)(void);

class Varget : public QWidget
{
    Q_OBJECT
public:
    explicit Varget(
        App *a, int Order, QString Label, Meeus *m, QString Function, QWidget *parent = nullptr);
    void Refresh();
    int Order;
    QString Label;
    QString Help;
    QString Value;
    QString Function;
    Meeus *m;

private:
    void compute();
    QString css;
    callback_function pFunc;
    QLineEdit *txtValue;

signals:
};

class Varboard
{
public:
    QVector<Varget *> vargets;
    static QMap<QString, callback_function> aFunc;
    int addVarget(QString Label, Meeus *m, QString Function, QWidget *parent = nullptr);
    void pack();
    explicit Varboard(App *a, Ui::MainWindow *ui);
    void Refresh();
    int SaveFile(QString name);
    int LoadFile(QString name, Meeus *m);
    void Clear();

private slots:

private:
    App *a;
    Ui::MainWindow *ui;
};

#endif // VARGET_H
