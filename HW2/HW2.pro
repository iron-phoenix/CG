#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T05:07:34
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HW2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    shaders.qrc

OTHER_FILES += \
    f1.frag \
    f2.frag \
    v1.vert \
    v2.vert
