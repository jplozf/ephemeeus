#ifndef DLGINPUTTIME_H
#define DLGINPUTTIME_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject>

class QLineEdit;
class QLabel;

class DlgInputTime : public QDialog
{
    Q_OBJECT
public:
    explicit DlgInputTime(QWidget *parent = nullptr);
    static QStringList getStrings(QWidget *parent, bool *ok = nullptr);

private:
    QList<QLineEdit *> fields;
};

#endif // DLGINPUTTIME_H
