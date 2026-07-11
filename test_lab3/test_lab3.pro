QT += core testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++17
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../practika_lab

SOURCES += \
    tst_bookingservice.cpp \
    ../practika_lab/bookingservice.cpp

HEADERS += \
    ../practika_lab/booking.h \
    ../practika_lab/bookingservice.h
