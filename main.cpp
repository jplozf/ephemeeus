#include <QApplication>
#include "MainWindow.h"

QApplication *a;

//******************************************************************************
// main()
//******************************************************************************
int main(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    a->setWindowIcon(QIcon(":/16x16/Clock.png"));
    MainWindow w(a);
    w.show();
    return a->exec();
}
