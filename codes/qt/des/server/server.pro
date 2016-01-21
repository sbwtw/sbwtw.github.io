QT  += core gui network widgets

include(../common/common.pri)

TARGET = server
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    serverwindow.cpp

HEADERS += \
    serverwindow.h
