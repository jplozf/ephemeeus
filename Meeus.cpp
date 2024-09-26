#include "Meeus.h"

//******************************************************************************
// Meeus()
//******************************************************************************
Meeus::Meeus(Location location, QDateTime dt, QTimeZone tz, int time_mode) {
  this->location = location;
  this->dt = dt;
  this->tz = tz;
  this->time_mode = time_mode;
}

//******************************************************************************
// ~Meeus()
//******************************************************************************
Meeus::~Meeus() {}

//******************************************************************************
// ComputeJD()
//******************************************************************************
void Meeus::ComputeJD() {
    this->JD = this->Date2JD(this->dt);
}

//******************************************************************************
// VarJD()
//******************************************************************************
QString Meeus::VarJD()
{
    this->ComputeJD();
    return QString::number(this->JD, 'f', 6);
}

//******************************************************************************
// VarDayOfWeek()
//******************************************************************************
QString Meeus::VarDayOfWeek()
{
    int dow = this->DayOfWeek(this->JD);
    QString days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[dow];
}

//******************************************************************************
// VarDateTime()
//******************************************************************************
QString Meeus::VarDateTime()
{
    return this->dt.toString();
}

//******************************************************************************
// VarLocation()
//******************************************************************************
QString Meeus::VarLocation()
{
    return this->location.Name;
}

//******************************************************************************
// VarLatitude()
//******************************************************************************
QString Meeus::VarLatitude()
{
    auto dms = DD2DMS(this->location.Latitude);
    QString lat
        = QString("%1°%2'%3\"").arg(std::get<0>(dms)).arg(std::get<1>(dms)).arg(std::get<2>(dms));
    return lat;
}

//******************************************************************************
// VarLongitude()
//******************************************************************************
QString Meeus::VarLongitude()
{
    auto dms = DD2DMS(this->location.Longitude);
    QString lon
        = QString("%1°%2'%3\"").arg(std::get<0>(dms)).arg(std::get<1>(dms)).arg(std::get<2>(dms));
    return lon;
}

//******************************************************************************
// Date2JD()
//******************************************************************************
double Meeus::Date2JD(QDateTime dt)
{
    int d = dt.date().day();
    int m = dt.date().month();
    int y = dt.date().year();
    int h = dt.time().hour();
    int n = dt.time().minute();
    int s = dt.time().second();
    double dd = DHMS2DD(d, h, n, s);

    if (m <= 2) {
        y--;
        m = m + 12;
    }

    double a = floor(y / 100);
    double b = 2 - a + floor(a / 4);
    double JD = floor(365.25 * (y + 4716)) + floor(30.6001 * (m + 1)) + dd + b - 1524.5;
    return JD;
}

//******************************************************************************
// JD2Date()
//******************************************************************************
QDateTime Meeus::JD2Date(double JD)
{
    double JJ = JD + 0.5;
    double Z = floor(JJ);
    //  double F = JJ - floor(JJ);
    double F = frac(JJ);
    double A = Z;
    if (Z >= 2299161.0) {
        double a = floor((Z - 1867216.25) / 36524.25);
        A = Z + 1.0 + a - floor(a / 4.0);
    }
    double B = A + 1524.0;
    double C = floor((B - 122.1) / 365.25);
    double D = floor(C * 365.25);
    double E = floor((B - D) / 30.6001);
    double day = B - D - floor(30.6001 * E) + F; // This is the day with decimals
    auto dhms = DD2DHMS(day);
    int qd = std::get<0>(dhms);
    int qh = std::get<1>(dhms);
    int qn = std::get<2>(dhms);
    int qs = std::get<3>(dhms);
    int qm = (int) (E - 13.0);
    if (E < 14.0) {
        qm = (int) (E - 1.0);
    }
    int qy = (int) (C - 4715.0);
    if (qm > 2) {
        qy = (int) (C - 4716.0);
    }
    QDateTime qdate(QDate(qy, qm, qd), QTime(qh, qn, qs));
    return qdate;
}

//******************************************************************************
// DayOfWeek()
//******************************************************************************
int Meeus::DayOfWeek(double JD)
{
    int dow = (int) (JD + 1.5) % 7;
    return dow;
}

