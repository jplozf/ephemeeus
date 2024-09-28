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

  initUI();
  this->appTitle = QString("%1 %2").arg(app->appConstants->getQString("APPLICATION_NAME"),
                                        app->appConstants->getQString("VERSION"));
  this->setWindowTitle(this->appTitle);
  showMessage("Welcome");

  db = QSqlDatabase::addDatabase("QSQLITE");
  // Try to open the local database otherwise download it from ligorax.free.fr
  QString dbName = QDir(appDir).filePath(app->appConstants->getQString("CITIES_DATABASE"));
  if (!QFile::exists(dbName)) {
      showMessage("Downloading cities database from internet");
      Downloader::downloadFile(app->appConstants->getQString("CITIES_URL"), dbName);
  }

  db.setDatabaseName(dbName);
  if (!db.open()) {
      showMessage("Can't open cities database");
  } else {
      showMessage("Cities database open");
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

  readSettings();

  // TODO : Read the previous location from the readSettings()
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
  this->vb = new Varboard(app, this, ui);
  QString fName = QDir(appDir).filePath(app->appConstants->getQString("DEFAULT_VARBOARD"));
  if (QFile::exists(fName)) {
      // Load default Varboard if it exists...
      this->vb->LoadJSON(fName, meeus);
      showMessage("Default varboard open");
  } else {
      // ...Or create it otherwise
      this->vb->addVarget("Date & Time", meeus, "VarDateTime");
      this->vb->addVarget("Location", meeus, "VarLocation");
      this->vb->addVarget("Latitude", meeus, "VarLatitude");
      this->vb->addVarget("Longitude", meeus, "VarLongitude");
      this->vb->addVarget("Julian Day", meeus, "VarJD");
      this->vb->pack();
      this->vb->SaveJSON(fName);
      showMessage("Creating default varboard");
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
  showMessage(app->appConstants->consoleText);

  //**************************************************************************
  // Populate Vargets List
  //**************************************************************************
  for (auto it = Varboard::aFunc.keyValueBegin(); it != Varboard::aFunc.keyValueEnd(); ++it) {
      qDebug() << it->first << it->second;
      ui->cbxVargets->addItem(it->first);
  }
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

  QStringList msgList = message.split("\n");
  for (const auto &i : msgList) {
      if (i != "") {
          ui->statusBar->showMessage(i, timeout);
          QDateTime date = QDateTime::currentDateTime();
          QString formattedTime = date.toString("yyyyMMdd-hhmmss");
          ui->txtConsole->append(formattedTime + " : " + i);
      }
  }
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
        showMessage("Exiting");
        saveSettings();
        event->accept();
    } else {
        showMessage("Cancel exit");
        event->ignore();
    }
  } else {
      showMessage("Exiting");
      saveSettings();
      event->accept();
  }
}

//******************************************************************************
// saveSettings()
//******************************************************************************
void MainWindow::saveSettings() {
    showMessage("Saving settings");
    //**************************************************************************
    // Application state saving
    //**************************************************************************
    QSettings registry(app->appConstants->getQString("ORGANIZATION_NAME"),
                       app->appConstants->getQString("APPLICATION_NAME"));
    registry.setValue("geometry", saveGeometry());
    registry.setValue("windowState", saveState());
    registry.setValue("splitter", ui->splitter->saveState());
    registry.setValue("splitterHelp", ui->splitterHelp->saveState());
    registry.setValue("tab", ui->tabWidget->currentIndex());

    // TODO : Store the current location
    registry.setValue("country", ui->cbxCountry->currentText());
    registry.setValue("location", ui->txtLocation->text());
    registry.setValue("latitude", ui->txtLatitude->text());
    registry.setValue("longitude", ui->txtLongitude->text());

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
    showMessage("Reading settings");
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

  const QByteArray splitterHelp = registry.value("splitterHelp", QByteArray()).toByteArray();
  if (!splitterHelp.isEmpty()) {
      ui->splitterHelp->restoreState(registry.value("splitterHelp").toByteArray());
  }

  const int tabIndex = registry.value("tab", 0).toInt();
  ui->tabWidget->setCurrentIndex(tabIndex);

  // TODO : Read the previous stored location
  const QString country = registry.value("country", "").toString();
  qDebug() << country;
  int index = ui->cbxCountry->findText(country);
  if (index != -1) { // -1 for not found
      ui->cbxCountry->setCurrentIndex(index);
      qDebug() << index;
  }
  const QString location = registry.value("location", "").toString();
  ui->txtLocation->setText(location);
  qDebug() << location;
  const QString latitude = registry.value("latitude", "").toString();
  ui->txtLatitude->setText(latitude);
  qDebug() << latitude;
  const QString longitude = registry.value("longitude", "").toString();
  ui->txtLongitude->setText(longitude);
  qDebug() << longitude;
}

//******************************************************************************
// out()
//******************************************************************************
void MainWindow::out(QString txt) {
    ui->txtConsole->append(txt);
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
    ui->txtConsole->setText("");
}

