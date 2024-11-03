QT       += core gui network sql widgets

GIT_HASH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --short HEAD)\\\""
GIT_BRANCH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --abbrev-ref HEAD)\\\""
linux-g++*: BUILD_TIMESTAMP="\\\"$$system(date -u +\""%Y-%m-%dT%H:%M:%SUTC\"")\\\""
win32:      BUILD_TIMESTAMP="\\\"$$system(echo %date%-%time: =0%)\\\""
DEFINES += GIT_HASH=$$GIT_HASH GIT_BRANCH=$$GIT_BRANCH BUILD_TIMESTAMP=$$BUILD_TIMESTAMP

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DlgInputLocation.cpp \
    Meeus.cpp \
    app.cpp \
    constants.cpp \
    downloader.cpp \
    main.cpp \
    MainWindow.cpp \
    settings.cpp \
    utils.cpp

HEADERS += \
    DlgInputLocation.h \
    MainWindow.h \
    Meeus.h \
    app.h \
    constants.h \
    downloader.h \
    settings.h \
    utils.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ephemeeus.qrc

DISTFILES += \
    db/cities.db \
    dox/en/country.md \
    dox/en/date-time.md \
    dox/en/day-of-week.md \
    dox/en/julian-day.md \
    dox/en/latitude.md \
    dox/en/location.md \
    dox/en/longitude.md \
    dox/en/moon-distance-from-ascendant-node.md \
    dox/en/moon-mean-anomaly.md \
    dox/en/moon-mean-elongation.md \
    dox/en/moon-mean-longitude-from-ascendant-node.md \
    dox/en/moon-mean-longitude.md \
    dox/en/sun-apparent-longitude.md \
    dox/en/sun-center.md \
    dox/en/sun-mean-anomaly.md \
    dox/en/sun-mean-longitude.md \
    dox/en/sun-nutation-aberration-correction.md \
    dox/en/sun-radius-vector.md \
    dox/en/sun-true-anomaly.md \
    dox/en/sun-true-longitude.md \
    dox/en/t2000.md \
    dox/en/time-zone.md
