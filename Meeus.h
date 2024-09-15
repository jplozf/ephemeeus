#ifndef MEEUS_H
#define MEEUS_H

#include <QDateTime>
#include <QTimeZone>
#include "cmath"
#include "tuple"

class Meeus {
 public:
  const static int TIME_MODE_FIXED = 0;
  const static int TIME_MODE_REAL = 1;
  const static int TIME_MODE_RUNNING = 2;
  struct Location {
    QString Name;
    double Latitude;
    double Longitude;
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
  int getDay();
  int getMonth();
  int getYear();
  int getHour();
  int getMinute();
  int getSecond();
  void init();
  void refresh();
  QString getDateTime();
  QString getLocation();
  double Date2JD(QDateTime dt);
  QDateTime JD2Date(double JD);
  QString VarJD();
  QString VarDateTime();
  QString VarLocation();

  private:
  QDateTime dt;
  Location location;
  QTimeZone tz;
};

//******************************************************************************
// Misc General Purpose Functions defined outside the Class
//******************************************************************************
double frac(double d);
double DHMS2DD(int d, int h, int m, int s);
std::tuple<int, int, int, int> DD2DHMS(double dd);

#endif  // MEEUS_H
