#include "MainWindow.h"

//******************************************************************************
// MainWindow()
//******************************************************************************
MainWindow::MainWindow(QApplication* a, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->a = a;
  this->TimeLocked = false;
  ui->setupUi(this);
  app = new App();
  this->nPreviousMessage = 1;

  // APP_FOLDER
  QDir appDir = QDir(QDir::homePath()).filePath(app->appConstants->getQString("APP_FOLDER"));
  if (!appDir.exists())
      appDir.mkpath(".");
  this->appDir = appDir;

  connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(slotDoExit()));

  this->appTitle = QString("%1 %2").arg(app->appConstants->getQString("APPLICATION_NAME"),
                                        app->appConstants->getQString("VERSION"));
  initUI();
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
      modelCities = new QSqlTableModel(this, db);
      modelCities->setTable("cities");
      // modelCities->setFilter("country_idx='be'");
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
  defaultLocation.Country = app->appSettings->get("DEFAULT_LOCATION_COUNTRY").toString();
  defaultLocation.Name = app->appSettings->get("DEFAULT_LOCATION_NAME").toString();
  defaultLocation.Latitude =
      app->appSettings->get("DEFAULT_LOCATION_LATITUDE").toDouble();
  defaultLocation.Longitude =
      app->appSettings->get("DEFAULT_LOCATION_LONGITUDE").toDouble();

  meeus = new Meeus(defaultLocation);
  meeus->init();

  //****************************************************************************
  // Real Time or not
  //****************************************************************************
  this->tTime = new QTimer(this);
  this->tTime->setInterval(1000);
  connect(this->tTime, &QTimer::timeout, [&]() {
      QString time1 = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
      ui->txtTime->setDateTime(QDateTime::currentDateTime());
      if (this->ui->chkAutoRefresh->isChecked()) {
          this->refresh();
      }
  });
  this->tTime->start();

  // Display the default Varboard
  this->vb = new Varboard(app, this, ui);
  QString fName = QDir(appDir).filePath(app->appConstants->getQString("DEFAULT_VARBOARD"));
  if (QFile::exists(fName)) {
      // Load default Varboard if it exists...
      this->vb->LoadJSON(fName, meeus);
      showMessage("Default varboard open");
      QFileInfo fi(fName);
      this->lblFileName->setText("File : " + fi.fileName());
      this->vbdFileName = fName;
      this->vbdModified = false;
      this->displayFileName();
  } else {
      // ...Or create it otherwise
      this->vb->addVarget("Date & Time", meeus, "VarDateTime");
      this->vb->addVarget("Location", meeus, "VarLocation");
      this->vb->addVarget("Latitude", meeus, "VarLatitude");
      this->vb->addVarget("Longitude", meeus, "VarLongitude");
      this->vb->addVarget("Julian Day", meeus, "VarJulianDay");
      this->vb->pack();
      this->vb->SaveJSON(fName);
      showMessage("Creating default varboard");
      QFileInfo fi(fName);
      this->lblFileName->setText("File : " + fi.fileName());
      this->vbdFileName = fName;
      this->vbdModified = false;
      this->displayFileName();
  }

  // And the Show must go on !
  // We have to specify manually the current datetime,
  // because the timer is not yet triggered at this time
  this->meeus->refresh(QDateTime::currentDateTime());
  this->vb->Refresh();
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
  // Status Bar
  //**************************************************************************
  QString css = QString("background-color: %1;").arg(app->appConstants->getQString("BAR_COLOR"));
  ui->statusBar->setStyleSheet(css);
  this->lblFileName = new QLabel();
  this->lblFileName->setIndent(10);
  ui->statusBar->addPermanentWidget(this->lblFileName);
  this->lblNumberVargets = new QLabel("0");
  this->lblNumberVargets->setIndent(10);
  //**************************************************************************
  // Menu Bar & Tool Bar
  //**************************************************************************
  ui->menuBar->setStyleSheet(css);
  ui->toolBar->setStyleSheet(css);
  ui->statusBar->addPermanentWidget(this->lblNumberVargets);
  QWidget *spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  ui->toolBar->addWidget(spacer);
  this->lblTitle = new QLabel(this->appTitle);
  this->lblTitle->setStyleSheet("font-weight: bold; font-style: italic;");
  ui->toolBar->addWidget(this->lblTitle);

  //**************************************************************************
  // MRU Menu
  //**************************************************************************
  for (int i = 0; i < this->app->appConstants->getInt("MRU_FILES"); i++) {
      actMRUFiles.resize(i + 1);
      actMRUFiles[i] = new QAction(this);
      actMRUFiles[i]->setVisible(false);
      connect(actMRUFiles[i], SIGNAL(triggered()), this, SLOT(openMRUFile()));
      ui->menuRecent->addAction(actMRUFiles[i]);
      // qDebug() << i;
  }

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
  // Populate Time Zone List
  //**************************************************************************
  QList<QByteArray> ids = QTimeZone::availableTimeZoneIds();
  foreach (QByteArray id, ids) {
      ui->cbxTimeZone->addItem(id);
  }

  //**************************************************************************
  // Populate Vargets List
  //**************************************************************************
  for (auto it = Varboard::aKeywords.keyValueBegin(); it != Varboard::aKeywords.keyValueEnd();
       ++it) {
      QTreeWidgetItem *topItem = new QTreeWidgetItem(ui->trwVargets);
      ui->trwVargets->addTopLevelItem(topItem);
      topItem->setText(0, it->first);
      topItem->setExpanded(true);
      for (const auto &i : it->second) {
          QTreeWidgetItem *item = new QTreeWidgetItem(topItem);
          item->setText(0, i);
      }
  }
  ui->trwVargets->setItemsExpandable(false);

  //**************************************************************************
  // Show Doc Viewer or not
  //**************************************************************************
  if (app->appSettings->get("APPLICATION_SHOW_DOC").toBool() == false) {
      ui->actionHelp->setEnabled(false);
  }

  //**************************************************************************
  // Show Time !!!
  //**************************************************************************
  ui->txtTime->setReadOnly(true);
  // this->tTime->start();
  QPixmap pixmap(":/16x16/Lock Open.png");
  QIcon btnIcon(pixmap);
  ui->btnTimeLocked->setIcon(btnIcon);
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
          if (i == this->previousMessage) {
              this->nPreviousMessage++;
              ui->txtConsole->setFocus();
              QTextCursor storeCursorPos = ui->txtConsole->textCursor();
              ui->txtConsole->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
              ui->txtConsole->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
              ui->txtConsole->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
              ui->txtConsole->textCursor().removeSelectedText();
              ui->txtConsole->textCursor().deletePreviousChar();
              ui->txtConsole->setTextCursor(storeCursorPos);
              ui->txtConsole->append(formattedTime + " : " + i
                                     + QString(" (x%1)").arg(this->nPreviousMessage));
          } else {
              ui->txtConsole->append(formattedTime + " : " + i);
              this->previousMessage = i;
              this->nPreviousMessage = 1;
          }
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
    if (this->vbdModified) {
        QMessageBox::StandardButton rc;
        rc = QMessageBox::question(
            this,
            app->appConstants->getQString("APPLICATION_NAME"),
            QString("Current Varboard has been modified.\nDo you want to save it ?\n"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (rc == QMessageBox::Cancel) {
            showMessage("Cancel exit");
            event->ignore();
        } else {
            if (rc == QMessageBox::Yes) {
                this->on_actionSave_triggered();
            }
            if (app->appSettings->get("APPLICATION_CONFIRM_EXIT").toBool() == true) {
                QMessageBox::StandardButton rc;
                rc = QMessageBox::question(this,
                                           app->appConstants->getQString("APPLICATION_NAME"),
                                           QString("Really quit ?\n"),
                                           QMessageBox::Yes | QMessageBox::No);
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
    } else {
        if (app->appSettings->get("APPLICATION_CONFIRM_EXIT").toBool() == true) {
            QMessageBox::StandardButton rc;
            rc = QMessageBox::question(this,
                                       app->appConstants->getQString("APPLICATION_NAME"),
                                       QString("Really quit ?\n"),
                                       QMessageBox::Yes | QMessageBox::No);
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
    registry.setValue("timezone", ui->cbxTimeZone->currentText());

    // Save MRU Files
    registry.beginWriteArray("MRUFiles");
    for (int i = 0; i < mruFiles.size(); ++i) {
        registry.setArrayIndex(i);
        registry.setValue("MRUFiles", mruFiles.at(i));
    }
    registry.endArray();

    // Show Help Panel or not
    registry.setValue("showHelp", ui->chkShowHelp->isChecked());

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

    const QByteArray windowState = registry.value("windowState", QByteArray()).toByteArray();
    if (!windowState.isEmpty()) {
        restoreState(registry.value("windowState").toByteArray());
    }

    const QByteArray splitter = registry.value("splitter", QByteArray()).toByteArray();
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
    // qDebug() << country;
    ui->cbxCountry->setCurrentText(country);
    const QString location = registry.value("location", "").toString();
    ui->txtLocation->setText(location);
    // qDebug() << location;
    const QString latitude = registry.value("latitude", "").toString();
    ui->txtLatitude->setText(latitude);
    // qDebug() << latitude;
    const QString longitude = registry.value("longitude", "").toString();
    ui->txtLongitude->setText(longitude);
    // qDebug() << longitude;
    const QString timezone = registry.value("timezone", "").toString();
    // qDebug() << timezone;
    ui->cbxTimeZone->setCurrentText(timezone);

    // MRU Files
    int size = registry.beginReadArray("MRUFiles");
    for (int i = 0; i < size; ++i) {
        registry.setArrayIndex(i);
        this->mruFiles.append(registry.value("MRUFiles").toString());
    }
    registry.endArray();
    this->updateMRUMenu();

    // Show Help Panel or not
    ui->chkShowHelp->setChecked(registry.value("showHelp").toBool());
    if (ui->chkShowHelp->isChecked()) {
        // Show Help
        this->showMessage("Help panel visible");
        this->ui->txtHelp->show();
    } else {
        // Hide Help
        this->showMessage("Help panel hidden");
        this->ui->txtHelp->hide();
    }
}

//******************************************************************************
// updateMRUMenu()
//******************************************************************************
void MainWindow::updateMRUMenu()
{
    for (int i = 0; i < this->mruFiles.size(); i++) {
        actMRUFiles[i]->setText(mruFiles[i].split("/").last());
        actMRUFiles[i]->setData(mruFiles[i]);
        actMRUFiles[i]->setVisible(true);
    }
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
    showMessage("Computing");
    this->meeus->refresh(ui->txtTime->dateTime());
    this->vb->Refresh();
}

//******************************************************************************
// notify()
//******************************************************************************
void MainWindow::notify(QString message, QString title)
{
    if (title == "*DEFAULT") {
        title = this->app->appConstants->getQString("APPLICATION_NAME");
    }
    // qDebug() << "NOTIFICATION";
#ifdef Q_OS_LINUX
    if (this->app->appSettings->get("APPLICATION_NOTIFICATION_SYSTEM").toBool() == true) {
        system(QString("notify-send \"%1\" \"%2\"").arg(title).arg(message).toStdString().c_str());
    } else {
        QMessageBox *mbox = new QMessageBox;
        mbox->setWindowTitle(title);
        mbox->setText(message);
        mbox->show();

        QSize sizePopup = mbox->frameSize();
        QScreen *screen = qApp->screens().at(0);
        int heightScreen = screen->availableGeometry().height();
        int widthScreen = screen->availableGeometry().width();
        mbox->move(widthScreen - sizePopup.width() - 10, heightScreen - sizePopup.height() - 10);

        QTimer::singleShot(this->app->appSettings->get("APPLICATION_NOTIFICATION_TIMEOUT").toInt(),
                           mbox,
                           SLOT(hide()));
    }
#else
    QMessageBox *mbox = new QMessageBox;
    mbox->setWindowTitle(title);
    mbox->setText(message);
    mbox->show();

    QSize sizePopup = mbox->frameSize();
    QScreen *screen = qApp->screens().at(0);
    int heightScreen = screen->availableGeometry().height();
    int widthScreen = screen->availableGeometry().width();
    mbox->move(widthScreen - sizePopup.width() - 10, heightScreen - sizePopup.height() - 10);

    QTimer::singleShot(this->app->appSettings->get("APPLICATION_NOTIFICATION_TIMEOUT").toInt(),
                       mbox,
                       SLOT(hide()));
#endif
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
// on_btnCompute_clicked()
//******************************************************************************
void MainWindow::on_btnCompute_clicked()
{
    this->refresh();
}

//******************************************************************************
// on_cbxCountry_currentTextChanged()
//******************************************************************************
void MainWindow::on_cbxCountry_currentTextChanged(const QString &arg1)
{
    QString country_idx;
    QSqlQuery query;
    query.prepare("SELECT country_idx FROM countries WHERE country = :country");
    query.bindValue(":country", arg1);
    // qDebug() << arg1;
    if (!query.exec()) {
        showMessage("Query failed!");
    } else {
        if (query.first()) { // get the first record in the result,
            country_idx = query.value("country_idx").toString();
            this->modelCities->setFilter("country_idx='" + country_idx + "'");
            // qDebug() << country_idx;
        } else {
            showMessage("Data not found");
        }
    }
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
                this->SetLocation();
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
// SetLocation()
//******************************************************************************
void MainWindow::SetLocation()
{
    Meeus::Location loc;
    loc.Country = ui->cbxCountry->currentText();
    loc.Name = ui->txtLocation->text();
    loc.Latitude = ui->txtLatitude->text().toDouble();
    loc.Longitude = ui->txtLongitude->text().toDouble();
    loc.TimeZone = ui->cbxTimeZone->currentText();
    meeus->SetLocation(loc);
}

//******************************************************************************
// openMRUFile()
//******************************************************************************
void MainWindow::openMRUFile()
{
    if (this->vbdModified) {
        QMessageBox::StandardButton rc;
        rc = QMessageBox::question(
            this,
            app->appConstants->getQString("APPLICATION_NAME"),
            QString("Current Varboard has been modified.\nDo you want to save it ?\n"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (rc == QMessageBox::Cancel) {
            showMessage("Cancel open");
            return;
        } else {
            if (rc == QMessageBox::Yes) {
                this->on_actionSave_triggered();
            }
        }
    }

    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString vbdName = action->data().toString();
        showMessage("Opening " + vbdName);
        delete this->vb;
        this->vb = new Varboard(app, this, ui);
        if (this->vb->LoadJSON(vbdName, meeus) == 0) {
            QFileInfo fi(vbdName);
            // this->lblFileName->setText("File : " + fi.fileName());
            this->vbdFileName = vbdName;
            this->vbdModified = false;
            this->displayFileName();
        } else {
            showMessage("File " + vbdName + " not found");
            // We have to recreate a board since the previous one was deleted
            this->vb->Clear();
            this->vb->addVarget("Date & Time", meeus, "VarDateTime");
            this->vb->addVarget("Location", meeus, "VarLocation");
            this->vb->addVarget("Latitude", meeus, "VarLatitude");
            this->vb->addVarget("Longitude", meeus, "VarLongitude");
            this->vb->addVarget("Julian Day", meeus, "VarJulianDay");
            this->vb->pack();
            this->vb->Refresh();
            this->lblFileName->setText("File : NEW");
            this->vbdFileName = "";
            this->vbdModified = true;
            this->displayFileName();
        }
    }
}

//******************************************************************************
// on_actionOpen_triggered()
//******************************************************************************
void MainWindow::on_actionOpen_triggered()
{
    if (this->vbdModified) {
        QMessageBox::StandardButton rc;
        rc = QMessageBox::question(
            this,
            app->appConstants->getQString("APPLICATION_NAME"),
            QString("Current Varboard has been modified.\nDo you want to save it ?\n"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (rc == QMessageBox::Cancel) {
            showMessage("Cancel open");
            return;
        } else {
            if (rc == QMessageBox::Yes) {
                this->on_actionSave_triggered();
            }
        }
    }

    QString vbdName = QFileDialog::getOpenFileName(this,
                                                   "Open a varboard...",
                                                   QDir::homePath(),
                                                   "Varboard (*.vbd | *.vbz)");
    if (!vbdName.isNull()) {
        showMessage("Opening " + vbdName);
        delete this->vb;
        this->vb = new Varboard(app, this, ui);
        if (this->vb->LoadJSON(vbdName, meeus) == 0) {
            QFileInfo fi(vbdName);
            this->lblFileName->setText("File : " + fi.fileName());
            this->vbdFileName = vbdName;
            this->vbdModified = false;
            this->displayFileName();
        } else {
            showMessage("File " + vbdName + " not found");
            // We have to recreate a board since the previous one was deleted
            this->vb->Clear();
            this->vb->addVarget("Date & Time", meeus, "VarDateTime");
            this->vb->addVarget("Location", meeus, "VarLocation");
            this->vb->addVarget("Latitude", meeus, "VarLatitude");
            this->vb->addVarget("Longitude", meeus, "VarLongitude");
            this->vb->addVarget("Julian Day", meeus, "VarJulianDay");
            this->vb->pack();
            this->vb->Refresh();
            this->lblFileName->setText("File : NEW");
            this->vbdFileName = "";
            this->vbdModified = true;
            this->displayFileName();
        }
    } else {
        showMessage("Cancelling open");
    }
}

//******************************************************************************
// on_btnAddVarget_clicked()
//******************************************************************************
void MainWindow::on_btnAddVarget_clicked()
{
    QTreeWidgetItem *item = ui->trwVargets->currentItem();
    if (item != NULL) {
        if (item->parent()) {
            this->showMessage("Adding Varget [" + item->text(0) + "] with label \""
                              + ui->txtVargetLabel->text() + "\"");
            this->vb->addVarget(ui->txtVargetLabel->text(), meeus, item->text(0));
            this->vb->Refresh();
            this->vbdModified = true;
            this->displayFileName();
        } else {
            this->showMessage("No Varget selected");
        }
    } else {
        this->showMessage("No Varget selected");
    }
}

//******************************************************************************
// on_trwVargets_itemClicked()
//******************************************************************************
void MainWindow::on_trwVargets_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent()) {
        // It's not a top-level item
        // ui->txtVargetLabel->setText(item->text(0));
        QString lblRaw = item->text(0);
        if (lblRaw.left(3) == "Var") {
            lblRaw.remove(0, 3);
        }
        QString lblNice;
        QStringList sl = lblRaw.split(QRegExp("(?=[A-Z])"), QString::SkipEmptyParts);
        lblNice = sl.join(" ");

        ui->txtVargetLabel->setText(lblNice);
        ui->txtVargetLabel->selectAll();
        QTimer::singleShot(0, ui->txtVargetLabel, SLOT(setFocus()));
    }
}

//******************************************************************************
// on_trwVargets_itemDoubleClicked()
//******************************************************************************
void MainWindow::on_trwVargets_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent()) {
        // Varget selected
        QString lblRaw = item->text(0);
        if (lblRaw.left(3) == "Var") {
            lblRaw.remove(0, 3);
        }
        QString lblNice;
        QStringList sl = lblRaw.split(QRegExp("(?=[A-Z])"), QString::SkipEmptyParts);
        lblNice = sl.join(" ");
        ui->txtVargetLabel->setText(lblNice);

        this->showMessage("Adding Varget [" + item->text(0) + "] with label \""
                          + ui->txtVargetLabel->text() + "\"");
        this->vb->addVarget(ui->txtVargetLabel->text(), meeus, item->text(0));
        this->vb->Refresh();
        ui->txtVargetLabel->setText("");
        this->vbdModified = true;
        this->displayFileName();
    } else {
        // Keyword selected
        QString keyword = item->text(0);
        // qDebug() << keyword;
        for (auto it = Varboard::aKeywords.keyValueBegin(); it != Varboard::aKeywords.keyValueEnd();
             ++it) {
            if (it->first == keyword) {
                // Add a label with the keyword's name
                this->vb->addVarget(keyword, meeus, NULL);
                this->vb->Refresh();
                // ui->txtVarboardLabel->setText("");
                showMessage("Label \"" + keyword + "\" added");

                // Loop the vargets list for this keyword
                for (const auto &i : it->second) {
                    QString lblRaw = i;
                    // qDebug() << i;
                    if (lblRaw.left(3) == "Var") {
                        lblRaw.remove(0, 3);
                    }
                    QString lblNice;
                    QStringList sl = lblRaw.split(QRegExp("(?=[A-Z])"), QString::SkipEmptyParts);
                    lblNice = sl.join(" ");
                    // qDebug() << lblNice;

                    this->showMessage("Adding Varget [" + i + "] with label \"" + lblNice + "\"");
                    this->vb->addVarget(lblNice, meeus, i);
                    this->vb->Refresh();
                }
                this->vbdModified = true;
                this->displayFileName();
            }
        }
        ui->txtVargetLabel->setText("");
    }
}

//******************************************************************************
// on_btnClearVarboard_clicked()
//******************************************************************************
void MainWindow::on_btnClearVarboard_clicked()
{
    // First, we have to disable the auto-refresh, if any
    ui->chkAutoRefresh->setCheckState(Qt::Unchecked);
    // Clear, delete and create a new one empty varboard
    this->vb->Clear();
    delete this->vb;
    this->vb = new Varboard(app, this, ui);
    this->lblNumberVargets->setText("Vargets : 0");
    this->vbdModified = true;
    this->displayFileName();
    showMessage("Varboard cleared");
}

//******************************************************************************
// on_actionSave_triggered()
//******************************************************************************
void MainWindow::on_actionSave_triggered()
{
    if (this->vbdFileName != "") {
        showMessage("Saving " + vbdFileName);
        QFileInfo fi2(vbdFileName);
        // this->setWindowTitle(this->appTitle + " - " + fi2.fileName());
        // this->vb->SaveFile(vbdFileName);
        this->lblFileName->setText("File : " + fi2.fileName());
        this->vb->SaveJSON(vbdFileName);
        this->vbdModified = false;
        this->displayFileName();
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
                                                   "Varboard (*.vbd | *.vbz)");
    if (!vbdName.isNull()) {
        // Check if extension is .vbd or .vbz
        QFileInfo fi1(vbdName);
        QString ext = fi1.suffix();
        if (ext != "vbd" && ext != "vbz") {
            vbdName += ".vbd";
        }
        // Save the file
        showMessage("Saving " + vbdName);
        QFileInfo fi2(vbdName);
        // this->setWindowTitle(this->appTitle + " - " + fi2.fileName());
        this->lblFileName->setText("File : " + fi2.fileName());
        // this->vb->SaveFile(vbdName);
        this->vb->SaveJSON(vbdName);
        this->vbdFileName = vbdName;
        this->vbdModified = false;
        this->displayFileName();
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
        this->vbdModified = true;
        this->displayFileName();
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
        this->vbdModified = true;
        this->displayFileName();
    } else {
        showMessage("Cannot set an empty title");
    }
}

//******************************************************************************
// displayFileName()
//******************************************************************************
void MainWindow::displayFileName()
{
    QFileInfo fi(this->vbdFileName);
    QString vbdName = fi.fileName();

    if (vbdModified) {
        this->lblFileName->setText("File : " + vbdName + " *modified*");
    } else {
        this->lblFileName->setText("File : " + vbdName);
    }
}

//******************************************************************************
// on_actionHelp_triggered()
//******************************************************************************
void MainWindow::on_actionHelp_triggered()
{
    QString fDoc = QDir(this->appDir).filePath("Astronomical_Algorithms_-_Jean_Meeus.pdf");
    // qDebug() << fDoc;
    if (!QFile::exists(fDoc)) {
        QFile::copy(":/dox/Astronomical Algorithms - Jean Meeus.pdf", fDoc);
    }
    QDesktopServices::openUrl(QUrl(QString(fDoc), QUrl::TolerantMode));
}

//******************************************************************************
// MainWindow::on_action_About_triggered()
//******************************************************************************
void MainWindow::on_action_About_triggered()
{
    ui->tabWidget->setCurrentIndex(3);
}

//******************************************************************************
// MainWindow::on_actionSettings_triggered()
//******************************************************************************
void MainWindow::on_actionSettings_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
}

//******************************************************************************
// MainWindow::on_btnTimeLocked_clicked()
//******************************************************************************
void MainWindow::on_btnTimeLocked_clicked()
{
    if (!this->TimeLocked) {
        // Locked => Fixed Time
        this->TimeLocked = true;
        this->ui->chkAutoRefresh->setEnabled(false);
        ui->txtTime->setReadOnly(false);
        // Stop the timer and set the current time
        this->tTime->stop();
        QDateTime date = QDateTime::currentDateTime();
        QString formattedTime = date.toString("dd/MM/yyyy hh:mm:ss");
        // ui->txtTime->setText(formattedTime);
        ui->txtTime->setDateTime(date);
        // Set Icon to Locked
        QPixmap pixmap(":/16x16/Lock.png");
        QIcon btnIcon(pixmap);
        ui->btnTimeLocked->setIcon(btnIcon);
        showMessage("Locking time to fixed time");
    } else {
        // Unlocked => Real Time
        this->TimeLocked = false;
        this->ui->chkAutoRefresh->setEnabled(true);
        ui->txtTime->setReadOnly(true);
        // Start the timer
        this->tTime->start();
        // Set Icon to Unlocked
        QPixmap pixmap(":/16x16/Lock Open.png");
        QIcon btnIcon(pixmap);
        ui->btnTimeLocked->setIcon(btnIcon);
        showMessage("Unlocking time to real time");
    }
}

//******************************************************************************
// on_chkAutoRefresh_stateChanged()
//******************************************************************************
void MainWindow::on_chkAutoRefresh_stateChanged(int arg1)
{
    if (arg1 == 0) {
        // Auto-Refresh Unchecked
        this->showMessage("Auto Refresh disabled");
        this->lblTitle->setStyleSheet("font-weight: bold; color: black; font-style: italic;");
    } else {
        // Auto-Refresh Checked
        this->showMessage("Auto Refresh enabled");
        this->lblTitle->setStyleSheet("font-weight: bold; color: #008000; font-style: italic;");
    }
}

//******************************************************************************
// on_chkShowHelp_stateChanged()
//******************************************************************************
void MainWindow::on_chkShowHelp_stateChanged(int arg1)
{
    if (arg1 == 0) {
        // Hide Help
        this->showMessage("Help panel hidden");
        this->ui->txtHelp->hide();
    } else {
        // Show Help
        this->showMessage("Help panel visible");
        this->ui->txtHelp->show();
    }
}

QMap<QString, callback_function> Varboard::aFunc
    = {{"VarDateTime", &Meeus::VarDateTime},
       {"VarJulianDay", &Meeus::VarJulianDay},
       {"VarT", &Meeus::VarT},
       {"VarDayOfWeek", &Meeus::VarDayOfWeek},
       {"VarLatitude", &Meeus::VarLatitude},
       {"VarLongitude", &Meeus::VarLongitude},
       {"VarLocation", &Meeus::VarLocation},
       {"VarCountry", &Meeus::VarCountry},
       {"VarTimeZone", &Meeus::VarTimeZone},
       {"VarSunMeanLongitude", &Meeus::VarSunMeanLongitude},
       {"VarSunMeanAnomaly", &Meeus::VarSunMeanAnomaly},
       {"VarSunCenter", &Meeus::VarSunCenter},
       {"VarSunTrueLongitude", &Meeus::VarSunTrueLongitude},
       {"VarSunTrueAnomaly", &Meeus::VarSunTrueAnomaly},
       {"VarSunApparentLongitude", &Meeus::VarSunApparentLongitude},
       {"VarSunRadiusVector", &Meeus::VarSunRadiusVector},
       {"VarSunNutationAberrationCorrection", &Meeus::VarSunNutationAberrationCorrection},
       {"VarMoonMeanLongitude", &Meeus::VarMoonMeanLongitude},
       {"VarMoonMeanAnomaly", &Meeus::VarMoonMeanAnomaly},
       {"VarMoonMeanElongation", &Meeus::VarMoonMeanElongation},
       {"VarMoonMeanDistanceFromAscendantNode", &Meeus::VarMoonMeanDistanceFromAscendantNode},
       {"VarMoonMeanLongitudeFromAscendantNode", &Meeus::VarMoonMeanLongitudeFromAscendantNode},
       {"VarEarthMeanEccentricity", &Meeus::VarEarthMeanEccentricity},
       {"VarEarthNutationLongitude", &Meeus::VarEarthNutationLongitude},
       {"VarEarthNutationObliquity", &Meeus::VarEarthNutationObliquity},
       {"VarEarthMeanObliquity", &Meeus::VarEarthMeanObliquity},
       {"VarEarthTrueObliquity", &Meeus::VarEarthTrueObliquity}};

QMap<QString, QStringList> Varboard::aKeywords
    = {{"Time", {"VarDateTime", "VarJulianDay", "VarT", "VarDayOfWeek"}},
       {"Location", {"VarLatitude", "VarLongitude", "VarLocation", "VarCountry", "VarTimeZone"}},
       {"Sun",
        {"VarSunMeanLongitude",
         "VarSunMeanAnomaly",
         "VarSunCenter",
         "VarSunTrueLongitude",
         "VarSunTrueAnomaly",
         "VarSunApparentLongitude",
         "VarSunRadiusVector",
         "VarSunNutationAberrationCorrection"}},
       {"Moon",
        {"VarMoonMeanLongitude",
         "VarMoonMeanAnomaly",
         "VarMoonMeanElongation",
         "VarMoonMeanDistanceFromAscendantNode",
         "VarMoonMeanLongitudeFromAscendantNode"}},
       {"Earth",
        {"VarEarthMeanEccentricity",
         "VarEarthNutationLongitude",
         "VarEarthNutationObliquity",
         "VarEarthMeanObliquity",
         "VarEarthTrueObliquity"}}};

//******************************************************************************
// Varget()
//******************************************************************************
Varget::Varget(
    App *a, int Order, QString Label, Meeus *m, QString Function, Varboard *vb, QWidget *parent)
    : QWidget{parent}
{
    this->locked = false;
    this->Order = Order;
    this->Label = Label;
    this->Function = Function;
    this->m = m;
    this->vb = vb;
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);
    QString o = QString::asprintf("%05d", Order);
    this->lblOrder = new QLabel(o);
    this->lblLabel = new QLabel(Label + " ");
    QFont *f = new QFont();
    f->setBold(true);
    this->lblLabel->setFont(*f);
    this->lblLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    hbox->addWidget(this->lblOrder);
    if (this->Function == NULL) { // Function is NULL for Labels
        // Add a dummy filler for Label's Vargets
        this->lblFiller = new QLabel("");
        hbox->addWidget(this->lblFiller);
    }
    hbox->addWidget(this->lblLabel);

    // Set CSS for highlighting and not highlighting
    // Did you know ? #FADA5E is called "Naples Yellow"
    this->cssHighlighted = "background-color : #FADA5E; color : black;";
    this->cssValueHighlighted
        = "background-color : #FFFDD0; color : black; border: 2px solid grey; font-weight: bold;";
    this->cssValue
        = "background-color : #F5F5F4; color : black; border: 2px solid grey; font-weight: normal;";

    this->cssOrderHighlighted = "background-color : #FADA5E; color : black; font-weight: normal;";
    this->cssOrderLockedHighlighted
        = "background-color : #FADA5E; color : black; font-weight: bold;";

    if (this->Function != NULL) { // Function is NULL for Labels
        QFont font("Monospace");
        txtValue = new QLineEdit();
        txtValue->setFont(font);
        txtValue->setReadOnly(true);
        txtValue->setStyleSheet(this->cssValue);
        txtValue->setFixedWidth(this->lblOrder->frameGeometry().width() / 2);
        hbox->addWidget(txtValue);
    }

    this->btnDelete = new QPushButton(
        this); // parent is specified to this, because we need to know the parent when clicked
    QPixmap pixmap1(":/16x16/Trash.png");
    QIcon ButtonIcon1(pixmap1);
    this->btnDelete->setFlat(true);
    this->btnDelete->setIcon(ButtonIcon1);
    this->btnDelete->setIconSize(pixmap1.rect().size());
    this->btnDelete->setFixedSize(QSize(18, 18));
    connect(this->btnDelete, SIGNAL(clicked()), this, SLOT(on_clicked_button_delete()));
    hbox->addWidget(this->btnDelete);

    this->btnUp = new QPushButton(
        this); // parent is specified to this, because we need to know the parent when clicked
    QPixmap pixmap2(":/16x16/Arrow2 - Up.png");
    QIcon ButtonIcon2(pixmap2);
    this->btnUp->setFlat(true);
    this->btnUp->setIcon(ButtonIcon2);
    this->btnUp->setIconSize(pixmap2.rect().size());
    this->btnUp->setFixedSize(QSize(18, 18));
    connect(this->btnUp, SIGNAL(clicked()), this, SLOT(on_clicked_button_up()));
    hbox->addWidget(this->btnUp);

    this->btnDown = new QPushButton(
        this); // parent is specified to this, because we need to know the parent when clicked
    QPixmap pixmap3(":/16x16/Arrow2 - Down.png");
    QIcon ButtonIcon3(pixmap3);
    this->btnDown->setFlat(true);
    this->btnDown->setIcon(ButtonIcon3);
    this->btnDown->setIconSize(pixmap3.rect().size());
    this->btnDown->setFixedSize(QSize(18, 18));
    connect(this->btnDown, SIGNAL(clicked()), this, SLOT(on_clicked_button_down()));
    hbox->addWidget(this->btnDown);

    this->setLayout(hbox);
    this->Refresh();
}

//******************************************************************************
// enterEvent()
//******************************************************************************
void Varget::enterEvent(QEvent *event)
{
    if (this->locked) {
        this->lblOrder->setStyleSheet(this->cssOrderLockedHighlighted);
    } else {
        this->lblOrder->setStyleSheet(this->cssOrderHighlighted);
    }
    this->lblLabel->setStyleSheet(this->cssHighlighted);
    if (this->Function == NULL) {
        this->lblFiller->setStyleSheet(this->cssHighlighted);
    } else {
        this->txtValue->setStyleSheet(this->cssValueHighlighted);
        bool gLocked(false);
        bool pLocked = this->locked;
        this->locked = false;
        for (int i = 0; i < this->vb->vargets.size(); ++i) {
            gLocked = gLocked || this->vb->vargets[i]->locked;
        }
        this->locked = pLocked;
        if (!gLocked)
            this->ShowHelp();
    }
}

//******************************************************************************
// leaveEvent()
//******************************************************************************
void Varget::leaveEvent(QEvent *event)
{
    this->lblLabel->setStyleSheet(this->css);
    this->lblOrder->setStyleSheet(this->cssOrder);
    // qDebug() << this->cssOrder;
    if (this->Function == NULL) {
        this->lblFiller->setStyleSheet(this->css);
    } else {
        this->txtValue->setStyleSheet(this->cssValue);
    }
}

//******************************************************************************
// mousePressEvent()
//******************************************************************************
void Varget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->locked = !this->locked;
        if (this->locked) {
            // we have to unlock all the other Vargets, because we can have only one Varget locked at a time
            for (int i = 0; i < this->vb->vargets.size(); ++i) {
                this->vb->vargets[i]->locked = false;
                this->vb->vargets[i]->cssOrder.replace("bold", "normal");
                this->vb->vargets[i]->lblOrder->setStyleSheet(this->vb->vargets[i]->cssOrder);
            }
            // don't forget to relock this Varget
            this->locked = true;
            this->ShowHelp();
        }
    }
    if (this->locked) {
        this->cssOrder.replace("normal", "bold");
        this->lblOrder->setStyleSheet(this->cssOrderLockedHighlighted);
    } else {
        this->cssOrder.replace("bold", "normal");
        this->lblOrder->setStyleSheet(this->cssOrderHighlighted);
    }
}

//******************************************************************************
// Refresh()
//******************************************************************************
void Varget::Refresh()
{
    if (this->Function != NULL) { // Function is NULL for Labels
        this->compute();
        qDebug() << "Refresh Varget : " + this->Value.value("FormattedValue").toString();
        this->txtValue->setText(this->Value.value("FormattedValue").toString());
        this->txtValue->setToolTip(this->Value.value("Value").toString());
    }
    this->lblOrder->setText(QString::asprintf("%05d", this->Order));
}

//******************************************************************************
// ShowHelp()
//******************************************************************************
void Varget::ShowHelp()
{
    QString mdHelp;
    if (this->Value.value("Text").toString() != "") {
        mdHelp = "# " + this->Value.value("Name").toString()
                 + " :: " + this->Value.value("Text").toString() + "\n";
        mdHelp += "---\n";
        mdHelp += "- Raw Value : **" + this->Value.value("Value").toString() + "**\n";
        mdHelp += "- Formatted Value : **"
                  + this->Value.value("FormattedValue").toString().trimmed() + "**\n";
        mdHelp += "---\n\n";

        // Try to open the Help file embedded into the resource file
        QFile mdf(this->Value.value("HelpFile").toString());
        if (mdf.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&mdf);
            QString txt = in.readAll();
            mdHelp += txt;
            mdf.close();
        }
    } else {
        mdHelp = "*None*";
    }
    this->vb->ui->txtHelp->setMarkdown(mdHelp);
}

//******************************************************************************
// compute()
//******************************************************************************
void Varget::compute()
{
    callback_function pFunc;
    pFunc = Varboard::aFunc[this->Function];
    this->Value = (m->*pFunc)();
    qDebug() << this->Value;
}

//******************************************************************************
// on_clicked_button_down()
//******************************************************************************
void Varget::on_clicked_button_down()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    Varget *vg = (Varget *) btn->parent();
    int current = vg->Order - 1;
    Varboard *vb = vg->vb;
    vb->mw->showMessage("Moving down varget at line #" + QString::number(current + 1));
    vb->vargets[current]->Order = vb->vargets[current]->Order + 1;
    vb->vargets[current + 1]->Order = vb->vargets[current + 1]->Order - 1;
    std::swap(vb->vargets[current], vb->vargets[current + 1]);

    vb->Refresh();
    vb->mw->vbdModified = true;
    vb->mw->displayFileName();
}