//******************************************************************************
// SetDefaultLocation()
//******************************************************************************
void Meeus::SetDefaultLocation() {
  Location loc;
  loc.Name = "Ozoir-la-Ferrière (FR)";
  loc.Latitude = 48.778056;
  loc.Longitude = 2.68;
  this->location = loc;
}

//******************************************************************************
// SetLocation()
//******************************************************************************
void Meeus::SetLocation(Location loc)
{
    this->location = loc;
}

//******************************************************************************
// getDay()
//******************************************************************************
int Meeus::getDay() {
  return this->dt.date().day();
}

//******************************************************************************
// getMonth()
//******************************************************************************
int Meeus::getMonth() {
  return this->dt.date().month();
}

//******************************************************************************
// getYear()
//******************************************************************************
int Meeus::getYear() {
  return this->dt.date().year();
}

//******************************************************************************
// getHour()
//******************************************************************************
int Meeus::getHour() {
  return this->dt.time().hour();
}

//******************************************************************************
// getMinute()
//******************************************************************************
int Meeus::getMinute() {
  return this->dt.time().minute();
}

//******************************************************************************
// getSecond()
//******************************************************************************
int Meeus::getSecond() {
  return this->dt.time().second();
}

//******************************************************************************
// init()
//******************************************************************************
void Meeus::init() {
  this->refresh();
}

//******************************************************************************
// refresh()
//******************************************************************************
void Meeus::refresh()
{
    if (this->time_mode == Meeus::TIME_MODE_REAL) {
        this->dt = QDateTime::currentDateTime();
    }
    this->ComputeJD();
}

//******************************************************************************
// getDateTime()
//******************************************************************************
QString Meeus::getDateTime()
{
    return this->dt.toString();
}

//******************************************************************************
// getLocation()
//******************************************************************************
QString Meeus::getLocation()
{
    return this->location.Name;
}

//******************************************************************************
//
// Misc General Purpose Functions defined outside the Class
// (Why ? I told you : there are General Purpose Functions)
//
//******************************************************************************

//******************************************************************************
// frac()
//******************************************************************************
double frac(double d)
{
    return (floor(abs(d)) - abs(d));
}

//******************************************************************************
// DHMS2DD()
// Warning : This is a conversion from DAYS, HOURS, MINUTES, SECONDS to DECIMAL DAYS
//******************************************************************************
double DHMS2DD(int d, int h, int m, int s)
{
    double dd = d + (h / 24.0) + (m / 1440.0) + (s / 86400.0);
    return dd;
}

//******************************************************************************
// DD2DHMS() => tuple{ d, h, m, s }
// Warning : This is a conversion from DECIMAL DAYS to DAYS, HOURS, MINUTES, SECONDS
//******************************************************************************
std::tuple<int, int, int, int> DD2DHMS(double dd)
{
    double sign = 1;
    if (dd < 0) {
        dd = abs(dd);
        sign = -1;
    }

    double fd = floor(dd);      // Full Day
    double dh = (dd - fd) * 24; // Double Hour
    double fh = floor(dh);      // Full Hour
    double dm = (dh - fh) * 60; // Double Minute
    double fm = floor(dm);      // Full Minute
    double ds = (dm - fm) * 60; // Double Second
    double fs = floor(ds);      // Full Second
    return std::make_tuple((int) (fd * sign), (int) fh, (int) fm, (int) fs);
}

//******************************************************************************
// DMS2DD()
// Warning : This is a conversion from DEGREES, MINUTES, SECONDS to DECIMAL DEGREES
//******************************************************************************
double DMS2DD(int d, int m, int s)
{
    double dd = d + (m / 60.0) + (s / 3600.0);
    return dd;
}

//******************************************************************************
// DD2DMS() => tuple{ d, m, s }
// Warning : This is a conversion from DECIMAL DEGREES to DEGREES, MINUTES, SECONDS
//******************************************************************************
std::tuple<int, int, int> DD2DMS(double dd)
{
    double sign = 1;
    if (dd < 0) {
        dd = abs(dd);
        sign = -1;
    }

    double fd = floor(dd);      // Full Degrees
    double dm = (dd - fd) * 60; // Double Minute
    double fm = floor(dm);      // Full Minute
    double ds = (dm - fm) * 60; // Double Second
    double fs = floor(ds);      // Full Second
    return std::make_tuple((int) (fd * sign), (int) fm, (int) fs);
}
