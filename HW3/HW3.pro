#-------------------------------------------------
#
# Project created by QtCreator 2015-01-05T15:13:21
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HW3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    v2.vert \
    v1.vert \
    f2.frag

DISTFILES += \
    fragment.frag \
    vertex.vert
