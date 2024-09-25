#ifndef DLGINPUTLOCATION_H
#define DLGINPUTLOCATION_H

#include <QDialog>

class QLineEdit;
class QLabel;

class DlgInputLocation : public QDialog
{
    Q_OBJECT
public:
    explicit DlgInputLocation(QString loc, QWidget *parent = nullptr);

    static QStringList getStrings(QWidget *parent, QString loc, bool *ok = nullptr);

private:
    QList<QLineEdit *> fields;
};

#endif // DLGINPUTLOCATION_H
