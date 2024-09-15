#include "MainWindow.h"

//******************************************************************************
// MainWindow()
//******************************************************************************
MainWindow::MainWindow(QApplication* a, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->a = a;
  ui->setupUi(this);
  app = new App();
  QDir appDir = QDir(QDir::homePath()).filePath(app->appConstants->getQString("APP_FOLDER"));
  connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(slotDoExit()));

  readSettings();
  initUI();
  QString appTitle =
      QString("%1 %2").arg(app->appConstants->getQString("APPLICATION_NAME"),
                           app->appConstants->getQString("VERSION"));
  setWindowTitle(appTitle);
  showMessage("Welcome");

  db = QSqlDatabase::addDatabase("QSQLITE");
  // FIXME : Fix the path to the SQLite database
  // https://drive.google.com/file/d/1wSa3Py52II9EeCvbRUiVkr-MTIQF5lRa/view?usp=sharing
  QString dbName = QDir(appDir).filePath(app->appConstants->getQString("CITIES_DATABASE"));
  if (QFile::exists(dbName)) {
      db.setDatabaseName(dbName);
      if (!db.open()) {
          showMessage("Can't open database");
      } else {
          QSqlTableModel *modelCities = new QSqlTableModel(this, db);
          modelCities->setTable("cities");
          modelCities->select();

          QCompleter *cityCompleter = new QCompleter(modelCities, this);
          cityCompleter->setCompletionColumn(2); // "City" Column
          ui->txtLocation->setCompleter(cityCompleter);

          QSqlTableModel *modelCountries = new QSqlTableModel(this, db);
          modelCountries->setTable("countries");
          modelCountries->select();
          ui->cbxCountry->setModel(modelCountries);
          ui->cbxCountry->setModelColumn(modelCountries->fieldIndex("country"));
      }
  }

  Meeus::Location defaultLocation;
  defaultLocation.Name =
      app->appSettings->get("DEFAULT_LOCATION_NAME").toString();
  defaultLocation.Latitude =
      app->appSettings->get("DEFAULT_LOCATION_LATITUDE").toDouble();
  defaultLocation.Longitude =
      app->appSettings->get("DEFAULT_LOCATION_LONGITUDE").toDouble();

  meeus = new Meeus(defaultLocation);
  meeus->init();

  // Display the default Varboard
  this->vb = new Varboard(app, ui);
  QString fName = QDir(appDir).filePath(app->appConstants->getQString("DEFAULT_VARBOARD"));
  if (QFile::exists(fName)) {
      // Load default Varboard if it exists...
      this->vb->LoadFile(fName, meeus);
  } else {
      // ...Or create it otherwise
      this->vb->addVarget("Date & Time", meeus, "VarDateTime");
      this->vb->addVarget("Location", meeus, "VarLocation");
      this->vb->addVarget("Julian Day", meeus, "VarJD");
      this->vb->pack();
      this->vb->SaveFile(fName);
  }

  this->refresh();
}

//******************************************************************************
// ~MainWindow()
//******************************************************************************
MainWindow::~MainWindow() {
  db.close();
  delete ui;
}

//******************************************************************************
// initUI()
//******************************************************************************
void MainWindow::initUI() {
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
void MainWindow::setTheme() {
  QString tName = app->appSettings->get("APPLICATION_THEME").toString();
  if (tName != "DARK" && tName != "LIGHT" && tName != "ALTERNATE") {
    tName = "ALTERNATE";
  }
  if (tName == "ALTERNATE") {
    this->a->setStyle("Fusion");
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window,
                     QColor(app->appSettings->get("THEME_WINDOW").toString()));
    palette.setColor(
        QPalette::WindowText,
        QColor(app->appSettings->get("THEME_WINDOW_TEXT").toString()));
    palette.setColor(QPalette::Base,
                     QColor(app->appSettings->get("THEME_BASE").toString()));
    palette.setColor(
        QPalette::AlternateBase,
        QColor(app->appSettings->get("THEME_ALTERNATE_BASE").toString()));
    palette.setColor(
        QPalette::ToolTipBase,
        QColor(app->appSettings->get("THEME_TOOLTIP_BASE").toString()));
    palette.setColor(
        QPalette::ToolTipText,
        QColor(app->appSettings->get("THEME_TOOLTIP_TEXT").toString()));
    palette.setColor(QPalette::Text,
                     QColor(app->appSettings->get("THEME_TEXT").toString()));
    palette.setColor(QPalette::Button,
                     QColor(app->appSettings->get("THEME_BUTTON").toString()));
    palette.setColor(
        QPalette::ButtonText,
        QColor(app->appSettings->get("THEME_BUTTON_TEXT").toString()));
    palette.setColor(
        QPalette::BrightText,
        QColor(app->appSettings->get("THEME_BRIGHT_TEXT").toString()));
    palette.setColor(QPalette::Link,
                     QColor(app->appSettings->get("THEME_LINK").toString()));
    palette.setColor(
        QPalette::Highlight,
        QColor(app->appSettings->get("THEME_HIGHLIGHT").toString()));
    palette.setColor(
        QPalette::HighlightedText,
        QColor(app->appSettings->get("THEME_HIGHLIGHTED_TEXT").toString()));
    a->setPalette(palette);
  } else {
    this->a->setStyle("Fusion");
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window,
                     QColor(app->appConstants->theme[tName][0]));
    palette.setColor(QPalette::WindowText,
                     QColor(app->appConstants->theme[tName][1]));
    palette.setColor(QPalette::Base,
                     QColor(app->appConstants->theme[tName][2]));
    palette.setColor(QPalette::AlternateBase,
                     QColor(app->appConstants->theme[tName][3]));
    palette.setColor(QPalette::ToolTipBase,
                     QColor(app->appConstants->theme[tName][4]));
    palette.setColor(QPalette::ToolTipText,
                     QColor(app->appConstants->theme[tName][5]));
    palette.setColor(QPalette::Text,
                     QColor(app->appConstants->theme[tName][6]));
    palette.setColor(QPalette::Button,
                     QColor(app->appConstants->theme[tName][7]));
    palette.setColor(QPalette::ButtonText,
                     QColor(app->appConstants->theme[tName][8]));
    palette.setColor(QPalette::BrightText,
                     QColor(app->appConstants->theme[tName][9]));
    palette.setColor(QPalette::Link,
                     QColor(app->appConstants->theme[tName][10]));
    palette.setColor(QPalette::Highlight,
                     QColor(app->appConstants->theme[tName][11]));
    palette.setColor(QPalette::HighlightedText,
                     QColor(app->appConstants->theme[tName][12]));
    a->setPalette(palette);
  }
}

