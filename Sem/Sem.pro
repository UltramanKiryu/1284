TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        binary_sem.c \
        main.c

HEADERS += \
    binary_sem.h \
    semun.h
