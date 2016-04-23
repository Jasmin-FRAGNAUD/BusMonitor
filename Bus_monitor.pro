
TEMPLATE = app
QT += network widgets
TARGET = BusMonitor
DEPENDPATH += ./
INCLUDEPATH += ./
CONFIG += release

# Input
HEADERS += fenetre_bm.h
FORMS += fenetre_bm.ui
SOURCES += fenetre_bm.cpp main.cpp
