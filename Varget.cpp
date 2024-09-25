#include "Varget.h"

QMap<QString, callback_function> Varboard::aFunc = {{"VarDateTime", &Meeus::VarDateTime},
                                                    {"VarJD", &Meeus::VarJD},
                                                    {"VarLatitude", &Meeus::VarLatitude},
                                                    {"VarLongitude", &Meeus::VarLongitude},
                                                    {"VarLocation", &Meeus::VarLocation}};

//******************************************************************************
// Varget()
//******************************************************************************
Varget::Varget(
    App *a, int Order, QString Label, Meeus *m, QString Function, Varboard *vb, QWidget *parent)
    : QWidget{parent}
{
    this->Order = Order;
    this->Label = Label;
    this->Function = Function;
    this->m = m;
    this->vb = vb;
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);
    QString o = QString::asprintf("%05d", Order);
    this->lblOrder = new QLabel(o);
    QLabel *lbl = new QLabel(Label + " ");
    QFont *f = new QFont();
    f->setBold(true);
    lbl->setFont(*f);
    lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    hbox->addWidget(this->lblOrder);
    hbox->addWidget(lbl);

    txtValue = new QLineEdit();
    txtValue->setReadOnly(true);
    txtValue->setStyleSheet("background-color : #f5f5f4; color : black; border: 2px solid grey;");
    txtValue->setFixedWidth(this->lblOrder->frameGeometry().width() / 2);
    hbox->addWidget(txtValue);

    this->btnDelete = new QPushButton(
        this); // parent is specified to this, because we need to know the parent when clicked
    QPixmap pixmap1(":/16x16/Trash.png");
    QIcon ButtonIcon1(pixmap1);
    this->btnDelete->setFlat(true);
    this->btnDelete->setIcon(ButtonIcon1);
    this->btnDelete->setIconSize(pixmap1.rect().size());
    this->btnDelete->setFixedSize(QSize(18, 18));
    connect(this->btnDelete, SIGNAL(clicked()), this, SLOT(on_clicked_button_delete()));
    hbox->addWidget(this->btnDelete);

    this->btnUp = new QPushButton(
        this); // parent is specified to this, because we need to know the parent when clicked
    QPixmap pixmap2(":/16x16/Arrow2 - Up.png");
    QIcon ButtonIcon2(pixmap2);
    this->btnUp->setFlat(true);
    this->btnUp->setIcon(ButtonIcon2);
    this->btnUp->setIconSize(pixmap2.rect().size());
    this->btnUp->setFixedSize(QSize(18, 18));
    connect(this->btnUp, SIGNAL(clicked()), this, SLOT(on_clicked_button_up()));
    hbox->addWidget(this->btnUp);

    this->btnDown = new QPushButton(
        this); // parent is specified to this, because we need to know the parent when clicked
    QPixmap pixmap3(":/16x16/Arrow2 - Down.png");
    QIcon ButtonIcon3(pixmap3);
    this->btnDown->setFlat(true);
    this->btnDown->setIcon(ButtonIcon3);
    this->btnDown->setIconSize(pixmap3.rect().size());
    this->btnDown->setFixedSize(QSize(18, 18));
    connect(this->btnDown, SIGNAL(clicked()), this, SLOT(on_clicked_button_down()));
    hbox->addWidget(this->btnDown);

    this->setLayout(hbox);
    this->Refresh();
}

//******************************************************************************
// Refresh()
//******************************************************************************
void Varget::Refresh()
{
    this->compute();
    QString o = QString::asprintf("%05d", this->Order);
    this->lblOrder->setText(o);
    this->txtValue->setText(this->Value);
    qDebug() << "REFRESH VARGET #" + o;
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
// on_clicked_button_down()
//******************************************************************************
void Varget::on_clicked_button_down()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    Varget *vg = (Varget *) btn->parent();
    int current = vg->Order - 1;
    qDebug() << ("Clicked DOWN #" + QString::number(current));
    Varboard *vb = vg->vb;

    vb->vargets[current]->Order = vb->vargets[current]->Order + 1;
    vb->vargets[current + 1]->Order = vb->vargets[current + 1]->Order - 1;
    std::swap(vb->vargets[current], vb->vargets[current + 1]);

    vb->Refresh();
}

