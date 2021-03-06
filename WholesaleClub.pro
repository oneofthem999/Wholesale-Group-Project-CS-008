#-------------------------------------------------
#
# Project created by QtCreator 2017-03-19T16:13:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WholesaleClub
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    member.cpp \
    purchase.cpp \
    inventory.cpp \
    item.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    member.h \
    thelist.h \
    thenode.h \
    purchase.h \
    inventory.h \
    item.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
