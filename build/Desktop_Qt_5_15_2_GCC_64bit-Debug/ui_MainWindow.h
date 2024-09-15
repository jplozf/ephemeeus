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
#include <QtWidgets/QComboBox>
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionOpen;
    QAction *actionRefresh;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtLocation;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *cbxCountry;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *txtLatitude;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *txtLongitude;
    QPushButton *pushButton_12;
    QPushButton *pushButton_11;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnRefresh;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *tabWidget;
    QWidget *tabConsoleOut;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnClearConsole;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer;
    QTextEdit *txtConsoleOut;
    QWidget *tabDashboard;
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QVBoxLayout *boardLayout;
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
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/16x16/Refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRefresh->setIcon(icon2);
        actionRefresh->setMenuRole(QAction::MenuRole::TextHeuristicRole);
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

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        txtLocation = new QLineEdit(verticalLayoutWidget);
        txtLocation->setObjectName(QString::fromUtf8("txtLocation"));

        horizontalLayout_2->addWidget(txtLocation);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/16x16/Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon3);

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/16x16/Pen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon4);

        horizontalLayout_2->addWidget(pushButton_2);


        formLayout_2->setLayout(1, QFormLayout::FieldRole, horizontalLayout_2);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setIcon(icon3);

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setIcon(icon4);

        horizontalLayout_3->addWidget(pushButton_4);


        formLayout_2->setLayout(4, QFormLayout::FieldRole, horizontalLayout_3);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_4->addWidget(lineEdit_3);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setIcon(icon3);

        horizontalLayout_4->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setIcon(icon4);

        horizontalLayout_4->addWidget(pushButton_6);


        formLayout_2->setLayout(5, QFormLayout::FieldRole, horizontalLayout_4);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        cbxCountry = new QComboBox(verticalLayoutWidget);
        cbxCountry->setObjectName(QString::fromUtf8("cbxCountry"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cbxCountry);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        txtLatitude = new QLineEdit(verticalLayoutWidget);
        txtLatitude->setObjectName(QString::fromUtf8("txtLatitude"));
        txtLatitude->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        txtLatitude->setReadOnly(true);

        horizontalLayout_6->addWidget(txtLatitude);

        pushButton_10 = new QPushButton(verticalLayoutWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/16x16/Lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_10->setIcon(icon5);

        horizontalLayout_6->addWidget(pushButton_10);

        pushButton_8 = new QPushButton(verticalLayoutWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/16x16/Write.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_8->setIcon(icon6);

        horizontalLayout_6->addWidget(pushButton_8);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        txtLongitude = new QLineEdit(verticalLayoutWidget);
        txtLongitude->setObjectName(QString::fromUtf8("txtLongitude"));
        txtLongitude->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        txtLongitude->setReadOnly(true);

        horizontalLayout_7->addWidget(txtLongitude);

        pushButton_12 = new QPushButton(verticalLayoutWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setIcon(icon5);

        horizontalLayout_7->addWidget(pushButton_12);

        pushButton_11 = new QPushButton(verticalLayoutWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setIcon(icon6);

        horizontalLayout_7->addWidget(pushButton_11);


        formLayout_2->setLayout(3, QFormLayout::FieldRole, horizontalLayout_7);


        verticalLayout_2->addLayout(formLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        btnRefresh = new QPushButton(verticalLayoutWidget);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));
        btnRefresh->setIcon(icon2);

        horizontalLayout_5->addWidget(btnRefresh);

        pushButton_9 = new QPushButton(verticalLayoutWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        horizontalLayout_5->addWidget(pushButton_9);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        splitter->addWidget(verticalLayoutWidget);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabConsoleOut = new QWidget();
        tabConsoleOut->setObjectName(QString::fromUtf8("tabConsoleOut"));
        tabConsoleOut->setCursor(QCursor(Qt::CrossCursor));
        gridLayout_5 = new QGridLayout(tabConsoleOut);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnClearConsole = new QPushButton(tabConsoleOut);
        btnClearConsole->setObjectName(QString::fromUtf8("btnClearConsole"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/16x16/Trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClearConsole->setIcon(icon7);

        horizontalLayout->addWidget(btnClearConsole);

        pushButton_7 = new QPushButton(tabConsoleOut);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        horizontalLayout->addWidget(pushButton_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        txtConsoleOut = new QTextEdit(tabConsoleOut);
        txtConsoleOut->setObjectName(QString::fromUtf8("txtConsoleOut"));
        txtConsoleOut->setReadOnly(true);

        gridLayout_5->addWidget(txtConsoleOut, 2, 0, 1, 1);

        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/16x16/Computer.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabConsoleOut, icon8, QString());
        tabDashboard = new QWidget();
        tabDashboard->setObjectName(QString::fromUtf8("tabDashboard"));
        gridLayout_3 = new QGridLayout(tabDashboard);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        scrollArea = new QScrollArea(tabDashboard);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 425, 425));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        boardLayout = new QVBoxLayout();
        boardLayout->setObjectName(QString::fromUtf8("boardLayout"));

        gridLayout_4->addLayout(boardLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 0, 0, 1, 1);

        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/16x16/Document Spreadsheet.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabDashboard, icon9, QString());
        tabSettings = new QWidget();
        tabSettings->setObjectName(QString::fromUtf8("tabSettings"));
        gridLayout_7 = new QGridLayout(tabSettings);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        scrollArea_2 = new QScrollArea(tabSettings);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        boxSettings = new QWidget();
        boxSettings->setObjectName(QString::fromUtf8("boxSettings"));
        boxSettings->setGeometry(QRect(0, 0, 425, 425));
        scrollArea_2->setWidget(boxSettings);

        gridLayout_7->addWidget(scrollArea_2, 0, 1, 1, 1);

        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/16x16/Gear.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabSettings, icon10, QString());
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

        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/16x16/Copyright.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabAbout, icon11, QString());
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
        menu_File->addAction(actionRefresh);
        menu_File->addAction(actionQuit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


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
        actionRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
#if QT_CONFIG(tooltip)
        actionRefresh->setToolTip(QCoreApplication::translate("MainWindow", "Refresh F5", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRefresh->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        label->setText(QCoreApplication::translate("MainWindow", "Location", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Time Zone", nullptr));
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Latitude", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Longitude", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Country", nullptr));
        pushButton_10->setText(QString());
        pushButton_8->setText(QString());
        pushButton_12->setText(QString());
        pushButton_11->setText(QString());
        btnRefresh->setText(QString());
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        btnClearConsole->setText(QString());
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabConsoleOut), QCoreApplication::translate("MainWindow", "Console Out", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDashboard), QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
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