//******************************************************************************
// on_clicked_button_up()
//******************************************************************************
void Varget::on_clicked_button_up()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    Varget *vg = (Varget *) btn->parent();
    int current = vg->Order - 1;
    qDebug() << ("Clicked UP #" + QString::number(current));
    Varboard *vb = vg->vb;

    vb->vargets[current]->Order = vb->vargets[current]->Order - 1;
    vb->vargets[current - 1]->Order = vb->vargets[current - 1]->Order + 1;
    std::swap(vb->vargets[current], vb->vargets[current - 1]);

    vb->Refresh();
}

//******************************************************************************
// on_clicked_button_delete()
//******************************************************************************
void Varget::on_clicked_button_delete()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    Varget *vg = (Varget *) btn->parent();
    int current = vg->Order - 1;
    qDebug() << ("Clicked DELETE #" + QString::number(current));

    Varboard *vb = vg->vb;
    vb->mw->showMessage("Deleting Varget #" + QString::number(current));

    for (int i = current + 1; i < vb->vargets.size(); ++i) {
        vb->vargets[i]->Order = vb->vargets[i]->Order - 1;
    }
    vb->vargets.removeAt(current);

    vb->Refresh();
}

//******************************************************************************
// Varboard()
//******************************************************************************
Varboard::Varboard(App *a, MainWindow *mw, Ui::MainWindow *ui)
{
    this->a = a;
    this->ui = ui;
    this->mw = mw;
}

//******************************************************************************
// addVarget()
//******************************************************************************
int Varboard::addVarget(QString Label, Meeus *m, QString Function, QWidget *parent)
{
    int i = this->vargets.count() + 1;
    Varget *v = new Varget(this->a, i, Label, m, Function, this, parent);
    this->vargets.append(v);
    return i;
}

//******************************************************************************
// pack()
//******************************************************************************
void Varboard::pack()
{
    // Remove any previous QSpacerItem
    for (int i = 0; i < ui->boardLayout->count(); ++i) {
        QLayoutItem *layoutItem = ui->boardLayout->itemAt(i);
        if (layoutItem->spacerItem()) {
            ui->boardLayout->removeItem(layoutItem);
            delete layoutItem;
            --i;
        }
    }
    // Finally, add the QSpacerItem to pack (Shakur...)
    this->ui->boardLayout->addItem(
        new QSpacerItem(0, 1000, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

//******************************************************************************
// Refresh()
//******************************************************************************
void Varboard::Refresh()
{
    qDebug() << this->vargets.size();
    for (int i = 0; i < this->vargets.size(); ++i) {
        this->ui->boardLayout->addWidget(vargets[i]);
        if (i % 2 == 0) {
            this->vargets[i]->css = "background-color : "
                                    + a->appSettings->get("VARGET_COLOR_LINE_1").toString()
                                    + "; color : black;";
        } else {
            this->vargets[i]->css = "background-color : "
                                    + a->appSettings->get("VARGET_COLOR_LINE_2").toString()
                                    + "; color : black;";
        }
        this->vargets[i]->btnUp->setEnabled(true);
        this->vargets[i]->btnDown->setEnabled(true);
        this->vargets[i]->setStyleSheet(this->vargets[i]->css);
        this->vargets[i]->Refresh();
    }
    this->pack();
    // Disable the first UP button and the last DOWN button
    this->vargets[0]->btnUp->setEnabled(false);
    this->vargets[this->vargets.size() - 1]->btnDown->setEnabled(false);
    // Set the focus on the dashboard tab
    this->ui->tabWidget->setCurrentWidget(this->ui->tabDashboard);
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
        file.close();
        this->Refresh();
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
    clearLayout(ui->boardLayout);
}

//******************************************************************************
// clearLayout()
//******************************************************************************
void clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        if (child->layout() != 0)
            clearLayout(child->layout());
        else if (child->widget() != 0)
            delete child->widget();

        delete child;
    }
}
