QT  += core gui network widgets

include(../common/common.pri)

TARGET = client
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    clientwindow.cpp

HEADERS += \
    clientwindow.h
