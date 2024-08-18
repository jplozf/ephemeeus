#ifndef MEEUS_H
#define MEEUS_H

#include <QDateTime>
#include <QTimeZone>

class Meeus {
 public:
  struct Location {
    QString Name;
    double Latitude;
    double Longitude;
  };
  double JD;
  Meeus();
  Meeus(QDateTime dt);
  Meeus(Location location);
  Meeus(Location location, QDateTime dt);
  Meeus(Location location, QDateTime dt, QTimeZone tz);
  ~Meeus();
  void ComputeJD();
  void SetDefaultLocation();

 private:
  QDateTime dt;
  Location location;
  QTimeZone tz;
};

#endif  // MEEUS_H
