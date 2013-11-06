#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T08:32:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_hack
TEMPLATE = app


SOURCES += main.cpp\
        pixmapwidget.cpp \
    myglwidget.cpp \
    qtlogo.cpp \
    transparentwidget.cpp \
    movablewidget.cpp

HEADERS  += pixmapwidget.h \
    myglwidget.h \
    qtlogo.h \
    transparentwidget.h \
    movablewidget.h

*g++* {
    QMAKE_CXXFLAGS += -std=gnu++0x
}

win32* {
    LIBS += -lglu32 -lopengl32 -lgdi32
}
