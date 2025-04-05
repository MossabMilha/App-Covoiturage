QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    checkers.cpp \
    databasemanager.cpp \
    drivercreatetrip.cpp \
    driverhistoryoftraject.cpp \
    driverhomepage.cpp \
    encryption.cpp \
    login.cpp \
    main.cpp \
    passengerhomepage.cpp \
    passengersearchhistory.cpp \
    passengershowsearchresult.cpp \
    search.cpp \
    signup.cpp \
    start.cpp \
    traject.cpp \
    user.cpp

HEADERS += \
    checkers.h \
    databasemanager.h \
    drivercreatetrip.h \
    driverhistoryoftraject.h \
    driverhomepage.h \
    encryption.h \
    login.h \
    passengerhomepage.h \
    passengersearchhistory.h \
    passengershowsearchresult.h \
    search.h \
    signup.h \
    start.h \
    traject.h \
    user.h

FORMS += \
    drivercreatetrip.ui \
    driverhistoryoftraject.ui \
    driverhomepage.ui \
    login.ui \
    passengerhomepage.ui \
    passengersearchhistory.ui \
    passengershowsearchresult.ui \
    signup.ui \
    start.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
