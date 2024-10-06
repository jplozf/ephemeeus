#include "settings.h"
#include "MainWindow.h"

//******************************************************************************
// Settings()
//******************************************************************************
Settings::Settings() {
  // Set  the defaults values...
#ifdef Q_OS_LINUX
#else
#endif
  defaults["APPLICATION_CONFIRM_EXIT"] = QVariant(true);
  defaults["APPLICATION_THEME"] =
      QVariant("LIGHT");  // DARK, LIGHT or ALTERNATE
  defaults["APPLICATION_STATUSBAR_TIMEOUT"] = QVariant(3000);
  defaults["APPLICATION_SHOW_DOC"] = QVariant(false);
  defaults["APPLICATION_NOTIFICATION_SYSTEM"] = QVariant(false);
  defaults["APPLICATION_NOTIFICATION_TIMEOUT"] = QVariant(3000);

  defaults["THEME_WINDOW"] = QVariant("#efefef");
  defaults["THEME_WINDOW_TEXT"] = QVariant("#000000");
  defaults["THEME_BASE"] = QVariant("#ffffff");
  defaults["THEME_ALTERNATE_BASE"] = QVariant("#f7f7f7");
  defaults["THEME_TOOLTIP_BASE"] = QVariant("#ffffdc");
  defaults["THEME_TOOLTIP_TEXT"] = QVariant("#000000");
  defaults["THEME_TEXT"] = QVariant("#000000");
  defaults["THEME_BUTTON"] = QVariant("#efefef");
  defaults["THEME_BUTTON_TEXT"] = QVariant("#000000");
  defaults["THEME_BRIGHT_TEXT"] = QVariant("#ffffff");
  defaults["THEME_LINK"] = QVariant("#0000ff");
  defaults["THEME_HIGHLIGHT"] = QVariant("#308cc6");
  defaults["THEME_HIGHLIGHTED_TEXT"] = QVariant("#ffffff");

  defaults["DEFAULT_LOCATION_COUNTRY"] = QVariant("France");
  defaults["DEFAULT_LOCATION_NAME"] = QVariant("Ozoir-la-Ferrière");
  defaults["DEFAULT_LOCATION_LATITUDE"] = QVariant(48.778056);
  defaults["DEFAULT_LOCATION_LONGITUDE"] = QVariant(2.68);

  defaults["VARBOARD_COLOR_LINE_1"] = QVariant("#ccdee2");
  defaults["VARBOARD_COLOR_LINE_2"] = QVariant("#b3b8bf");
  defaults["VARBOARD_SHOW_HELP"] = QVariant(true);

  // Read the settings from user's settings
  read();

  // Check if all defaults settings are set and set them if any
  foreach (const auto& defaultKey, defaults.keys()) {
    if (!settings.contains(defaultKey)) {
      settings[defaultKey] = defaults[defaultKey];
    }
  }

  // Delete all keys that are no more in the defaults settings values
  foreach (const auto& settingKey, settings.keys()) {
    if (!defaults.contains(settingKey)) {
      settings.erase(settings.find(settingKey));
    }
  }

  // Save the settings to user's settings
  write();
}

//******************************************************************************
// get()
//******************************************************************************
QVariant Settings::get(QString param) {
  return this->settings[param];
}

//******************************************************************************
// write()
//******************************************************************************
void Settings::write() {
  // TODO : Apply new settings in real time
  Constants* appConstants = new Constants();
  QDir appDir =
      QDir(QDir::homePath()).filePath(appConstants->getQString("APP_FOLDER"));
  QFile fSettings(
      QDir(appDir).filePath(appConstants->getQString("SETTINGS_FILE")));
  if (fSettings.open(QIODevice::WriteOnly)) {
    QDataStream out(&fSettings);
    out.setVersion(QDataStream::Qt_5_3);
    out << settings;
  }
}

//******************************************************************************
// read()
//******************************************************************************
void Settings::read() {
  Constants* appConstants = new Constants();
  QDir appDir =
      QDir(QDir::homePath()).filePath(appConstants->getQString("APP_FOLDER"));
  QFile fSettings(
      QDir(appDir).filePath(appConstants->getQString("SETTINGS_FILE")));
  if (fSettings.open(QIODevice::ReadOnly)) {
    QDataStream in(&fSettings);
    in.setVersion(QDataStream::Qt_5_3);
    in >> settings;
  }
}

//******************************************************************************
// form()
//******************************************************************************
void Settings::form(MainWindow* w) {
  QFormLayout* form = new QFormLayout(w->ui->boxSettings);
  form->setLabelAlignment(Qt::AlignRight);
  QString previousKeyword;
  for (auto e : settings.keys()) {
    QString currentKeyword = e.section("_", 0, 0);
    if (currentKeyword != previousKeyword) {
      previousKeyword = currentKeyword;
      QLabel* lblKeyword = new QLabel("▸ " + currentKeyword);
      lblKeyword->setStyleSheet("font-weight: bold;");
      form->addRow(lblKeyword);
    }
    QLabel* lblSetting = new QLabel(e);
    QLineEdit* txtSetting = new QLineEdit(settings.value(e).toString());
    connect(txtSetting, &QLineEdit::returnPressed, [=] {
        handleTextChanged(w, lblSetting, txtSetting);
    });
    form->addRow(lblSetting, txtSetting);
  }
  w->setLayout(form);
}

//******************************************************************************
// handleTextChanged()
//******************************************************************************
void Settings::handleTextChanged(MainWindow* w, QLabel* lbl, QLineEdit* txt) {
    QString param = lbl->text().toLatin1();
    QString oldValue = settings[lbl->text().toLatin1()].toString();
    QString newValue = txt->text().toLatin1();
    settings[param] = QVariant(newValue);
    write();
    w->setTheme();
    w->showMessage(QString("Setting \"%1\" updated with value \"%2\", previous value was \"%3\"")
                       .arg(param)
                       .arg(newValue)
                       .arg(oldValue));
    w->notify("Settings updated, application may need to be restarted");
}
