QT += testlib core gui

CONFIG += qt warn_on console
TEMPLATE = app

# Файл с тестами
SOURCES += \
    tst_equipmentmodel.cpp

# Подключаем исходники практики 2
INCLUDEPATH += \
    ../practic_2_lab

SOURCES += \
    ../practic_2_lab/equipmentmodel.cpp

HEADERS += \
    ../practic_2_lab/equipmentmodel.h
