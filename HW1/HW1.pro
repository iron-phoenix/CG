#-------------------------------------------------
#
# Project created by QtCreator 2014-12-28T01:18:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HW1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    v1.vert \
    f1.frag \
    f2.frag \
    v2.vert \
    f3.frag \
    v3.vert

RESOURCES += \
    shaders.qrc
