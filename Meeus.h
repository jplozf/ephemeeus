#ifndef MEEUS_H
#define MEEUS_H

<<<<<<< HEAD

class Meeus
{
public:
    Meeus();
};

#endif // MEEUS_H
=======
#include <QDateTime>
#include <QTimeZone>

class Meeus {
 public:
  struct Location {
    QString Name;
    double Latitude;
    double Longitude;
  };
  Meeus();
  Meeus(QDateTime dt);
  Meeus(Location location);
  Meeus(Location location, QDateTime dt);
  Meeus(Location location, QDateTime dt, QTimeZone tz);
  ~Meeus();

 private:
  QDateTime dt;
  Location location;
  QTimeZone tz;
};

#endif  // MEEUS_H
>>>>>>> 1e2a372 (First Commit)
