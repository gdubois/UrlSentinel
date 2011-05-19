#-------------------------------------------------
#
# Project created by QtCreator 2010-10-07T12:03:07
#
#-------------------------------------------------

QT       += core gui network

TARGET = UrlSentinel
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    urlcontent.cpp \
    traymenu.cpp \
    trayicon.cpp \
    sitelistwidget.cpp \
    site.cpp \
    sha1.cpp \
    settingspanel.cpp \
    persistentsettings.cpp \
    monitorreferential.cpp \
    global.cpp \
    favicon.cpp \
    centralwidget.cpp

HEADERS  += mainwindow.h \
    urlcontent.h \
    traymenu.h \
    trayicon.h \
    sitelistwidget.h \
    site.h \
    sha1.h \
    settingspanel.h \
    persistentsettings.h \
    monitorreferential.h \
    global.h \
    favicon.h \
    centralwidget.h