//******************************************************************************
// showMessage()
//******************************************************************************
void MainWindow::showMessage(const QString& message, int timeout) {
  if (timeout == -1) {
    timeout = app->appSettings->get("APPLICATION_STATUSBAR_TIMEOUT").toInt();
  }
  ui->statusBar->showMessage(message, timeout);
}

//******************************************************************************
// slotDoExit()
//******************************************************************************
void MainWindow::slotDoExit() {
  this->close();
}

//******************************************************************************
// closeEvent()
//******************************************************************************
void MainWindow::closeEvent(QCloseEvent* event) {
  if (app->appSettings->get("APPLICATION_CONFIRM_EXIT").toBool() == true) {
    QMessageBox::StandardButton rc;
    rc = QMessageBox::question(
        this, app->appConstants->getQString("APPLICATION_NAME"),
        QString("Really quit ?\n"), QMessageBox::Yes | QMessageBox::No);
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
void MainWindow::saveSettings() {
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
void MainWindow::readSettings() {
  QSettings registry(app->appConstants->getQString("ORGANIZATION_NAME"),
                     app->appConstants->getQString("APPLICATION_NAME"));

  const QByteArray geometry =
      registry.value("geometry", QByteArray()).toByteArray();
  if (geometry.isEmpty()) {
    const QRect availableGeometry =
        QApplication::desktop()->availableGeometry();
    resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
    move((availableGeometry.width() - width()) / 2,
         (availableGeometry.height() - height()) / 2);
  } else {
    restoreGeometry(geometry);
  }

  const QByteArray windowState =
      registry.value("windowState", QByteArray()).toByteArray();
  if (!windowState.isEmpty()) {
    restoreState(registry.value("windowState").toByteArray());
  }

  const QByteArray splitter =
      registry.value("splitter", QByteArray()).toByteArray();
  if (!splitter.isEmpty()) {
    ui->splitter->restoreState(registry.value("splitter").toByteArray());
  }

  const int tabIndex = registry.value("tab", 0).toInt();
  ui->tabWidget->setCurrentIndex(tabIndex);
}

//******************************************************************************
// out()
//******************************************************************************
void MainWindow::out(QString txt) {
  ui->txtConsoleOut->append(txt);
}

//******************************************************************************
// refresh()
//******************************************************************************
void MainWindow::refresh() {
    this->meeus->refresh();
    this->vb->Refresh();
}

//******************************************************************************
// on_actionRefresh_triggered()
//******************************************************************************
void MainWindow::on_actionRefresh_triggered() {
  this->refresh();
}

//******************************************************************************
// on_btnClearConsole_clicked()
//******************************************************************************
void MainWindow::on_btnClearConsole_clicked() {
  ui->txtConsoleOut->setText("");
}

//******************************************************************************
// on_btnRefresh_clicked()
//******************************************************************************
void MainWindow::on_btnRefresh_clicked() {
  this->refresh();
}

//******************************************************************************
// on_txtLocation_editingFinished()
//******************************************************************************
void MainWindow::on_txtLocation_editingFinished() {
  QSqlQuery query;
  // select * from cities where city="Paris" and country_idx=(select country_idx
  // from countries where country="France");
  if (db.isOpen()) {
      query.prepare(
          "SELECT latitude, longitude FROM cities WHERE city = :location AND " "country_idx = " "(S" "EL" "EC" "T " "co" "un" "tr" "y_" "id" "x " "FROM countries WHERE " "country = :country)");
      query.bindValue(":location", ui->txtLocation->text());
      query.bindValue(":country", ui->cbxCountry->currentText());
      if (!query.exec()) {
          showMessage("Query failed!");
      } else {
          if (query.first()) { // get the first record in the result,
              ui->txtLatitude->setText(query.value("latitude").toString());
              ui->txtLongitude->setText(query.value("longitude").toString());
          } else {
              showMessage("Data not found");
          }
      }
  }
}
