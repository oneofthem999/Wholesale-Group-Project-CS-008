TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    product.cpp \
    inventory.cpp \
    testfile.cpp \
    purchase.cpp \
    member.cpp

HEADERS += \
    thelist.h \
    thenode.h \
    product.h \
    inventory.h \
    purchase.h \
    member.h
