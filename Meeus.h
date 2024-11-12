//******************************************************************************
//             _
//     ___ ___| |_ ___ _____ ___ ___ _ _ ___
//    | -_| . |   | -_|     | -_| -_| | |_ -|
//    |___|  _|_|_|___|_|_|_|___|___|___|___|
//        |_|
//                   (C) JPL 2024
//
//******************************************************************************
#ifndef MEEUS_H
#define MEEUS_H

//******************************************************************************
// Includes
//******************************************************************************
#include <QDateTime>
#include <QDebug>
#include <QTimeZone>
#include "cmath"
#include "math.h"
#include "tuple"

//******************************************************************************
// Types definition
//******************************************************************************
typedef QVector<double> vCoefs;
typedef QMap<QString, QVariant> mVarget;
typedef struct
{
    double Transit;
    double Rise;
    double Set;
} TransitRiseSet;

//******************************************************************************
// Constants
//******************************************************************************
const double toRad = M_PI / 180.0;
const double toDeg = 180.0 / M_PI;
const double H0_SUN = -0.8333;
const double H0_STARS_PLANETS = -0.5667;
const double H0_MOON = 0.125;
const double H0_CIVIL_TWILIGHT = -6.0;
const double H0_NAUICAL_TWILIGHT = -12.0;
const double H0_ASTRONOMICALTWILIGHT = -18.0;

//******************************************************************************
// Class Meeus
//******************************************************************************
class Meeus
{
public:
    const static int TIME_MODE_FIXED = 0;
    const static int TIME_MODE_REAL = 1;
    const static int TIME_MODE_RUNNING = 2;
    struct Location
    {
        QString Country;
        QString Name;
        double Latitude;
        double Longitude;
        QString TimeZone;
        QTimeZone tz;
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
    void SetTimeZone(QTimeZone tz);
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
    double GreenwichMeanSideralTime(double JD);
    TransitRiseSet GetTransitRiseSet(double h0,
                                     double JD,
                                     double Latitude,
                                     double Longitude,
                                     double RightAscension,
                                     double Declination);
    double GetUTCTimeOffset(double JD);
    double GetDaylightTimeOffset(double JD);
    double GetStandardTimeOffset(double JD);
    // Misc General Purpose
    mVarget VarJulianDay();
    mVarget VarT();
    mVarget VarDayOfWeek();
    mVarget VarDateTime();
    mVarget VarCountry();
    mVarget VarLocation();
    mVarget VarLatitude();
    mVarget VarLongitude();
    mVarget VarTimeZone();
    mVarget VarUTCTimeOffset();
    mVarget VarDaylightTimeOffset();
    mVarget VarStandardTimeOffset();
    mVarget VarGreenwichMeanSideralTime();
    // EARTH
    mVarget VarEarthMeanEccentricity();
    mVarget VarEarthNutationLongitude();
    mVarget VarEarthNutationObliquity();
    mVarget VarEarthMeanObliquity();
    mVarget VarEarthTrueObliquity();
    // SUN
    mVarget VarSunMeanLongitude();
    mVarget VarSunMeanAnomaly();
    mVarget VarSunCenter();
    mVarget VarSunTrueLongitude();
    mVarget VarSunTrueAnomaly();
    mVarget VarSunApparentLongitude();
    mVarget VarSunRadiusVector();
    mVarget VarSunNutationAberrationCorrection();
    mVarget VarSunRightAscension();
    mVarget VarSunApparentRightAscension();
    mVarget VarSunDeclination();
    mVarget VarSunApparentDeclination();
    mVarget VarSunRise();
    mVarget VarSunTransit();
    mVarget VarSunSet();
    // MOON
    mVarget VarMoonMeanLongitude();
    mVarget VarMoonMeanAnomaly();
    mVarget VarMoonMeanElongation();
    mVarget VarMoonMeanDistanceFromAscendantNode();
    mVarget VarMoonMeanLongitudeFromAscendantNode();

private:
    QDateTime dt;
    Location location;
    QTimeZone tz;
};

//******************************************************************************
// Class Sun
//******************************************************************************
class Sun
{
public:
    static double MeanLongitude(double JD);                           // L0
    static double MeanAnomaly(double JD);                             // M
    static double Center(double JD, double MeanAnomaly);              // C
    static double TrueLongitude(double MeanLongitude, double Center); // Θ
    static double TrueAnomaly(double MeanAnomaly, double Center);     // ν
    static double ApparentLongitude(double TrueLongitude, double NutationAberrationCorrection); // λ
    static double RadiusVector(double MeanEccentricity, double TrueAnomaly);                    // R
    static double NutationAberrationCorrection(double JD); // Ω
    static double RightAscension(double TrueObliquity, double TrueLongitude); // α
    static double Declination(double TrueObliquity, double TrueLongitude);    // δ
    static double ApparentRightAscension(double TrueObliquity,
                                         double ApparentLongitude,
                                         double NutationAberrationCorrection); // αapp
    static double ApparentDeclination(double TrueObliquity,
                                      double ApparentLongitude,
                                      double NutationAberrationCorrection); // δapp
};

//******************************************************************************
// Class Moon
//******************************************************************************
class Moon
{
public:
    static double MeanLongitude(double JD);                  // L'
    static double MeanAnomaly(double JD);                    // M'
    static double MeanElongation(double JD);                 // D
    static double MeanDistanceFromAscendantNode(double JD);  // F
    static double MeanLongitudeFromAscendantNode(double JD); // Ω
};

//******************************************************************************
// Class Earth
//******************************************************************************
class Earth
{
public:
    static double MeanEccentricity(double JD); // e
    static double NutationLongitude(double JD,
                                    double SunMeanLongitude,
                                    double MoonMeanLongitude,
                                    double SunMeanAnomaly,
                                    double MoonMeanAnomaly,
                                    double MoonMeanLongitudeFromAscendantNode); // Δψ
    static double NutationObliquity(double JD,
                                    double SunMeanLongitude,
                                    double MoonMeanLongitude,
                                    double SunMeanAnomaly,
                                    double MoonMeanAnomaly,
                                    double MoonMeanLongitudeFromAscendantNode);  // Δε
    static double MeanObliquity(double JD);                                      // ε0
    static double TrueObliquity(double MeanObliquity, double NutationObliquity); // ε = ε0 + Δε
};

//******************************************************************************
// Class PlanetaryOrbits
//******************************************************************************
class PlanetaryOrbits
{
public:
    QString Planet;
    double MeanLongitude(double T, double a0, double a1, double a2, double a3);
    double SemiMajorAxisOrbit(double T, double a0, double a1, double a2, double a3);
    double EccentricityOrbit(double T, double a0, double a1, double a2, double a3);
    double InclinationPlaneEcliptic(double T, double a0, double a1, double a2, double a3);
    double LongitudeAscendingNode(double T, double a0, double a1, double a2, double a3);
    double LongitudePerihelion(double T, double a0, double a1, double a2, double a3);
};

//******************************************************************************
// Misc General Purpose Functions defined outside the Class
//******************************************************************************
double frac(double d);
double DHMS2DD(int d, int h, int m, int s);
std::tuple<int, int, int, int> DD2DHMS(double dd);
std::tuple<int, int, int, int> HD2HMS(double hd);
double DMS2DD(int d, int m, int s);
std::tuple<int, int, int, int> DD2DMS(double dd);
double deg2rad(double d);
double rad2deg(double r);
double reduceAngle(double a);
QString printDMS(double a);
QString printHMS(double a);
double Polynomial(double ind, vCoefs coefs);
double constrain(double v);

#endif  // MEEUS_H