//******************************************************************************
// on_clicked_button_up()
//******************************************************************************
void Varget::on_clicked_button_up()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    Varget *vg = (Varget *) btn->parent();
    int current = vg->Order - 1;
    Varboard *vb = vg->vb;
    vb->mw->showMessage("Moving up varget at line #" + QString::number(current + 1));
    vb->vargets[current]->Order = vb->vargets[current]->Order - 1;
    vb->vargets[current - 1]->Order = vb->vargets[current - 1]->Order + 1;
    std::swap(vb->vargets[current], vb->vargets[current - 1]);

    vb->Refresh();
    vb->mw->vbdModified = true;
    vb->mw->displayFileName();
}

//******************************************************************************
// on_clicked_button_delete()
//******************************************************************************
void Varget::on_clicked_button_delete()
{
    // Which button was clicked ?
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    // Get the parent's varget of the clicked button
    Varget *vg = (Varget *) btn->parent();
    // Get the order of this varget
    int current = vg->Order - 1;
    // Get the Varboard's owner of this varget
    Varboard *vb = vg->vb;
    // The Varboard has a reference to the MainWindow, so let's display some blahblah
    vb->mw->showMessage("Deleting varget at line #" + QString::number(current + 1));
    // Compute New Order (but I prefer Joy Division) for vargets below the varget deleted
    for (int i = current + 1; i < vb->vargets.size(); ++i) {
        vb->vargets[i]->Order = vb->vargets[i]->Order - 1;
    }
    // Remove the varget from the Varboad's vargets list
    vb->vargets.removeAt(current);
    // and don't forget to delete it
    delete vg;
    // Redisplay the modified Varboard, if not empty
    if (vb->vargets.size() != 0) {
        vb->Refresh();
    } else {
        vb->mw->lblNumberVargets->setText("Vargets : 0");
    }
    vb->mw->vbdModified = true;
    vb->mw->displayFileName();
}

