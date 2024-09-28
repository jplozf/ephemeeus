#include "Varget.h"

QMap<QString, callback_function> Varboard::aFunc = {{"VarDateTime", &Meeus::VarDateTime},
                                                    {"VarJD", &Meeus::VarJD},
                                                    {"VarDayOfWeek", &Meeus::VarDayOfWeek},
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
    if (this->Function != NULL) {
        lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    } else {
        lbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
    hbox->addWidget(this->lblOrder);
    hbox->addWidget(lbl);

    if (this->Function != NULL) { // Function is NULL for Labels
        txtValue = new QLineEdit();
        txtValue->setReadOnly(true);
        txtValue->setStyleSheet(
            "background-color : #f5f5f4; color : black; border: 2px solid grey;");
        txtValue->setFixedWidth(this->lblOrder->frameGeometry().width() / 2);
        hbox->addWidget(txtValue);
    }

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
    if (this->Function != NULL) { // Function is NULL for Labels
        this->compute();
        this->txtValue->setText(this->Value);
    }
    QString o = QString::asprintf("%05d", this->Order);
    this->lblOrder->setText(o);
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
    Varboard *vb = vg->vb;
    vb->mw->showMessage("Moving down varget at line #" + QString::number(current + 1));
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
    Varboard *vb = vg->vb;
    vb->mw->showMessage("Moving up varget at line #" + QString::number(current + 1));
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
    // Which button was clicked ?
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    // Get the parent's varget of the clicked button
    Varget *vg = (Varget *) btn->parent();
    // Get the order of this varget
    int current = vg->Order - 1;
    // Get the Varboard's owner of this varget
    Varboard *vb = vg->vb;
    // The Varboard has a reference to the MainWindow, so let's display some blahblah
    vb->mw->showMessage("Deleting varget at line #" + QString::number(current + 1));
    // Compute New Order (but I prefer Joy Division) for vargets below the varget deleted
    for (int i = current + 1; i < vb->vargets.size(); ++i) {
        vb->vargets[i]->Order = vb->vargets[i]->Order - 1;
    }
    // Remove the varget from the Varboad's vargets list
    vb->vargets.removeAt(current);
    // and don't forget to delete it
    delete vg;
    // Redisplay the modified Varboard
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
                                    + a->appSettings->get("VARBOARD_COLOR_LINE_1").toString()
                                    + "; color : black;";
        } else {
            this->vargets[i]->css = "background-color : "
                                    + a->appSettings->get("VARBOARD_COLOR_LINE_2").toString()
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
    // Hide or Show Help panel according to settings
    if (a->appSettings->get("VARBOARD_SHOW_HELP").toBool() == true) {
        this->ui->txtHelp->show();
    } else {
        this->ui->txtHelp->hide();
    }
    // Set the focus on the dashboard tab
    this->ui->tabWidget->setCurrentWidget(this->ui->tabDashboard);
}

//******************************************************************************
// SaveJSON()
//******************************************************************************
int Varboard::SaveJSON(QString name)
{
    int rc = 0;
    QJsonObject root;
    root.insert("title", this->ui->txtTitle->text());

    QJsonArray varboard;
    for (int i = 0; i < this->vargets.size(); ++i) {
        QJsonObject varget;
        varget.insert("label", this->vargets[i]->Label);
        varget.insert("function", this->vargets[i]->Function);
        varboard.push_back(varget);
    }
    root.insert("varboard", varboard);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(root);

    QFile fJSON(name);
    if (fJSON.open(QFile::ReadWrite)) {
        fJSON.open(QIODevice::WriteOnly);
        QByteArray uncompressedData = jsonDoc.toJson();
        QByteArray compressedData = qCompress(uncompressedData, 9);
        fJSON.write(compressedData);
        fJSON.close();
    } else {
        rc = 1;
    }
    return rc;
}

//******************************************************************************
// LoadJSON()
//******************************************************************************
int Varboard::LoadJSON(QString name, Meeus *m)
{
    int rc = 0;
    QFile file(name);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = qUncompress(file.readAll());
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject root = jsonDoc.object();

        this->Clear();
        this->ui->txtTitle->setText(root.value("title").toString());
        QJsonArray varboard = root.value("varboard").toArray();
        for (auto i = 0; i < varboard.size(); i++) {
            QJsonObject varget = varboard.at(i).toObject();
            this->addVarget(varget.value("label").toString(),
                            m,
                            varget.value("function").toString());
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
