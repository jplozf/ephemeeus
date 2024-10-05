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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionOpen;
    QAction *actionRefresh;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionHelp;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QComboBox *cbxCountry;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtLocation;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *txtLatitude;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *txtLongitude;
    QPushButton *pushButton_12;
    QPushButton *pushButton_11;
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
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_10;
    QComboBox *cbxVargets;
    QLineEdit *txtVargetLabel;
    QPushButton *btnAddVarget;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *txtVarboardTitle;
    QPushButton *btnAddTitle;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *txtVarboardLabel;
    QPushButton *btnAddLabel;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QPushButton *btnRefresh;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *tabWidget;
    QWidget *tabConsole;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnClearConsole;
    QPushButton *btnExportLog;
    QSpacerItem *horizontalSpacer;
    QTextEdit *txtConsole;
    QWidget *tabDashboard;
    QGridLayout *gridLayout_4;
    QLineEdit *txtTitle;
    QSplitter *splitterHelp;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QVBoxLayout *boardLayout;
    QTextEdit *txtHelp;
    QWidget *tabSettings;
    QGridLayout *gridLayout_7;
    QScrollArea *scrollArea_2;
    QWidget *boxSettings;
    QWidget *tabAbout;
    QGridLayout *gridLayout_2;
    QTextBrowser *txtAbout;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1086, 538);
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
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/16x16/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionSave_as->setIcon(icon3);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/16x16/pdf.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon4);
        actionHelp->setMenuRole(QAction::MenuRole::TextHeuristicRole);
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
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        cbxCountry = new QComboBox(verticalLayoutWidget);
        cbxCountry->setObjectName(QString::fromUtf8("cbxCountry"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cbxCountry);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        txtLocation = new QLineEdit(verticalLayoutWidget);
        txtLocation->setObjectName(QString::fromUtf8("txtLocation"));

        horizontalLayout_2->addWidget(txtLocation);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/16x16/Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon5);

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/16x16/Pen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon6);

        horizontalLayout_2->addWidget(pushButton_2);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        txtLatitude = new QLineEdit(verticalLayoutWidget);
        txtLatitude->setObjectName(QString::fromUtf8("txtLatitude"));
        txtLatitude->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        txtLatitude->setReadOnly(true);

        horizontalLayout_6->addWidget(txtLatitude);

        pushButton_10 = new QPushButton(verticalLayoutWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/16x16/Lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_10->setIcon(icon7);

        horizontalLayout_6->addWidget(pushButton_10);

        pushButton_8 = new QPushButton(verticalLayoutWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/16x16/Write.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_8->setIcon(icon8);

        horizontalLayout_6->addWidget(pushButton_8);


        formLayout_2->setLayout(3, QFormLayout::FieldRole, horizontalLayout_6);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        txtLongitude = new QLineEdit(verticalLayoutWidget);
        txtLongitude->setObjectName(QString::fromUtf8("txtLongitude"));
        txtLongitude->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        txtLongitude->setReadOnly(true);

        horizontalLayout_7->addWidget(txtLongitude);

        pushButton_12 = new QPushButton(verticalLayoutWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setIcon(icon7);

        horizontalLayout_7->addWidget(pushButton_12);

        pushButton_11 = new QPushButton(verticalLayoutWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setIcon(icon8);

        horizontalLayout_7->addWidget(pushButton_11);


        formLayout_2->setLayout(4, QFormLayout::FieldRole, horizontalLayout_7);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setIcon(icon5);

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setIcon(icon6);

        horizontalLayout_3->addWidget(pushButton_4);


        formLayout_2->setLayout(5, QFormLayout::FieldRole, horizontalLayout_3);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_4->addWidget(lineEdit_3);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setIcon(icon5);

        horizontalLayout_4->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setIcon(icon6);

        horizontalLayout_4->addWidget(pushButton_6);


        formLayout_2->setLayout(6, QFormLayout::FieldRole, horizontalLayout_4);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(10, QFormLayout::LabelRole, label_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        cbxVargets = new QComboBox(verticalLayoutWidget);
        cbxVargets->setObjectName(QString::fromUtf8("cbxVargets"));

        horizontalLayout_10->addWidget(cbxVargets);

        txtVargetLabel = new QLineEdit(verticalLayoutWidget);
        txtVargetLabel->setObjectName(QString::fromUtf8("txtVargetLabel"));

        horizontalLayout_10->addWidget(txtVargetLabel);

        btnAddVarget = new QPushButton(verticalLayoutWidget);
        btnAddVarget->setObjectName(QString::fromUtf8("btnAddVarget"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/16x16/Plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddVarget->setIcon(icon9);

        horizontalLayout_10->addWidget(btnAddVarget);


        formLayout_2->setLayout(10, QFormLayout::FieldRole, horizontalLayout_10);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font;
        font.setBold(true);
        label_8->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, label_8);

        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        formLayout_2->setWidget(7, QFormLayout::FieldRole, label_9);

        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, label_10);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        txtVarboardTitle = new QLineEdit(verticalLayoutWidget);
        txtVarboardTitle->setObjectName(QString::fromUtf8("txtVarboardTitle"));

        horizontalLayout_8->addWidget(txtVarboardTitle);

        btnAddTitle = new QPushButton(verticalLayoutWidget);
        btnAddTitle->setObjectName(QString::fromUtf8("btnAddTitle"));
        btnAddTitle->setIcon(icon9);

        horizontalLayout_8->addWidget(btnAddTitle);


        formLayout_2->setLayout(8, QFormLayout::FieldRole, horizontalLayout_8);

        label_11 = new QLabel(verticalLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_2->setWidget(9, QFormLayout::LabelRole, label_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        txtVarboardLabel = new QLineEdit(verticalLayoutWidget);
        txtVarboardLabel->setObjectName(QString::fromUtf8("txtVarboardLabel"));

        horizontalLayout_9->addWidget(txtVarboardLabel);

        btnAddLabel = new QPushButton(verticalLayoutWidget);
        btnAddLabel->setObjectName(QString::fromUtf8("btnAddLabel"));
        btnAddLabel->setIcon(icon9);

        horizontalLayout_9->addWidget(btnAddLabel);


        formLayout_2->setLayout(9, QFormLayout::FieldRole, horizontalLayout_9);


        verticalLayout_2->addLayout(formLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout_5->addLayout(verticalLayout);

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
        tabConsole = new QWidget();
        tabConsole->setObjectName(QString::fromUtf8("tabConsole"));
        tabConsole->setCursor(QCursor(Qt::CrossCursor));
        gridLayout_5 = new QGridLayout(tabConsole);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnClearConsole = new QPushButton(tabConsole);
        btnClearConsole->setObjectName(QString::fromUtf8("btnClearConsole"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/16x16/Recycle.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClearConsole->setIcon(icon10);

        horizontalLayout->addWidget(btnClearConsole);

        btnExportLog = new QPushButton(tabConsole);
        btnExportLog->setObjectName(QString::fromUtf8("btnExportLog"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/16x16/Upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExportLog->setIcon(icon11);

        horizontalLayout->addWidget(btnExportLog);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        txtConsole = new QTextEdit(tabConsole);
        txtConsole->setObjectName(QString::fromUtf8("txtConsole"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(10);
        txtConsole->setFont(font1);
        txtConsole->setReadOnly(true);

        gridLayout_5->addWidget(txtConsole, 2, 0, 1, 1);

        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/16x16/Computer.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabConsole, icon12, QString());
        tabDashboard = new QWidget();
        tabDashboard->setObjectName(QString::fromUtf8("tabDashboard"));
        gridLayout_4 = new QGridLayout(tabDashboard);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        txtTitle = new QLineEdit(tabDashboard);
        txtTitle->setObjectName(QString::fromUtf8("txtTitle"));
        txtTitle->setFont(font);
        txtTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        txtTitle->setReadOnly(true);

        gridLayout_4->addWidget(txtTitle, 0, 0, 1, 1);

        splitterHelp = new QSplitter(tabDashboard);
        splitterHelp->setObjectName(QString::fromUtf8("splitterHelp"));
        splitterHelp->setOrientation(Qt::Orientation::Vertical);
        scrollArea = new QScrollArea(splitterHelp);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 487, 68));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        boardLayout = new QVBoxLayout();
        boardLayout->setObjectName(QString::fromUtf8("boardLayout"));

        gridLayout_3->addLayout(boardLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitterHelp->addWidget(scrollArea);
        txtHelp = new QTextEdit(splitterHelp);
        txtHelp->setObjectName(QString::fromUtf8("txtHelp"));
        txtHelp->setReadOnly(true);
        splitterHelp->addWidget(txtHelp);

        gridLayout_4->addWidget(splitterHelp, 1, 0, 1, 1);

        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/16x16/Document Spreadsheet.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabDashboard, icon13, QString());
        tabSettings = new QWidget();
        tabSettings->setObjectName(QString::fromUtf8("tabSettings"));
        gridLayout_7 = new QGridLayout(tabSettings);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        scrollArea_2 = new QScrollArea(tabSettings);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        boxSettings = new QWidget();
        boxSettings->setObjectName(QString::fromUtf8("boxSettings"));
        boxSettings->setGeometry(QRect(0, 0, 487, 386));
        scrollArea_2->setWidget(boxSettings);

        gridLayout_7->addWidget(scrollArea_2, 0, 1, 1, 1);

        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/16x16/Gear.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabSettings, icon14, QString());
        tabAbout = new QWidget();
        tabAbout->setObjectName(QString::fromUtf8("tabAbout"));
        gridLayout_2 = new QGridLayout(tabAbout);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        txtAbout = new QTextBrowser(tabAbout);
        txtAbout->setObjectName(QString::fromUtf8("txtAbout"));

        gridLayout_2->addWidget(txtAbout, 0, 0, 1, 1);

        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/16x16/Copyright.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabAbout, icon15, QString());
        splitter->addWidget(tabWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1086, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(actionOpen);
        menu_File->addAction(actionSave);
        menu_File->addAction(actionSave_as);
        menu_File->addAction(actionRefresh);
        menu_File->addAction(actionQuit);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_as);
        toolBar->addSeparator();
        toolBar->addAction(actionRefresh);
        toolBar->addSeparator();
        toolBar->addAction(actionQuit);
        toolBar->addSeparator();
        toolBar->addAction(actionHelp);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


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
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as...", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
#if QT_CONFIG(tooltip)
        actionHelp->setToolTip(QCoreApplication::translate("MainWindow", "Open PDF Meeus Documentation", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("MainWindow", "Country", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Location", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Latitude", nullptr));
        pushButton_10->setText(QString());
        pushButton_8->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Longitude", nullptr));
        pushButton_12->setText(QString());
        pushButton_11->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Time Zone", nullptr));
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Varget", nullptr));
        btnAddVarget->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "\342\226\270 Time and Location Input", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\342\226\270 Ephemerids Output", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Title", nullptr));
        btnAddTitle->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "Label", nullptr));
        btnAddLabel->setText(QString());
        btnRefresh->setText(QString());
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
#if QT_CONFIG(tooltip)
        btnClearConsole->setToolTip(QCoreApplication::translate("MainWindow", "Clear the console log", nullptr));
#endif // QT_CONFIG(tooltip)
        btnClearConsole->setText(QString());
#if QT_CONFIG(tooltip)
        btnExportLog->setToolTip(QCoreApplication::translate("MainWindow", "Export the console log to local file", nullptr));
#endif // QT_CONFIG(tooltip)
        btnExportLog->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabConsole), QCoreApplication::translate("MainWindow", "Console", nullptr));
        txtTitle->setText(QCoreApplication::translate("MainWindow", "Varboard", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDashboard), QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSettings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAbout), QCoreApplication::translate("MainWindow", "About", nullptr));
        menu_File->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
