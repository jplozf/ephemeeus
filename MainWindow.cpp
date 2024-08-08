#include "MainWindow.h"

//******************************************************************************
// MainWindow()
//******************************************************************************
MainWindow::MainWindow(QApplication *a, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->a = a;
    ui->setupUi(this);
    app = new App();
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(slotDoExit()));

    readSettings();
    initUI();
    QString appTitle = QString("%1 %2").arg(app->appConstants->getQString("APPLICATION_NAME"),
                                            app->appConstants->getQString("VERSION"));
    setWindowTitle(appTitle);
    showMessage("Welcome");
}

//******************************************************************************
// ~MainWindow()
//******************************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}

//******************************************************************************
// initUI()
//******************************************************************************
void MainWindow::initUI()
{
    //**************************************************************************
    // Theme
    //**************************************************************************
    setTheme();

    //**************************************************************************
    // Settings Form
    //**************************************************************************
    app->appSettings->form(this);

    //**************************************************************************
    // About tab
    //**************************************************************************
    QFile file(":/help.html");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    QString html = app->appConstants->aboutText;
    html += stream.readAll();
    ui->txtAbout->setHtml(html);
}

//******************************************************************************
// setTheme()
//******************************************************************************
void MainWindow::setTheme()
{
    QString tName = app->appSettings->get("APPLICATION_THEME").toString();
    if (tName != "DARK" && tName != "LIGHT" && tName != "ALTERNATE") {
        tName = "ALTERNATE";
    }
    if (tName == "ALTERNATE") {
        this->a->setStyle("Fusion");
        QPalette palette = QPalette();
        palette.setColor(QPalette::Window, QColor(app->appSettings->get("THEME_WINDOW").toString()));
        palette.setColor(QPalette::WindowText,
                         QColor(app->appSettings->get("THEME_WINDOW_TEXT").toString()));
        palette.setColor(QPalette::Base, QColor(app->appSettings->get("THEME_BASE").toString()));
        palette.setColor(QPalette::AlternateBase,
                         QColor(app->appSettings->get("THEME_ALTERNATE_BASE").toString()));
        palette.setColor(QPalette::ToolTipBase,
                         QColor(app->appSettings->get("THEME_TOOLTIP_BASE").toString()));
        palette.setColor(QPalette::ToolTipText,
                         QColor(app->appSettings->get("THEME_TOOLTIP_TEXT").toString()));
        palette.setColor(QPalette::Text, QColor(app->appSettings->get("THEME_TEXT").toString()));
        palette.setColor(QPalette::Button, QColor(app->appSettings->get("THEME_BUTTON").toString()));
        palette.setColor(QPalette::ButtonText,
                         QColor(app->appSettings->get("THEME_BUTTON_TEXT").toString()));
        palette.setColor(QPalette::BrightText,
                         QColor(app->appSettings->get("THEME_BRIGHT_TEXT").toString()));
        palette.setColor(QPalette::Link, QColor(app->appSettings->get("THEME_LINK").toString()));
        palette.setColor(QPalette::Highlight,
                         QColor(app->appSettings->get("THEME_HIGHLIGHT").toString()));
        palette.setColor(QPalette::HighlightedText,
                         QColor(app->appSettings->get("THEME_HIGHLIGHTED_TEXT").toString()));
        a->setPalette(palette);
    } else {
        this->a->setStyle("Fusion");
        QPalette palette = QPalette();
        palette.setColor(QPalette::Window, QColor(app->appConstants->theme[tName][0]));
        palette.setColor(QPalette::WindowText, QColor(app->appConstants->theme[tName][1]));
        palette.setColor(QPalette::Base, QColor(app->appConstants->theme[tName][2]));
        palette.setColor(QPalette::AlternateBase, QColor(app->appConstants->theme[tName][3]));
        palette.setColor(QPalette::ToolTipBase, QColor(app->appConstants->theme[tName][4]));
        palette.setColor(QPalette::ToolTipText, QColor(app->appConstants->theme[tName][5]));
        palette.setColor(QPalette::Text, QColor(app->appConstants->theme[tName][6]));
        palette.setColor(QPalette::Button, QColor(app->appConstants->theme[tName][7]));
        palette.setColor(QPalette::ButtonText, QColor(app->appConstants->theme[tName][8]));
        palette.setColor(QPalette::BrightText, QColor(app->appConstants->theme[tName][9]));
        palette.setColor(QPalette::Link, QColor(app->appConstants->theme[tName][10]));
        palette.setColor(QPalette::Highlight, QColor(app->appConstants->theme[tName][11]));
        palette.setColor(QPalette::HighlightedText, QColor(app->appConstants->theme[tName][12]));
        a->setPalette(palette);
    }
}

//******************************************************************************
// showMessage()
//******************************************************************************
void MainWindow::showMessage(const QString &message, int timeout)
{
    if (timeout == -1) {
        timeout = app->appSettings->get("APPLICATION_STATUSBAR_TIMEOUT").toInt();
    }
    ui->statusBar->showMessage(message, timeout);
}

//******************************************************************************
// slotDoExit()
//******************************************************************************
void MainWindow::slotDoExit()
{
    this->close();
}

//******************************************************************************
// closeEvent()
//******************************************************************************
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (app->appSettings->get("APPLICATION_CONFIRM_EXIT").toBool() == true) {
        QMessageBox::StandardButton rc;
        rc = QMessageBox::question(this,
                                   app->appConstants->getQString("APPLICATION_NAME"),
                                   QString("Really quit ?\n"),
                                   QMessageBox::Yes | QMessageBox::No);
        if (rc == QMessageBox::Yes) {
            saveSettings();
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        saveSettings();
        event->accept();
    }
}

//******************************************************************************
// saveSettings()
//******************************************************************************
void MainWindow::saveSettings()
{
    //**************************************************************************
    // Application state saving
    //**************************************************************************
    QSettings registry(app->appConstants->getQString("ORGANIZATION_NAME"),
                       app->appConstants->getQString("APPLICATION_NAME"));
    registry.setValue("geometry", saveGeometry());
    registry.setValue("windowState", saveState());
    registry.setValue("splitter", ui->splitter->saveState());
    registry.setValue("tab", ui->tabWidget->currentIndex());

    //**************************************************************************
    // Settings saving
    //**************************************************************************
    Settings mySettings;
    mySettings.write();
}

//******************************************************************************
// readSettings()
//******************************************************************************
void MainWindow::readSettings()
{
    QSettings registry(app->appConstants->getQString("ORGANIZATION_NAME"),
                       app->appConstants->getQString("APPLICATION_NAME"));

    const QByteArray geometry = registry.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }

    const QByteArray windowState = registry.value("windowState", QByteArray()).toByteArray();
    if (!windowState.isEmpty()) {
        restoreState(registry.value("windowState").toByteArray());
    }

    const QByteArray splitter = registry.value("splitter", QByteArray()).toByteArray();
    if (!splitter.isEmpty()) {
        ui->splitter->restoreState(registry.value("splitter").toByteArray());
    }

    const int tabIndex = registry.value("tab", 0).toInt();
    ui->tabWidget->setCurrentIndex(tabIndex);
}
