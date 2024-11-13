//******************************************************************************
//             _
//     ___ ___| |_ ___ _____ ___ ___ _ _ ___
//    | -_| . |   | -_|     | -_| -_| | |_ -|
//    |___|  _|_|_|___|_|_|_|___|___|___|___|
//        |_|
//                   (C) JPL 2024
//
//********************;**********************************************************
#include "Meeus.h"

//******************************************************************************
// Meeus::Meeus()
//******************************************************************************
Meeus::Meeus(Location location, QDateTime dt, QTimeZone tz, int time_mode) {
  this->location = location;
  this->dt = dt;
  this->tz = tz;
  this->time_mode = time_mode;
}

//******************************************************************************
// Meeus::~Meeus()
//******************************************************************************
Meeus::~Meeus() {}

//******************************************************************************
// Meeus::ComputeJD()
//******************************************************************************
void Meeus::ComputeJD() {
    this->JD = this->Date2JD(this->dt);
}

//******************************************************************************
// Meeus::VarJulianDay()
//******************************************************************************
mVarget Meeus::VarJulianDay()
{
    this->ComputeJD();
    mVarget rc{{"Name", "VarJulianDay"},
               {"Text", "Julian Day"},
               {"Value", this->JD},
               {"FormattedValue", QString::number(this->JD, 'f', 6)},
               {"Page", 67},
               {"HelpFile", ":/dox/en/julian-day.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarT()
//******************************************************************************
mVarget Meeus::VarT()
{
    this->ComputeJD();
    double T = (JD - 2451545.0) / 36525.0;
    mVarget rc{{"Name", "VarT"},
               {"Text", "Julian Centuries T"},
               {"Value", T},
               {"FormattedValue", QString::number(T, 'f', 9)},
               {"Page", 95},
               {"HelpFile", ":/dox/en/t2000.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarDayOfWeek()
//******************************************************************************
mVarget Meeus::VarDayOfWeek()
{
    int dow = this->DayOfWeek(this->JD);
    QString days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    mVarget rc{{"Name", "VarDayOfWeek"},
               {"Text", "Day of Week"},
               {"Value", dow},
               {"FormattedValue", days[dow]},
               {"Page", 73},
               {"HelpFile", ":/dox/en/day-of-week.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarDateTime()
//******************************************************************************
mVarget Meeus::VarDateTime()
{
    mVarget rc{{"Name", "VarDateTime"},
               {"Text", "Date and Time"},
               {"Value", this->dt.toString()},
               {"FormattedValue", this->dt.toString()},
               {"HelpFile", ":/dox/en/date-time.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarGreenwichMeanSideralTime()
//******************************************************************************
mVarget Meeus::VarGreenwichMeanSideralTime()
{
    double gmst = GreenwichMeanSideralTime(this->JD);
    mVarget rc{{"Name", "VarGreenwichMeanSideralTime"},
               {"Text", "Greenwich Mean Sideral Time"},
               {"Value", gmst},
               {"FormattedValue", printDMS(gmst)},
               {"AlternateFormat", printHMS(gmst / 15.0)},
               {"HelpFile", ":/dox/en/greenwich-mean-sideral-time.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarCountry()
//******************************************************************************
mVarget Meeus::VarCountry()
{
    mVarget rc{{"Name", "VarCountry"},
               {"Text", "Country"},
               {"Value", this->location.Country},
               {"FormattedValue", this->location.Country},
               {"HelpFile", ":/dox/en/country.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarLocation()
//******************************************************************************
mVarget Meeus::VarLocation()
{
    mVarget rc{{"Name", "VarLocation"},
               {"Text", "Location"},
               {"Value", this->location.Name},
               {"FormattedValue", this->location.Name},
               {"HelpFile", ":/dox/en/location.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarTimeZone()
//******************************************************************************
mVarget Meeus::VarTimeZone()
{
    qDebug() << this->location.tz.id();
    qDebug() << this->location.tz.standardTimeOffset(QDateTime::currentDateTime());
    mVarget rc{{"Name", "VarTimeZone"},
               {"Text", "Time Zone"},
               {"Value", this->location.TimeZone},
               {"FormattedValue", this->location.TimeZone},
               {"HelpFile", ":/dox/en/time-zone.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarUTCTimeOffset()
//******************************************************************************
mVarget Meeus::VarUTCTimeOffset()
{
    double sto = this->GetUTCTimeOffset(this->JD);
    mVarget rc{{"Name", "VarUTCTimeOffset"},
               {"Text", "UTC Time Offset for this TimeZone"},
               {"Value", sto},
               {"FormattedValue", printHMS(sto)},
               {"HelpFile", ":/dox/en/utc-time-offset.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarDaylightSavingTimeOffset()
//******************************************************************************
mVarget Meeus::VarDaylightSavingTimeOffset()
{
    double sto = this->GetDaylightSavingTimeOffset(this->JD);
    mVarget rc{{"Name", "VarDaylightTimeOffset"},
               {"Text", "Daylight Time Offset for this TimeZone"},
               {"Value", sto},
               {"FormattedValue", printHMS(sto)},
               {"HelpFile", ":/dox/en/daylight-time-offset.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarStandardTimeOffset()
//******************************************************************************
mVarget Meeus::VarStandardTimeOffset()
{
    double sto = this->GetStandardTimeOffset(this->JD);
    mVarget rc{{"Name", "VarStandardTimeOffset"},
               {"Text", "Standard Time Offset for this TimeZone"},
               {"Value", sto},
               {"FormattedValue", printHMS(sto)},
               {"HelpFile", ":/dox/en/standard-time-offset.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarLatitude()
//******************************************************************************
mVarget Meeus::VarLatitude()
{
    mVarget rc{{"Name", "VarLatitude"},
               {"Text", "Latitude"},
               {"Value", this->location.Latitude},
               {"FormattedValue", printDMS(this->location.Latitude)},
               {"HelpFile", ":/dox/en/latitude.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarLongitude()
//******************************************************************************
mVarget Meeus::VarLongitude()
{
    mVarget rc{{"Name", "VarLongitude"},
               {"Text", "Longitude"},
               {"Value", this->location.Longitude},
               {"FormattedValue", printDMS(this->location.Longitude)},
               {"HelpFile", ":/dox/en/longitude.md"}};
    return rc;
}

//******************************************************************************
// Meeus::Date2JD()
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
// Meeus::JD2Date()
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
// Meeus::DayOfWeek()
//******************************************************************************
int Meeus::DayOfWeek(double JD)
{
    int dow = (int) (JD + 1.5) % 7;
    return dow;
}

//******************************************************************************
// Meeus::DaysBetweenDates()
//******************************************************************************
int Meeus::DaysBetweenDates(QDateTime dt1, QDateTime dt2)
{
    double jd1 = Date2JD(dt1);
    double jd2 = Date2JD(dt2);
    return (int) (jd2 - jd1);
}

//******************************************************************************
// Meeus::AddDays2Date()
//******************************************************************************
QDateTime Meeus::AddDays2Date(QDateTime dt, int d)
{
    double jd = Date2JD(dt);
    jd = jd + (double) d;
    return JD2Date(jd);
}

//******************************************************************************
// Meeus::SetDefaultLocation()
//******************************************************************************
void Meeus::SetDefaultLocation() {
  Location loc;
  loc.Country = "France";
  loc.Name = "Ozoir-la-Ferrière (FR)";
  loc.Latitude = 48.778056;
  loc.Longitude = 2.68;
  loc.TimeZone = "Europe/Paris";
  loc.tz = QTimeZone(loc.TimeZone.toUtf8());
  this->location = loc;
}

//******************************************************************************
// Meeus::SetLocation()
//******************************************************************************
void Meeus::SetLocation(Location loc)
{
    this->location = loc;
}

//******************************************************************************
// Meeus::SetTimeZone()
//******************************************************************************
void Meeus::SetTimeZone(QTimeZone tz)
{
    this->tz = tz;
    this->location.tz = tz;
    this->location.TimeZone = tz.id();
}

//******************************************************************************
// Meeus::getDay()
//******************************************************************************
int Meeus::getDay() {
  return this->dt.date().day();
}

//******************************************************************************
// Meeus::getMonth()
//******************************************************************************
int Meeus::getMonth() {
  return this->dt.date().month();
}

//******************************************************************************
// Meeus::getYear()
//******************************************************************************
int Meeus::getYear() {
  return this->dt.date().year();
}

//******************************************************************************
// Meeus::getHour()
//******************************************************************************
int Meeus::getHour() {
  return this->dt.time().hour();
}

//******************************************************************************
// Meeus::getMinute()
//******************************************************************************
int Meeus::getMinute() {
  return this->dt.time().minute();
}

//******************************************************************************
// Meeus::getSecond()
//******************************************************************************
int Meeus::getSecond() {
  return this->dt.time().second();
}

//******************************************************************************
// Meeus::init()
//******************************************************************************
void Meeus::init() {
    this->refresh(this->dt);
}

//******************************************************************************
// Meeus::refresh()
//******************************************************************************
void Meeus::refresh(QDateTime dt)
{
    this->dt = dt;
    this->ComputeJD();
}

//******************************************************************************
// Meeus::getDateTime()
//******************************************************************************
QString Meeus::getDateTime()
{
    return this->dt.toString();
}

//******************************************************************************
// Meeus::getLocation()
//******************************************************************************
QString Meeus::getLocation()
{
    return this->location.Name;
}

//******************************************************************************
// Meeus::VarSunMeanLongitude()
//******************************************************************************
mVarget Meeus::VarSunMeanLongitude()
{
    double sml = Sun::MeanLongitude(this->JD);
    mVarget rc{{"Name", "VarSunMeanLongitude"},
               {"Text", "Sun's Mean Longitude"},
               {"Value", sml},
               {"FormattedValue", printDMS(sml)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/sun-mean-longitude.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunMeanAnomaly()
//******************************************************************************
mVarget Meeus::VarSunMeanAnomaly()
{
    double sma = Sun::MeanAnomaly(this->JD);
    mVarget rc{{"Name", "VarSunMeanAnomaly"},
               {"Text", "Sun's Mean Anomaly"},
               {"Value", sma},
               {"FormattedValue", printDMS(sma)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/sun-mean-anomaly.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunCenter()
//******************************************************************************
mVarget Meeus::VarSunCenter()
{
    double sc = Sun::Center(this->JD, Sun::MeanAnomaly(this->JD));
    mVarget rc{{"Name", "VarSunCenter"},
               {"Text", "Sun's Center"},
               {"Value", sc},
               {"FormattedValue", printDMS(sc)},
               {"Page", 172},
               {"HelpFile", ":/dox/en/sun-center.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunTrueLongitude()
//******************************************************************************
mVarget Meeus::VarSunTrueLongitude()
{
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(this->JD),
                                    Sun::Center(this->JD, Sun::MeanAnomaly(this->JD)));
    mVarget rc{{"Name", "VarSunTrueLongitude"},
               {"Text", "Sun's True Longitude"},
               {"Value", stl},
               {"FormattedValue", printDMS(stl)},
               {"Page", 173},
               {"HelpFile", ":/dox/en/sun-true-longitude.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunTrueAnomaly()
//******************************************************************************
mVarget Meeus::VarSunTrueAnomaly()
{
    double sta = Sun::TrueAnomaly(Sun::MeanAnomaly(this->JD),
                                  Sun::Center(this->JD, Sun::MeanAnomaly(this->JD)));
    mVarget rc{{"Name", "VarSunTrueAnomaly"},
               {"Text", "Sun's True Anomaly"},
               {"Value", sta},
               {"FormattedValue", printDMS(sta)},
               {"Page", 172},
               {"HelpFile", ":/dox/en/sun-true-anomaly.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunApparentLongitude()
//******************************************************************************
mVarget Meeus::VarSunApparentLongitude()
{
    double sal = Sun::ApparentLongitude(Sun::TrueLongitude(Sun::MeanLongitude(this->JD),
                                                           Sun::Center(this->JD,
                                                                       Sun::MeanAnomaly(this->JD))),
                                        Sun::NutationAberrationCorrection(this->JD));
    mVarget rc{{"Name", "VarSunApparentLongitude"},
               {"Text", "Sun's Apparent Longitude"},
               {"Value", sal},
               {"FormattedValue", printDMS(sal)},
               {"Page", 172},
               {"HelpFile", ":/dox/en/sun-apparent-longitude.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunRadiusVector()
//******************************************************************************
mVarget Meeus::VarSunRadiusVector()
{
    double srv = Sun::RadiusVector(Earth::MeanEccentricity(this->JD),
                                   Sun::TrueAnomaly(Sun::MeanAnomaly(this->JD),
                                                    Sun::Center(this->JD,
                                                                Sun::MeanAnomaly(this->JD))));
    mVarget rc{{"Name", "VarSunRadiusVector"},
               {"Text", "Sun's Radius Vector"},
               {"Value", srv},
               {"FormattedValue", QString("%1").arg(srv, 7)},
               {"Page", 172},
               {"HelpFile", ":/dox/en/sun-radius-vector.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunNutationAberrationCorrection()
//******************************************************************************
mVarget Meeus::VarSunNutationAberrationCorrection()
{
    // Sun::compute(this->JD);
    double snac = Sun::NutationAberrationCorrection(this->JD);
    mVarget rc{{"Name", "VarSunNutationAberrationCorrection"},
               {"Text", "Sun's Nutation Aberration Correction"},
               {"Value", snac},
               {"FormattedValue", printDMS(snac)},
               {"Page", 172},
               {"HelpFile", ":/dox/en/sun-nutation-aberration-correction.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunRightAscension()
//******************************************************************************
mVarget Meeus::VarSunRightAscension()
{
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(this->JD),
                                      Earth::NutationObliquity(this->JD,
                                                               Sun::MeanLongitude(this->JD),
                                                               Moon::MeanLongitude(this->JD),
                                                               Sun::MeanAnomaly(this->JD),
                                                               Moon::MeanAnomaly(this->JD),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   this->JD)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(this->JD),
                                    Sun::Center(this->JD, Sun::MeanAnomaly(this->JD)));
    double sra = Sun::RightAscension(eto, stl);
    mVarget rc{{"Name", "VarSunRightAscension"},
               {"Text", "Sun's Right Ascension"},
               {"Value", sra},
               {"FormattedValue", printHMS(sra)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/sun-right-ascension.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunApparentRightAscension()
//******************************************************************************
mVarget Meeus::VarSunApparentRightAscension()
{
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(this->JD),
                                      Earth::NutationObliquity(this->JD,
                                                               Sun::MeanLongitude(this->JD),
                                                               Moon::MeanLongitude(this->JD),
                                                               Sun::MeanAnomaly(this->JD),
                                                               Moon::MeanAnomaly(this->JD),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   this->JD)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(this->JD),
                                    Sun::Center(this->JD, Sun::MeanAnomaly(this->JD)));
    double snac = Sun::NutationAberrationCorrection(this->JD);
    double sal = Sun::ApparentLongitude(stl, snac);
    double sara = Sun::ApparentRightAscension(eto, sal, snac);
    mVarget rc{{"Name", "VarSunApparentRightAscension"},
               {"Text", "Sun's Apparent Right Ascension"},
               {"Value", sara},
               {"FormattedValue", printHMS(sara)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/sun-apparent-right-ascension.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunDeclination()
//******************************************************************************
mVarget Meeus::VarSunDeclination()
{
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(this->JD),
                                      Earth::NutationObliquity(this->JD,
                                                               Sun::MeanLongitude(this->JD),
                                                               Moon::MeanLongitude(this->JD),
                                                               Sun::MeanAnomaly(this->JD),
                                                               Moon::MeanAnomaly(this->JD),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   this->JD)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(this->JD),
                                    Sun::Center(this->JD, Sun::MeanAnomaly(this->JD)));
    double sd = Sun::Declination(eto, stl);
    mVarget rc{{"Name", "VarSunDeclination"},
               {"Text", "Sun's Declination"},
               {"Value", sd},
               {"FormattedValue", printDMS(sd)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/sun-declination.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunApparentDeclination()
//******************************************************************************
mVarget Meeus::VarSunApparentDeclination()
{
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(this->JD),
                                      Earth::NutationObliquity(this->JD,
                                                               Sun::MeanLongitude(this->JD),
                                                               Moon::MeanLongitude(this->JD),
                                                               Sun::MeanAnomaly(this->JD),
                                                               Moon::MeanAnomaly(this->JD),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   this->JD)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(this->JD),
                                    Sun::Center(this->JD, Sun::MeanAnomaly(this->JD)));
    double snac = Sun::NutationAberrationCorrection(this->JD);
    double sal = Sun::ApparentLongitude(stl, snac);
    double sad = Sun::ApparentDeclination(eto, sal, snac);
    mVarget rc{{"Name", "VarSunApparentDeclination"},
               {"Text", "Sun's Apparent Declination"},
               {"Value", sad},
               {"FormattedValue", printDMS(sad)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/sun-apparent-right-ascension.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunRise()
//******************************************************************************
mVarget Meeus::VarSunRise()
{
    // Warning : The JD used for Sun's Right Ascension and Declination is the JD at noon
    double mjd = floor(this->JD) + 0.5;
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(mjd),
                                      Earth::NutationObliquity(mjd,
                                                               Sun::MeanLongitude(mjd),
                                                               Moon::MeanLongitude(mjd),
                                                               Sun::MeanAnomaly(mjd),
                                                               Moon::MeanAnomaly(mjd),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   mjd)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(mjd),
                                    Sun::Center(mjd, Sun::MeanAnomaly(mjd)));
    double snac = Sun::NutationAberrationCorrection(mjd);
    double sal = Sun::ApparentLongitude(stl, snac);
    double sad = Sun::ApparentDeclination(eto, sal, snac);
    double sara = Sun::ApparentRightAscension(eto, sal, snac);
    TransitRiseSet trs = GetTransitRiseSet(H0_SUN * toRad,
                                           this->JD,
                                           this->location.Latitude * toRad,
                                           this->location.Longitude * toRad,
                                           sara * 15.0 * toRad,
                                           sad * toRad);
    double rise = trs.Rise + GetUTCTimeOffset(mjd);
    mVarget rc{{"Name", "VarSunRise"},
               {"Text", "Sun's Rise"},
               {"Value", rise},
               {"FormattedValue", printHMS(rise)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/sun-rise.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunTransit()
//******************************************************************************
mVarget Meeus::VarSunTransit()
{
    // Warning : The JD used for Sun's Right Ascension and Declination is the JD at noon
    double mjd = floor(this->JD) + 0.5;
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(mjd),
                                      Earth::NutationObliquity(mjd,
                                                               Sun::MeanLongitude(mjd),
                                                               Moon::MeanLongitude(mjd),
                                                               Sun::MeanAnomaly(mjd),
                                                               Moon::MeanAnomaly(mjd),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   mjd)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(mjd),
                                    Sun::Center(mjd, Sun::MeanAnomaly(mjd)));
    double snac = Sun::NutationAberrationCorrection(mjd);
    double sal = Sun::ApparentLongitude(stl, snac);
    double sad = Sun::ApparentDeclination(eto, sal, snac);
    double sara = Sun::ApparentRightAscension(eto, sal, snac);
    TransitRiseSet trs = GetTransitRiseSet(H0_SUN * toRad,
                                           this->JD,
                                           this->location.Latitude * toRad,
                                           this->location.Longitude * toRad,
                                           sara * 15.0 * toRad,
                                           sad * toRad);
    double transit = trs.Transit + GetUTCTimeOffset(mjd);
    mVarget rc{{"Name", "VarSunTransit"},
               {"Text", "Sun's Transit"},
               {"Value", transit},
               {"FormattedValue", printHMS(transit)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/sun-transit.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarSunSet()
//******************************************************************************
mVarget Meeus::VarSunSet()
{
    // Warning : The JD used for Sun's Right Ascension and Declination is the JD at noon
    double mjd = floor(this->JD) + 0.5;
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(mjd),
                                      Earth::NutationObliquity(mjd,
                                                               Sun::MeanLongitude(mjd),
                                                               Moon::MeanLongitude(mjd),
                                                               Sun::MeanAnomaly(mjd),
                                                               Moon::MeanAnomaly(mjd),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   mjd)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(mjd),
                                    Sun::Center(mjd, Sun::MeanAnomaly(mjd)));
    double snac = Sun::NutationAberrationCorrection(mjd);
    double sal = Sun::ApparentLongitude(stl, snac);
    double sad = Sun::ApparentDeclination(eto, sal, snac);
    double sara = Sun::ApparentRightAscension(eto, sal, snac);
    TransitRiseSet trs = GetTransitRiseSet(H0_SUN * toRad,
                                           this->JD,
                                           this->location.Latitude * toRad,
                                           this->location.Longitude * toRad,
                                           sara * 15.0 * toRad,
                                           sad * toRad);
    double set = trs.Set + GetUTCTimeOffset(mjd);
    mVarget rc{{"Name", "VarSunSet"},
               {"Text", "Sun's Set"},
               {"Value", set},
               {"FormattedValue", printHMS(set)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/sun-set.md"}};
    return rc;
}

//******************************************************************************
// Meeus::GetUTCTimeOffset()
//******************************************************************************
double Meeus::GetUTCTimeOffset(double JD)
{
    return ((double) this->location.tz.offsetFromUtc(JD2Date(JD)) / 3600.0);
}

//******************************************************************************
// Meeus::GetDaylightSavingTimeOffset()
//******************************************************************************
double Meeus::GetDaylightSavingTimeOffset(double JD)
{
    return ((double) this->location.tz.daylightTimeOffset(JD2Date(JD)) / 3600.0);
}

//******************************************************************************
// Meeus::GetStandardTimeOffset()
//******************************************************************************
double Meeus::GetStandardTimeOffset(double JD)
{
    return ((double) this->location.tz.standardTimeOffset(JD2Date(JD)) / 3600.0);
}

//******************************************************************************
// Meeus::GetDaylightDuration()
//******************************************************************************
double Meeus::GetDaylightDuration(double JD)
{
    // Warning : The JD used for Sun's Right Ascension and Declination is the JD at noon
    double mjd = floor(JD) + 0.5;
    double eto = Earth::TrueObliquity(Earth::MeanObliquity(mjd),
                                      Earth::NutationObliquity(mjd,
                                                               Sun::MeanLongitude(mjd),
                                                               Moon::MeanLongitude(mjd),
                                                               Sun::MeanAnomaly(mjd),
                                                               Moon::MeanAnomaly(mjd),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   mjd)));
    double stl = Sun::TrueLongitude(Sun::MeanLongitude(mjd),
                                    Sun::Center(mjd, Sun::MeanAnomaly(mjd)));
    double snac = Sun::NutationAberrationCorrection(mjd);
    double sal = Sun::ApparentLongitude(stl, snac);
    double sad = Sun::ApparentDeclination(eto, sal, snac);
    double sara = Sun::ApparentRightAscension(eto, sal, snac);
    TransitRiseSet trs = GetTransitRiseSet(H0_SUN * toRad,
                                           this->JD,
                                           this->location.Latitude * toRad,
                                           this->location.Longitude * toRad,
                                           sara * 15.0 * toRad,
                                           sad * toRad);
    double set = trs.Set + GetUTCTimeOffset(mjd);
    double rise = trs.Rise + GetUTCTimeOffset(mjd);

    return (set - rise);
}

//******************************************************************************
// Meeus::VarDaylightDuration()
//******************************************************************************
mVarget Meeus::VarDaylightDuration()
{
    double dld = this->GetDaylightDuration(this->JD);
    mVarget rc{{"Name", "VarDaylightDuration"},
               {"Text", "Daylight Duration"},
               {"Value", dld},
               {"FormattedValue", printHMS(dld)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/daylight-duration.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarDaylightDurationVersusYesterday()
//******************************************************************************
mVarget Meeus::VarDaylightDurationVersusYesterday()
{
    double dld0 = this->GetDaylightDuration(this->JD);
    double dld1 = this->GetDaylightDuration(this->JD - 1);
    qDebug() << dld0;
    qDebug() << dld1;
    mVarget rc{{"Name", "VarDaylightDurationVersusYesterday"},
               {"Text", "Daylight Duration versus yesterday"},
               {"Value", (dld0 - dld1)},
               {"FormattedValue", printSHMS(dld0 - dld1)},
               {"Page", 165},
               {"HelpFile", ":/dox/en/daylight-duration-versus-yesterday.md"}};
    return rc;
}

//******************************************************************************
// Meeus::GetTransitRiseSet()
// Warning : All angles must be in radians
//******************************************************************************
TransitRiseSet Meeus::GetTransitRiseSet(double h0,
                                        double JD,
                                        double Latitude,
                                        double Longitude,
                                        double RightAscension,
                                        double Declination)
{
    // Warning : Jean Meeus considers eastward longitudes are negatives, the opposite of what we use !!!
    Longitude = Longitude * -1;
    double cosH = (sin(h0) - sin(Latitude) * sin(Declination)) / (cos(Latitude) * cos(Declination));
    double H0 = acos(cosH) * toDeg;
    double gmst = GreenwichMeanSideralTime(floor(JD) + 0.5);

    // Warning : These hours are in UT
    double transit = (RightAscension * toDeg + Longitude * toDeg - gmst) / 360.0;
    double rise = transit - (H0 / 360.0);
    double set = transit + (H0 / 360.0);

    // These values are fractions of a day, so we have to multiply them by 24
    // and be sure they are between 0 and 1 before
    TransitRiseSet trs = {constrain(transit) * 24.0, constrain(rise) * 24.0, constrain(set) * 24.0};

    return trs;
}

//******************************************************************************
// Meeus::GreenwichMeanSideralTime()
//******************************************************************************
double Meeus::GreenwichMeanSideralTime(double JD)
{
    double T = (JD - 2451545.0) / 36525.0;
    double gmst = 280.46061837 + 360.98564736629 * (JD - 2451545.0) + 0.000387933 * (T * T)
                  - (T * T * T) / 38710000.0;
    gmst = fmod(gmst, 360.0);
    if (gmst < 0.0) {
        gmst += 360.0;
    }
    qDebug() << "GMST:" + QString::number(gmst);
    return gmst;
}

//******************************************************************************
// Sun::MeanLongitude()
//******************************************************************************
double Sun::MeanLongitude(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Sun's Mean Longitude
    return reduceAngle(Polynomial(T, vCoefs{280.46646, 36000.76983, 0.0003032}));
}

//******************************************************************************
// Sun::MeanAnomaly()
//******************************************************************************
double Sun::MeanAnomaly(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Sun's Mean Anomaly
    return reduceAngle(Polynomial(T, vCoefs{357.52911, 35999.05029, -0.0001537}));
}

//******************************************************************************
// Sun::Center()
//******************************************************************************
double Sun::Center(double JD, double MeanAnomaly)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Sun's Equation of the Center
    double c;
    c = (1.914602 - 0.004817 * T - 0.000014 * (T * T)) * sin(deg2rad(MeanAnomaly));
    c += (0.01993 - 0.000101 * T) * sin(deg2rad(2 * MeanAnomaly));
    c += 0.000289 * sin(deg2rad(3 * MeanAnomaly));
    c = reduceAngle(c);
    return c;
}

//******************************************************************************
// Sun::TrueLongitude()
//******************************************************************************
double Sun::TrueLongitude(double MeanLongitude, double Center)
{
    // Sun's True Longitude
    return reduceAngle(MeanLongitude + Center);
}

//******************************************************************************
// Sun::TrueAnomaly()
//******************************************************************************
double Sun::TrueAnomaly(double MeanAnomaly, double Center)
{
    // Sun's True Anomaly
    return reduceAngle(MeanAnomaly + Center);
}

//******************************************************************************
// Sun::RadiusVector()
//******************************************************************************
double Sun::RadiusVector(double MeanEccentricity, double TrueAnomaly)
{
    // Sun's Radius Vector
    return (1.000001018 * (1 - (MeanEccentricity * MeanEccentricity)))
           / (1 + MeanEccentricity * cos(deg2rad(TrueAnomaly)));
}

//******************************************************************************
// Sun::NutationAberrationCorrection()
//******************************************************************************
double Sun::NutationAberrationCorrection(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Nutation & Aberration Correction
    return reduceAngle(125.04 - 1934.136 * T);
}

//******************************************************************************
// Sun::ApparentLongitude()
//******************************************************************************
double Sun::ApparentLongitude(double TrueLongitude, double NutationAberrationCorrection)
{
    // Sun's Apparent Longitude
    return reduceAngle(TrueLongitude - 0.00569
                       - 0.00478 * sin(deg2rad(NutationAberrationCorrection)));
}

//******************************************************************************
// Sun::RightAscension()
//******************************************************************************
double Sun::RightAscension(double TrueObliquity, double TrueLongitude)
{
    TrueObliquity = toRad * TrueObliquity;
    TrueLongitude = toRad * TrueLongitude;
    double ra = atan2(cos(TrueObliquity) * sin(TrueLongitude), cos(TrueLongitude));
    if (ra < 0.0) {
        ra += M_PI * 2.0;
    }

    return ra * toDeg / 15.0;
}

//******************************************************************************
// Sun::Declination()
//******************************************************************************
double Sun::Declination(double TrueObliquity, double TrueLongitude)
{
    TrueObliquity = toRad * TrueObliquity;
    TrueLongitude = toRad * TrueLongitude;
    double dec = asin(sin(TrueObliquity) * sin(TrueLongitude));

    return dec * toDeg;
}

//******************************************************************************
// Sun::ApparentRightAscension()
//******************************************************************************
double Sun::ApparentRightAscension(double TrueObliquity,
                                   double ApparentLongitude,
                                   double NutationAberrationCorrection)
{
    NutationAberrationCorrection = toRad * NutationAberrationCorrection;
    TrueObliquity = toRad * (TrueObliquity + 0.00256 * cos(toRad * NutationAberrationCorrection));
    ApparentLongitude = toRad * ApparentLongitude;
    double ra = atan2(cos(TrueObliquity) * sin(ApparentLongitude), cos(ApparentLongitude));
    if (ra < 0.0) {
        ra += M_PI * 2.0;
    }

    return ra * toDeg / 15.0;
}

//******************************************************************************
// Sun::ApparentDeclination()
//******************************************************************************
double Sun::ApparentDeclination(double TrueObliquity,
                                double ApparentLongitude,
                                double NutationAberrationCorrection)
{
    NutationAberrationCorrection = toRad * NutationAberrationCorrection;
    TrueObliquity = toRad * (TrueObliquity + 0.00256 * cos(toRad * NutationAberrationCorrection));
    ApparentLongitude = toRad * ApparentLongitude;
    double dec = asin(sin(TrueObliquity) * sin(ApparentLongitude));

    return dec * toDeg;
}

//******************************************************************************
// Moon::MeanLongitude()
//******************************************************************************
double Moon::MeanLongitude(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Mean Longitude
    return reduceAngle(
        Polynomial(T, vCoefs{218.31644735, 481267.88122838, -0.00159944, 1 / 538841}));
}

//******************************************************************************
// Moon::MeanAnomaly()
//******************************************************************************
double Moon::MeanAnomaly(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Mean Anomaly
    return reduceAngle(Polynomial(T, vCoefs{134.96339622, 477198.86750067, 0.00872053, 1 / 69699}));
}

//******************************************************************************
// Moon::MeanElongation()
//******************************************************************************
double Moon::MeanElongation(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Mean Elongation
    return reduceAngle(
        Polynomial(T, vCoefs{297.85019172, 445267.11139756, -0.00190272, 1 / 545868}));
}

//******************************************************************************
// Moon::MeanDistanceFromAscendantNode()
//******************************************************************************
double Moon::MeanDistanceFromAscendantNode(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Mean Distance from Ascendant Node
    return reduceAngle(
        Polynomial(T, vCoefs{93.27209769, 483202.01756053, -0.00367481, -1 / 3525955}));
}

//******************************************************************************
// Moon::MeanLongitudeFromAscendantNode()
//******************************************************************************
double Moon::MeanLongitudeFromAscendantNode(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Mean Longitude from Ascendant Node of Moon's Orbit on ecliptic
    return reduceAngle(Polynomial(T, vCoefs{125.0443, -1934.1363, 0.002075}));
}

//******************************************************************************
// Meeus::VarMoonMeanLongitude()
//******************************************************************************
mVarget Meeus::VarMoonMeanLongitude()
{
    double mml = Moon::MeanLongitude(this->JD);
    mVarget rc{{"Name", "VarMoonMeanLongitude"},
               {"Text", "Moon's Mean Longitude"},
               {"Value", mml},
               {"FormattedValue", printDMS(mml)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/moon-mean-longitude.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarMoonMeanAnomaly()
//******************************************************************************
mVarget Meeus::VarMoonMeanAnomaly()
{
    double mma = Moon::MeanAnomaly(this->JD);
    mVarget rc{{"Name", "VarMoonMeanAnomaly"},
               {"Text", "Moon's Mean Anomaly"},
               {"Value", mma},
               {"FormattedValue", printDMS(mma)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/moon-mean-anomaly.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarMoonMeanElongation()
//******************************************************************************
mVarget Meeus::VarMoonMeanElongation()
{
    double mme = Moon::MeanAnomaly(this->JD);
    mVarget rc{{"Name", "VarMoonMeanElongation"},
               {"Text", "Moon's Mean Elongation"},
               {"Value", mme},
               {"FormattedValue", printDMS(mme)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/moon-mean-elongation.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarMoonMeanDistanceFromAscendantNode()
//******************************************************************************
mVarget Meeus::VarMoonMeanDistanceFromAscendantNode()
{
    double mdfan = Moon::MeanDistanceFromAscendantNode(this->JD);
    mVarget rc{{"Name", "VarMoonMeanDistanceFromAscendantNode"},
               {"Text", "Moon's Distance from Ascendant Node"},
               {"Value", mdfan},
               {"FormattedValue", printDMS(mdfan)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/moon-distance-from-ascendant-node.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarMoonMeanLongitudeFromAscendantNode()
//******************************************************************************
mVarget Meeus::VarMoonMeanLongitudeFromAscendantNode()
{
    double mmlfan = Moon::MeanLongitudeFromAscendantNode(this->JD);
    mVarget rc{{"Name", "VarMoonMeanLongitudeFromAscendantNode"},
               {"Text", "Moon's Mean Longitude from Ascendant Node"},
               {"Value", mmlfan},
               {"FormattedValue", printDMS(mmlfan)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/moon-mean-longitude-from-ascendant-node.md"}};
    return rc;
}

//******************************************************************************
// Earth::MeanEccentricity()
//******************************************************************************
double Earth::MeanEccentricity(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Earth's Mean Eccentricity
    return reduceAngle(Polynomial(T, vCoefs{0.016708634, -0.000042037, -0.0000001267}));
}

//******************************************************************************
// Earth::NutationLongitude()
//******************************************************************************
double Earth::NutationLongitude(double JD,
                                double SunMeanLongitude,
                                double MoonMeanLongitude,
                                double SunMeanAnomaly,
                                double MoonMeanAnomaly,
                                double MoonMeanLongitudeFromAscendantNode)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Earth's Nutation in Longitude
    double dnl = -(17.1996 + 0.01742 * T) * sin(deg2rad(MoonMeanLongitudeFromAscendantNode));
    dnl -= (1.3187 + 0.00016 * T) * sin(deg2rad(2 * SunMeanLongitude));
    dnl -= 0.2274 * sin(deg2rad(2 * MoonMeanLongitude));
    dnl += 0.2062 * sin(deg2rad(2 * MoonMeanLongitudeFromAscendantNode));
    dnl += (0.1426 - 0.00034 * T) * sin(deg2rad(SunMeanAnomaly));
    dnl += 0.0712 * sin(deg2rad(MoonMeanAnomaly));
    dnl -= (0.0517 - 0.00012 * T) * sin(deg2rad(2 * SunMeanLongitude + SunMeanAnomaly));
    dnl -= 0.0386 * sin(deg2rad(2 * MoonMeanLongitude - MoonMeanLongitudeFromAscendantNode));
    dnl -= 0.0301 * sin(deg2rad(2 * MoonMeanLongitude + MoonMeanAnomaly));
    dnl += 0.0217 * sin(deg2rad(2 * SunMeanLongitude - SunMeanAnomaly));
    dnl -= 0.0158 * sin(deg2rad(2 * SunMeanLongitude - 2 * MoonMeanLongitude + MoonMeanAnomaly));
    dnl += 0.0129 * sin(deg2rad(2 * SunMeanLongitude - MoonMeanLongitudeFromAscendantNode));
    dnl += 0.0123 * sin(deg2rad(2 * MoonMeanLongitude - MoonMeanAnomaly));

    return reduceAngle(dnl / 3600.0);
}

//******************************************************************************
// Earth::NutationObliquity()
//******************************************************************************
double Earth::NutationObliquity(double JD,
                                double SunMeanLongitude,
                                double MoonMeanLongitude,
                                double SunMeanAnomaly,
                                double MoonMeanAnomaly,
                                double MoonMeanLongitudeFromAscendantNode)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Earth's Nutation in Obliquity
    double dno = (9.2025 + 0.00089 * T) * cos(deg2rad(MoonMeanLongitudeFromAscendantNode));
    dno += (0.5736 - 0.00031 * T) * cos(deg2rad(2 * SunMeanLongitude));
    dno += 0.0977 * cos(deg2rad(2 * MoonMeanLongitude));
    dno -= 0.0895 * cos(deg2rad(2 * MoonMeanLongitudeFromAscendantNode));
    dno += 0.0224 * cos(deg2rad(2 * SunMeanLongitude + SunMeanAnomaly));
    dno += 0.0200 * cos(deg2rad(2 * MoonMeanLongitude - MoonMeanLongitudeFromAscendantNode));
    dno += 0.0129 * cos(deg2rad(2 * MoonMeanLongitude + MoonMeanAnomaly));
    dno -= 0.0095 * cos(deg2rad(2 * SunMeanLongitude - SunMeanAnomaly));
    dno -= 0.0070 * cos(deg2rad(2 * SunMeanLongitude - MoonMeanLongitudeFromAscendantNode));

    return reduceAngle(dno / 3600.0);
}

//******************************************************************************
// Earth::MeanObliquity()
//******************************************************************************
double Earth::MeanObliquity(double JD)
{
    // Time in Julian Centuries
    double T = (JD - 2451545.0) / 36525.0;
    // Earth's Mean Obliquity
    return reduceAngle(Polynomial(T, vCoefs{23.43929111, -0.01300417, -0.00000016, 0.00000050}));
}

//******************************************************************************
// Earth::TrueObliquity()
//******************************************************************************
double Earth::TrueObliquity(double MeanObliquity, double NutationObliquity)
{
    // Earth's True Obliquity ε = ε0 + Δε
    return reduceAngle(MeanObliquity + NutationObliquity);
}

//******************************************************************************
// Meeus::VarEarthMeanEccentricity()
//******************************************************************************
mVarget Meeus::VarEarthMeanEccentricity()
{
    double eme = Earth::MeanEccentricity(this->JD);
    mVarget rc{{"Name", "VarEarthMeanEccentricity"},
               {"Text", "Earth's Mean Eccentricity"},
               {"Value", eme},
               {"FormattedValue", printDMS(eme)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/earth-mean-eccentricity.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarEarthNutationLongitude()
//******************************************************************************
mVarget Meeus::VarEarthNutationLongitude()
{
    double var = Earth::NutationLongitude(this->JD,
                                          Sun::MeanLongitude(this->JD),
                                          Moon::MeanLongitude(this->JD),
                                          Sun::MeanAnomaly(this->JD),
                                          Moon::MeanAnomaly(this->JD),
                                          Moon::MeanLongitudeFromAscendantNode(this->JD));
    mVarget rc{{"Name", "VarEarthNutationLongitude"},
               {"Text", "Earth's Nutation in Longitude"},
               {"Value", var},
               {"FormattedValue", printDMS(var)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/earth-nutation-longitude.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarEarthNutationObliquity()
//******************************************************************************
mVarget Meeus::VarEarthNutationObliquity()
{
    double var = Earth::NutationObliquity(this->JD,
                                          Sun::MeanLongitude(this->JD),
                                          Moon::MeanLongitude(this->JD),
                                          Sun::MeanAnomaly(this->JD),
                                          Moon::MeanAnomaly(this->JD),
                                          Moon::MeanLongitudeFromAscendantNode(this->JD));
    mVarget rc{{"Name", "VarEarthNutationObliquity"},
               {"Text", "Earth's Nutation in Obliquity"},
               {"Value", var},
               {"FormattedValue", printDMS(var)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/earth-nutation-obliquity.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarEarthMeanObliquity()
//******************************************************************************
mVarget Meeus::VarEarthMeanObliquity()
{
    double var = Earth::MeanObliquity(this->JD);
    mVarget rc{{"Name", "VarEarthMeanObliquity"},
               {"Text", "Earth's Mean Obliquity"},
               {"Value", var},
               {"FormattedValue", printDMS(var)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/earth-mean-obliquity.md"}};
    return rc;
}

//******************************************************************************
// Meeus::VarEarthTrueObliquity()
//******************************************************************************
mVarget Meeus::VarEarthTrueObliquity()
{
    double var = Earth::TrueObliquity(Earth::MeanObliquity(this->JD),
                                      Earth::NutationObliquity(this->JD,
                                                               Sun::MeanLongitude(this->JD),
                                                               Moon::MeanLongitude(this->JD),
                                                               Sun::MeanAnomaly(this->JD),
                                                               Moon::MeanAnomaly(this->JD),
                                                               Moon::MeanLongitudeFromAscendantNode(
                                                                   this->JD)));
    mVarget rc{{"Name", "VarEarthTrueObliquity"},
               {"Text", "Earth's True Obliquity"},
               {"Value", var},
               {"FormattedValue", printDMS(var)},
               {"Page", 171},
               {"HelpFile", ":/dox/en/earth-true-obliquity.md"}};
    return rc;
}

//******************************************************************************
// PlanetaryOrbits::MeanLongitude()
//******************************************************************************
double PlanetaryOrbits::MeanLongitude(double T, double a0, double a1, double a2, double a3)
{
    return Polynomial(T, vCoefs{a0, a1, a2, a3});
}
// PlanetaryOrbits *Mercury = new PlanetaryOrbits();

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
// HD2HMS() => tuple{ h, m, s }
// Warning : This is a conversion from DECIMAL HOURS to HOURS, MINUTES, SECONDS
//******************************************************************************
std::tuple<int, int, int, int> HD2HMS(double hd)
{
    double fh = floor(hd);        // Full Hour
    double dm = (hd - fh) * 60;   // Double Minute
    double fm = floor(dm);        // Full Minute
    double ds = (dm - fm) * 60;   // Double Second
    double fs = floor(ds);        // Full Second
    double ss = (ds - fs) * 1000; // Decimal Second
    return std::make_tuple((int) fh, (int) fm, (int) fs, (int) ss);
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
std::tuple<int, int, int, int> DD2DMS(double dd)
{
    double sign = 1;
    if (dd < 0) {
        dd = abs(dd);
        sign = -1;
    }

    double fd = floor(dd);        // Full Degrees
    double dm = (dd - fd) * 60;   // Double Minute
    double fm = floor(dm);        // Full Minute
    double ds = (dm - fm) * 60;   // Double Second
    double fs = floor(ds);        // Full Second
    double ss = (ds - fs) * 1000; // Decimal Second

    return std::make_tuple((int) (fd * sign), (int) fm, (int) fs, (int) ss);
}

//******************************************************************************
// deg2rad()
//******************************************************************************
double deg2rad(double d)
{
    return (d * M_PI / 180.0);
}

//******************************************************************************
// rad2deg()
//******************************************************************************
double rad2deg(double r)
{
    return (r * 180.0 / M_PI);
}

//******************************************************************************
// reduceAngle()
//******************************************************************************
double reduceAngle(double a)
{
    while (a < 0) {
        a += 360.0;
    }
    // return fmod(a, 360.0);
    a = a - 360.0 * int(a / 360.0);
    return (a);
}

//******************************************************************************
// printDMS()
//******************************************************************************
QString printDMS(double a)
{
    auto dms = DD2DMS(a);
    QString s;
    s.sprintf("%+4d°%02d′%02d″.%03d",
              std::get<0>(dms),
              std::get<1>(dms),
              std::get<2>(dms),
              std::get<3>(dms));
    return s;
}

//******************************************************************************
// printHMS()
//******************************************************************************
QString printHMS(double a)
{
    auto hms = HD2HMS(a);
    QString s;
    s.sprintf("%2dʰ%02dᵐ%02dˢ.%03d",
              std::get<0>(hms),
              std::get<1>(hms),
              std::get<2>(hms),
              std::get<3>(hms));
    return s;
}

//******************************************************************************
// printSHMS()
//******************************************************************************
QString printSHMS(double a)
{
    QString sign = "+";
    QString s;
    if (a < 0) {
        sign = "-";
    }
    auto hms = HD2HMS(abs(a));
    s.sprintf("%s%02dʰ%02dᵐ%02dˢ.%03d",
              sign.toStdString().c_str(),
              std::get<0>(hms),
              std::get<1>(hms),
              std::get<2>(hms),
              std::get<3>(hms));
    return s;
}

//******************************************************************************
// Polynomial()
//******************************************************************************
double Polynomial(double ind, vCoefs coefs)
{
    // ind is the indeterminate
    // coefs are the coefficients for each power 0..n
    double value = 0;
    for (int n = 0; n < coefs.size(); ++n) {
        value = value + (coefs[n] * pow(ind, n));
    }
    return value;
}

//******************************************************************************
// constrain()
//******************************************************************************
double constrain(double v)
{
    if (v < 0) {
        return v + 1;
    }
    if (v > 1) {
        return v - 1;
    }
    return v;
}
/*
--------------------------------------------------------------------------------
The Greek Alphabet
https://web.mit.edu/jmorzins/www/greek-alphabet.html
--------------------------------------------------------------------------------

Α	α		alpha		a		father
Β	β		beta		b
Γ	γ		gamma		g
Δ	δ		delta		d
Ε	ε		epsilon 	e		end
Ζ	ζ		zêta		z
Η	η		êta			ê		hey
Θ	θ		thêta 		th		thick
Ι	ι		iota		i		it
Κ	κ		kappa		k
Λ	λ		lambda		l
Μ	μ		mu			m
Ν	ν		nu			n
Ξ	ξ		xi			ks		box
Ο	ο		omikron		o 		off
Π	π		pi			p
Ρ	ρ		rho			r
Σ	σ, ς	sigma		s		say
Τ	τ		tau			t
Υ	υ		upsilon		u		put
Φ	φ		phi			f
Χ	χ		chi			ch		Bach
Ψ	ψ		psi			ps
Ω	ω		omega		ô		grow

--------------------------------------------------------------------------------
*/
