#include "Varget.h"

QMap<QString, callback_function> Varboard::aFunc = {{"VarDateTime", &Meeus::VarDateTime},
                                                    {"VarJD", &Meeus::VarJD},
                                                    {"VarLocation", &Meeus::VarLocation}};

//******************************************************************************
// Varget()
//******************************************************************************
Varget::Varget(App *a, int Order, QString Label, Meeus *m, QString Function, QWidget *parent)
    : QWidget{parent}
{
    this->Order = Order;
    this->Label = Label;
    this->Function = Function;
    this->m = m;
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);
    QString o = QString::asprintf("%05d", Order);
    QLabel *ord = new QLabel(o);
    QLabel *lbl = new QLabel(Label + " ");
    QFont *f = new QFont();
    f->setBold(true);
    lbl->setFont(*f);
    lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    hbox->addWidget(ord);
    hbox->addWidget(lbl);

    txtValue = new QLineEdit();
    txtValue->setReadOnly(true);
    txtValue->setStyleSheet("background-color : #ffffff; color : black; border: 2px solid grey;");
    txtValue->setFixedWidth(lbl->frameGeometry().width() / 2);
    hbox->addWidget(txtValue);

    /*
    QPushButton *b1 = new QPushButton();
    b1->setText("");
    b1->setIcon(QIcon(":/16x16/Trash.png"));
    b1->setFixedWidth(40);
    b1->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    hbox->addWidget(b1);
    */

    this->setLayout(hbox);
    if (Order % 2 == 0) {
        this->css = "background-color : " + a->appSettings->get("VARGET_COLOR_LINE_1").toString()
                    + "; color : black;";
    } else {
        this->css = "background-color : " + a->appSettings->get("VARGET_COLOR_LINE_2").toString()
                    + "; color : black;";
    }
    this->setStyleSheet(this->css);

    this->Refresh();
}

//******************************************************************************
// Refresh()
//******************************************************************************
void Varget::Refresh()
{
    this->compute();
    this->txtValue->setText(this->Value);
}

//******************************************************************************
// compute()
//******************************************************************************
void Varget::compute()
{
    callback_function pFunc;
    pFunc = Varboard::aFunc[this->Function];
    this->Value = (m->*pFunc)();
}

//******************************************************************************
// Varboard()
//******************************************************************************
Varboard::Varboard(App *a, Ui::MainWindow *ui)
{
    this->a = a;
    this->ui = ui;
}

//******************************************************************************
// addVarget()
//******************************************************************************
int Varboard::addVarget(QString Label, Meeus *m, QString Function, QWidget *parent)
{
    int i = this->vargets.count() + 1;
    Varget *v = new Varget(this->a, i, Label, m, Function, parent);
    this->vargets.append(v);
    this->ui->boardLayout->addWidget(v);
    return i;
}

//******************************************************************************
// pack()
//******************************************************************************
void Varboard::pack()
{
    this->ui->boardLayout->addItem(
        new QSpacerItem(0, 1000, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

//******************************************************************************
// Refresh()
//******************************************************************************
void Varboard::Refresh()
{
    for (int i = 0; i < this->vargets.size(); ++i)
        this->vargets[i]->Refresh();
}

//******************************************************************************
// SaveFile()
//******************************************************************************
int Varboard::SaveFile(QString name)
{
    int rc = 0;
    QFile file(name);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);
        for (int i = 0; i < this->vargets.size(); ++i) {
            stream << "\"" + this->vargets[i]->Label + "\"" << ","
                   << "\"" + this->vargets[i]->Function + "\"" << "\n";
        }
        file.close();
    } else {
        rc = 1;
    }
    return rc;
}

//******************************************************************************
// LoadFile()
//******************************************************************************
int Varboard::LoadFile(QString name, Meeus *m)
{
    int rc = 0;
    QFile file(name);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        this->Clear();
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList list = line.split(",");
            this->addVarget(list[0].mid(1, list[0].size() - 2),
                            m,
                            list[1].mid(1, list[1].size() - 2));
        }
        this->pack();
        file.close();
    } else {
        rc = 1;
    }
    return rc;
}

//******************************************************************************
// Clear()
//******************************************************************************
void Varboard::Clear()
{
    QLayoutItem *item;
    while ((item = ui->boardLayout->takeAt(0)) != NULL) {
        delete item->widget();
        delete item;
    }
    while (this->vargets.count()) {
        delete this->vargets.takeLast();
    }
}
