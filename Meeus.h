#ifndef MEEUS_H
#define MEEUS_H

#include <QDateTime>
#include <QDebug>
#include <QTimeZone>
#include "cmath"
#include "math.h"
#include "tuple"

class Meeus {
 public:
  const static int TIME_MODE_FIXED = 0;
  const static int TIME_MODE_REAL = 1;
  const static int TIME_MODE_RUNNING = 2;
  struct Location {
      QString Country;
      QString Name;
      double Latitude;
      double Longitude;
      QString TimeZone;
  };
  double JD;
  int time_mode;
  Meeus(Location location,
        QDateTime dt = QDateTime::currentDateTime(),
        QTimeZone tz = QTimeZone::utc(),
        int time_mode = TIME_MODE_REAL);
  ~Meeus();
  void ComputeJD();
  void SetDefaultLocation();
  void SetLocation(Location loc);
  int getDay();
  int getMonth();
  int getYear();
  int getHour();
  int getMinute();
  int getSecond();
  void init();
  void refresh(QDateTime dt);
  QString getDateTime();
  QString getLocation();
  double Date2JD(QDateTime dt);
  QDateTime JD2Date(double JD);
  int DayOfWeek(double JD);
  int DaysBetweenDates(QDateTime dt1, QDateTime dt2);
  QDateTime AddDays2Date(QDateTime dt, int d);
  // Misc General Purpose
  QString VarJD();
  QString VarT();
  QString VarDayOfWeek();
  QString VarDateTime();
  QString VarCountry();
  QString VarLocation();
  QString VarLatitude();
  QString VarLongitude();
  QString VarTimeZone();
  // SUN
  QString VarSunMeanLongitude();
  QString VarSunMeanAnomaly();
  QString VarSunCenter();
  QString VarSunTrueLongitude();
  QString VarSunTrueAnomaly();
  QString VarSunApparentLongitude();
  QString VarSunRadiusVector();

  private:
  QDateTime dt;
  Location location;
  QTimeZone tz;
};

class Sun
{
public:
    static double MeanLongitude;     // L0
    static double MeanAnomaly;       // M
    static double Center;            // C
    static double TrueLongitude;     // Θ
    static double TrueAnomaly;       // ν
    static double ApparentLongitude; // λ
    static double RadiusVector;      // R
    static void compute(double JD);
};

//******************************************************************************
// Misc General Purpose Functions defined outside the Class
//******************************************************************************
double frac(double d);
double DHMS2DD(int d, int h, int m, int s);
std::tuple<int, int, int, int> DD2DHMS(double dd);
double DMS2DD(int d, int m, int s);
std::tuple<int, int, int> DD2DMS(double dd);
double deg2rad(double d);
double rad2deg(double r);
double reduceAngle(double a);
QString printDMS(double a);

#endif  // MEEUS_H
