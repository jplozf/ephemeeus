#include "DlgInputTime.h"

//******************************************************************************
// DlgInputTime()
//******************************************************************************
DlgInputTime::DlgInputTime(QWidget *parent)
    : QDialog(parent)
{
    QFormLayout *lytMain = new QFormLayout(this);

    /*
    for (int i = 0; i < 4; ++i) {
        QLabel *tLabel = new QLabel(QString("Text_%1:").arg(i), this);
        QLineEdit *tLine = new QLineEdit(this);
        lytMain->addRow(tLabel, tLine);

        fields << tLine;
    }
    */
    QLabel *lblLocation = new QLabel("Location", this);
    QLineEdit *txtLocation = new QLineEdit(this);
    // txtLocation->setText(loc);
    lytMain->addRow(lblLocation, txtLocation);
    fields << txtLocation;

    QLabel *lblLatitude = new QLabel("Latitude", this);
    QLineEdit *txtLatitude = new QLineEdit(this);
    lytMain->addRow(lblLatitude, txtLatitude);
    fields << txtLatitude;

    QLabel *lblLongitude = new QLabel("Longitude", this);
    QLineEdit *txtLongitude = new QLineEdit(this);
    lytMain->addRow(lblLongitude, txtLongitude);
    fields << txtLongitude;

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                           | QDialogButtonBox::Cancel,
                                                       Qt::Horizontal,
                                                       this);
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &DlgInputTime::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &DlgInputTime::reject);
    Q_ASSERT(conn);

    setLayout(lytMain);
}

//******************************************************************************
// getStrings()
//******************************************************************************
QStringList DlgInputTime::getStrings(QWidget *parent, bool *ok)
{
    DlgInputTime *dialog = new DlgInputTime(parent);

    QStringList list;

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    if (ret) {
        foreach (auto field, dialog->fields) {
            list << field->text();
        }
    }

    dialog->deleteLater();

    return list;
}

/*
Now you can use getStrings() method similar to QInputDialog::getText():

QStringList list = InputDialog::getStrings(this);
if (!list.isEmpty()) {
    // use list
}

Or

bool ok;
QStringList list = InputDialog::getStrings(this, &ok);
if (ok) {
    // use list
}
*/
