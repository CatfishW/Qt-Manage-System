QT       += core gui
QT += sql
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../LinearRegression.cpp \
    addinfo.cpp \
    delete_dia.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    predictedchart.cpp \
    query.cpp \
    registerwindow.cpp

HEADERS += \
    ../LinearRegression.h \
    ../Utils.h \
    addinfo.h \
    delete_dia.h \
    loginwindow.h \
    mainwindow.h \
    predictedchart.h \
    query.h \
    registerwindow.h

FORMS += \
    addinfo.ui \
    delete_dia.ui \
    loginwindow.ui \
    mainwindow.ui \
    predictedchart.ui \
    query.ui \
    registerwindow.ui

TRANSLATIONS += \
    GraduateCareerManageSystem_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
