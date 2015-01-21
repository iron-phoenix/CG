#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T06:39:18
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fractal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    f1.frag \
    v1.vert

RESOURCES += \
    shaders.qrc
