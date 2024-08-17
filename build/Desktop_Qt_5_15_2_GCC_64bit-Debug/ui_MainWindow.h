/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionOpen;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QTabWidget *tabWidget;
    QWidget *tabConsoleOut;
    QGridLayout *gridLayout_5;
    QWidget *tabEnvironment;
    QGridLayout *gridLayout_3;
    QWidget *tabSettings;
    QGridLayout *gridLayout_7;
    QScrollArea *scrollArea_2;
    QWidget *boxSettings;
    QWidget *tabXMLFile;
    QGridLayout *gridLayout_8;
    QWidget *tabAbout;
    QGridLayout *gridLayout_2;
    QTextBrowser *txtAbout;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(901, 538);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/16x16/Close.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/16x16/Document Text.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Orientation::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/16x16/Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon2);

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/16x16/Pen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon3);

        horizontalLayout_2->addWidget(pushButton_2);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setIcon(icon2);

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setIcon(icon3);

        horizontalLayout_3->addWidget(pushButton_4);


        formLayout_2->setLayout(1, QFormLayout::FieldRole, horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_4->addWidget(lineEdit_3);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setIcon(icon2);

        horizontalLayout_4->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setIcon(icon3);

        horizontalLayout_4->addWidget(pushButton_6);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, horizontalLayout_4);


        verticalLayout_2->addLayout(formLayout_2);

        splitter->addWidget(verticalLayoutWidget);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabConsoleOut = new QWidget();
        tabConsoleOut->setObjectName(QString::fromUtf8("tabConsoleOut"));
        tabConsoleOut->setCursor(QCursor(Qt::CrossCursor));
        gridLayout_5 = new QGridLayout(tabConsoleOut);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/16x16/Computer.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabConsoleOut, icon4, QString());
        tabEnvironment = new QWidget();
        tabEnvironment->setObjectName(QString::fromUtf8("tabEnvironment"));
        gridLayout_3 = new QGridLayout(tabEnvironment);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/16x16/Bubble4.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabEnvironment, icon5, QString());
        tabSettings = new QWidget();
        tabSettings->setObjectName(QString::fromUtf8("tabSettings"));
        gridLayout_7 = new QGridLayout(tabSettings);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        scrollArea_2 = new QScrollArea(tabSettings);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        boxSettings = new QWidget();
        boxSettings->setObjectName(QString::fromUtf8("boxSettings"));
        boxSettings->setGeometry(QRect(0, 0, 436, 425));
        scrollArea_2->setWidget(boxSettings);

        gridLayout_7->addWidget(scrollArea_2, 0, 1, 1, 1);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/16x16/Gear.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabSettings, icon6, QString());
        tabXMLFile = new QWidget();
        tabXMLFile->setObjectName(QString::fromUtf8("tabXMLFile"));
        gridLayout_8 = new QGridLayout(tabXMLFile);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        tabWidget->addTab(tabXMLFile, icon1, QString());
        tabAbout = new QWidget();
        tabAbout->setObjectName(QString::fromUtf8("tabAbout"));
        gridLayout_2 = new QGridLayout(tabAbout);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        txtAbout = new QTextBrowser(tabAbout);
        txtAbout->setObjectName(QString::fromUtf8("txtAbout"));

        gridLayout_2->addWidget(txtAbout, 0, 0, 1, 1);

        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/16x16/Copyright.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabAbout, icon7, QString());
        splitter->addWidget(tabWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 901, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(actionOpen);
        menu_File->addAction(actionQuit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form1", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "&Quit F10", nullptr));
        actionQuit->setIconText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "F10", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Location", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Time Zone", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabConsoleOut), QCoreApplication::translate("MainWindow", "Console Out", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabEnvironment), QCoreApplication::translate("MainWindow", "Environment", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSettings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabXMLFile), QCoreApplication::translate("MainWindow", "Commands", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAbout), QCoreApplication::translate("MainWindow", "About", nullptr));
        menu_File->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