//******************************************************************************
// on_btnExportLog_clicked()
//******************************************************************************
void MainWindow::on_btnExportLog_clicked()
{
    QDateTime now = QDateTime::currentDateTime();
    QString filename = QDir::homePath() + QDir::separator()
                       + app->appConstants->getQString("APPLICATION_NAME") + "_"
                       + now.toString("yyyyMMdd-hhmmss") + ".log";
    showMessage("Log exported to " + filename);
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << ui->txtConsole->toPlainText();
    file.close();
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
    // FIXME : Manage the case the cities database is not accessible
    if (db.isOpen()) {
        QSqlQuery query;
        // select * from cities where city="Paris" and country_idx=(select country_idx
        // from countries where country="France");
        query
            .prepare(
                "SELECT latitude, longitude FROM cities WHERE city = :location AND " "country_idx " "= (SELECT country_idx FROM countries WHERE country = " ":country)");
        query.bindValue(":location", ui->txtLocation->text());
        query.bindValue(":country", ui->cbxCountry->currentText());
        if (!query.exec()) {
            showMessage("Query failed!");
        } else {
            if (query.first()) { // get the first record in the result,
                ui->txtLatitude->setText(query.value("latitude").toString());
                ui->txtLongitude->setText(query.value("longitude").toString());
                Meeus::Location loc;
                loc.Name = ui->txtLocation->text();
                loc.Latitude = ui->txtLatitude->text().toDouble();
                loc.Longitude = ui->txtLongitude->text().toDouble();
                meeus->SetLocation(loc);
                showMessage("Location set");
            } else {
                showMessage("Data not found");
            }
        }
    } else {
        // TODO : Raise a custom InputDialog to input the values
        bool ok;
        QStringList list = DlgInputLocation::getStrings(this, ui->txtLocation->text(), &ok);
        if (ok) {
            // Use list
        } else {
            // Use the default location
        }
    }
}

//******************************************************************************
// on_actionOpen_triggered()
//******************************************************************************
void MainWindow::on_actionOpen_triggered()
{
    QString vbdName = QFileDialog::getOpenFileName(this,
                                                   "Open a varboard...",
                                                   QDir::homePath(),
                                                   "Varboard (*.vbd)");
    if (!vbdName.isNull()) {
        showMessage("Opening " + vbdName);
        QFileInfo fi(vbdName);
        this->setWindowTitle(this->appTitle + " - " + fi.fileName());
        delete this->vb;
        this->vb = new Varboard(app, this, ui);
        // this->vb->LoadFile(vbdName, meeus);
        this->vb->LoadJSON(vbdName, meeus);
        this->vbdFileName = vbdName;
    } else {
        showMessage("Cancelling open");
    }
}

//******************************************************************************
// on_btnAddVarget_clicked()
//******************************************************************************
void MainWindow::on_btnAddVarget_clicked()
{
    this->showMessage("Adding Varget [" + ui->cbxVargets->currentText() + "] with label \""
                      + ui->txtVargetLabel->text() + "\"");
    this->vb->addVarget(ui->txtVargetLabel->text(), meeus, ui->cbxVargets->currentText());
    this->vb->Refresh();
}

//******************************************************************************
// on_cbxVargets_currentIndexChanged()
//******************************************************************************
void MainWindow::on_cbxVargets_currentIndexChanged(int index)
{
    ui->txtVargetLabel->setText(ui->cbxVargets->currentText());
    ui->txtVargetLabel->selectAll();
    QTimer::singleShot(0, ui->txtVargetLabel, SLOT(setFocus()));
}

//******************************************************************************
// on_actionSave_triggered()
//******************************************************************************
void MainWindow::on_actionSave_triggered()
{
    if (this->vbdFileName != "") {
        showMessage("Saving " + vbdFileName);
        QFileInfo fi2(vbdFileName);
        this->setWindowTitle(this->appTitle + " - " + fi2.fileName());
        // this->vb->SaveFile(vbdFileName);
        this->vb->SaveJSON(vbdFileName);
    } else {
        this->on_actionSave_as_triggered();
    }
}

//******************************************************************************
// on_actionSave_as_triggered()
//******************************************************************************
void MainWindow::on_actionSave_as_triggered()
{
    QString vbdName = QFileDialog::getSaveFileName(this,
                                                   "Save this varboard...",
                                                   QDir::homePath(),
                                                   "Varboard (*.vbd)");
    if (!vbdName.isNull()) {
        // Check if extension is .vbd
        QFileInfo fi1(vbdName);
        QString ext = fi1.suffix();
        if (ext != "vbd") {
            vbdName += ".vbd";
        }
        // Save the file
        showMessage("Saving " + vbdName);
        QFileInfo fi2(vbdName);
        this->setWindowTitle(this->appTitle + " - " + fi2.fileName());
        // this->vb->SaveFile(vbdName);
        this->vb->SaveJSON(vbdName);
        this->vbdFileName = vbdName;
    } else {
        showMessage("Cancelling save");
    }
}

//******************************************************************************
// on_btnAddLabel_clicked()
//******************************************************************************
void MainWindow::on_btnAddLabel_clicked()
{
    QString label = ui->txtVarboardLabel->text();
    if (label != "") {
        this->vb->addVarget(ui->txtVarboardLabel->text(), meeus, NULL);
        this->vb->Refresh();
        ui->txtVarboardLabel->setText("");
        showMessage("Label \"" + label + "\" added");
    } else {
        showMessage("Cannot add an empty label");
    }
}

//******************************************************************************
// on_btnAddTitle_clicked()
//******************************************************************************
void MainWindow::on_btnAddTitle_clicked()
{
    QString title = ui->txtVarboardTitle->text();
    if (title != "") {
        ui->txtTitle->setText(title);
        ui->txtVarboardTitle->setText("");
        showMessage("Title set to \"" + title + "\"");
    } else {
        showMessage("Cannot set an empty title");
    }
}