//******************************************************************************
// Varboard()
//******************************************************************************
Varboard::Varboard(App *a, MainWindow *mw, Ui::MainWindow *ui)
{
    this->a = a;
    this->ui = ui;
    this->mw = mw;
}

//******************************************************************************
// addVarget()
//******************************************************************************
int Varboard::addVarget(QString Label, Meeus *m, QString Function, QWidget *parent)
{
    int i = this->vargets.count() + 1;
    Varget *v = new Varget(this->a, i, Label, m, Function, this, parent);
    this->vargets.append(v);
    return i;
}

//******************************************************************************
// pack()
//******************************************************************************
void Varboard::pack()
{
    // Remove any previous QSpacerItem
    for (int i = 0; i < ui->boardLayout->count(); ++i) {
        QLayoutItem *layoutItem = ui->boardLayout->itemAt(i);
        if (layoutItem->spacerItem()) {
            ui->boardLayout->removeItem(layoutItem);
            delete layoutItem;
            --i;
        }
    }
    // Finally, add the QSpacerItem to pack (Shakur...)
    this->ui->boardLayout->addItem(
        new QSpacerItem(0, 1000, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

//******************************************************************************
// Refresh()
//******************************************************************************
void Varboard::Refresh()
{
    // qDebug() << this->vargets.size();
    for (int i = 0; i < this->vargets.size(); ++i) {
        this->ui->boardLayout->addWidget(vargets[i]);
        if (i % 2 == 0) {
            this->vargets[i]->css = "background-color : "
                                    + a->appSettings->get("VARBOARD_COLOR_LINE_1").toString()
                                    + "; color : black;";
            if (this->vargets[i]->locked) {
                this->vargets[i]->cssOrder = "background-color : "
                                             + a->appSettings->get("VARBOARD_COLOR_LINE_1").toString()
                                             + "; color : black; font-weight: bold;";
            } else {
                this->vargets[i]->cssOrder = "background-color : "
                                             + a->appSettings->get("VARBOARD_COLOR_LINE_1").toString()
                                             + "; color : black; font-weight: normal;";
            }
        } else {
            this->vargets[i]->css = "background-color : "
                                    + a->appSettings->get("VARBOARD_COLOR_LINE_2").toString()
                                    + "; color : black;";
            if (this->vargets[i]->locked) {
                this->vargets[i]->cssOrder = "background-color : "
                                             + a->appSettings->get("VARBOARD_COLOR_LINE_2").toString()
                                             + "; color : black; font-weight: bold;";
            } else {
                this->vargets[i]->cssOrder = "background-color : "
                                             + a->appSettings->get("VARBOARD_COLOR_LINE_2").toString()
                                             + "; color : black; font-weight: normal;";
            }
        }
        this->vargets[i]->btnUp->setEnabled(true);
        this->vargets[i]->btnDown->setEnabled(true);
        this->vargets[i]->setStyleSheet(this->vargets[i]->css);
        this->vargets[i]->lblOrder->setStyleSheet(this->vargets[i]->cssOrder);
        this->vargets[i]->Refresh();
    }
    this->pack();
    // Disable the first UP button and the last DOWN button
    this->vargets[0]->btnUp->setEnabled(false);
    this->vargets[this->vargets.size() - 1]->btnDown->setEnabled(false);
    //
    QString s = QString::asprintf("Vargets : %d", this->vargets.size());
    this->mw->lblNumberVargets->setText(s);
    // Set the focus on the dashboard tab
    this->ui->tabWidget->setCurrentWidget(this->ui->tabDashboard);
}

//******************************************************************************
// SaveJSON()
//******************************************************************************
int Varboard::SaveJSON(QString name)
{
    int rc = 0;
    QJsonObject root;
    root.insert("title", this->ui->txtTitle->text());

    QJsonObject location;
    location.insert("country", ui->cbxCountry->currentText());
    location.insert("name", ui->txtLocation->text());
    location.insert("latitude", ui->txtLatitude->text());
    location.insert("longitude", ui->txtLongitude->text());
    location.insert("timezone", ui->cbxTimeZone->currentText());
    root.insert("location", location);

    QJsonObject timing;
    timing.insert("time", ui->txtTime->dateTime().toString("yyyy/MM/dd hh:mm:ss"));
    if (this->mw->TimeLocked) {
        timing.insert("refresh", "fixed");
    } else {
        timing.insert("refresh", "running");
    }
    root.insert("time", timing);

    QJsonArray varboard;
    for (int i = 0; i < this->vargets.size(); ++i) {
        QJsonObject varget;
        varget.insert("label", this->vargets[i]->Label);
        varget.insert("function", this->vargets[i]->Function);
        varboard.push_back(varget);
    }
    root.insert("varboard", varboard);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(root);

    QFile fJSON(name);
    if (fJSON.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QByteArray uncompressedData = jsonDoc.toJson();
        QByteArray compressedData = qCompress(uncompressedData, 9);
        QFileInfo fi1(name);
        QString ext = fi1.suffix();
        if (ext == "vbz") {
            fJSON.write(compressedData);
        } else {
            fJSON.write(uncompressedData);
        }
        fJSON.close();
    } else {
        rc = 1;
    }
    return rc;
}

//******************************************************************************
// LoadJSON()
//******************************************************************************
int Varboard::LoadJSON(QString name, Meeus *m)
{
    int rc = 0;
    QFile file(name);

    // Do we need to save the previous Varboard
    // Parse the JSON file
    if (file.open(QIODevice::ReadOnly)) {
        // Add it to MRU
        bool found = false;
        for (const auto &i : this->mw->mruFiles) {
            if (name == i) {
                found = true;
            }
        }
        if (!found) {
            this->mw->mruFiles.append(name);
            if (this->mw->mruFiles.size() > mw->app->appConstants->getInt("MRU_FILES")) {
                this->mw->mruFiles.removeAt(0);
            }
        }
        this->mw->updateMRUMenu();

        QFileInfo fi1(name);
        QString ext = fi1.suffix();
        QByteArray data;
        if (ext == "vbz") {
            data = qUncompress(file.readAll());
        } else {
            data = file.readAll();
        }
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject root = jsonDoc.object();

        this->Clear();
        this->ui->txtTitle->setText(root.value("title").toString());

        QJsonObject location = root.value("location").toObject();
        this->ui->cbxCountry->setCurrentText(location.value("country").toString());
        this->ui->txtLocation->setText(location.value("name").toString());
        this->ui->txtLatitude->setText(location.value("latitude").toString());
        this->ui->txtLongitude->setText(location.value("longitude").toString());
        this->ui->cbxTimeZone->setCurrentText(location.value("timezone").toString());
        this->mw->SetLocation();

        QJsonObject timing = root.value("time").toObject();
        if (timing.value("refresh").toString() == "fixed") {
            // Locked => Fixed Time
            this->mw->TimeLocked = true;
            ui->txtTime->setReadOnly(false);
            ui->chkAutoRefresh->setEnabled(false);
            // Stop the timer and set the current time
            this->mw->tTime->stop();
            this->ui->txtTime->setDateTime(
                QDateTime::fromString(timing.value("time").toString(), "yyyy/MM/dd hh:mm:ss"));
            // Set Icon to Locked
            QPixmap pixmap(":/16x16/Lock.png");
            QIcon btnIcon(pixmap);
            ui->btnTimeLocked->setIcon(btnIcon);
        } else {
            // Unlocked => Real Time
            this->mw->TimeLocked = false;
            ui->txtTime->setReadOnly(true);
            ui->chkAutoRefresh->setEnabled(true);
            // Start the timer
            this->mw->tTime->start();
            // Set Icon to Unlocked
            QPixmap pixmap(":/16x16/Lock Open.png");
            QIcon btnIcon(pixmap);
            ui->btnTimeLocked->setIcon(btnIcon);
        }

        QJsonArray varboard = root.value("varboard").toArray();
        for (auto i = 0; i < varboard.size(); i++) {
            QJsonObject varget = varboard.at(i).toObject();
            this->addVarget(varget.value("label").toString(),
                            m,
                            varget.value("function").toString());
        }
        file.close();
        this->mw->meeus->refresh(ui->txtTime->dateTime());
        this->Refresh();
        this->mw->lblFileName->setToolTip(name);
    } else {
        rc = 1;
    }
    return rc;
}

//******************************************************************************
// Clear()
//******************************************************************************
void Varboard::Clear()
{
    clearLayout(ui->boardLayout);
}

//******************************************************************************
// clearLayout()
//******************************************************************************
void clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        if (child->layout() != 0)
            clearLayout(child->layout());
        else if (child->widget() != 0)
            delete child->widget();

        delete child;
    }
}
