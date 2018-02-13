#-------------------------------------------------
#
# Project created by QtCreator 2017-12-02T12:59:03
#
#-------------------------------------------------

QT += core gui
QT += widgets
QT += network

TARGET = client
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    loading.cpp

HEADERS  += mainwindow.h \
    commands.h \
    game.h \
    loading.h

FORMS    += mainwindow.ui \
    loading.ui
