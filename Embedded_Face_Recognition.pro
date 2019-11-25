#-------------------------------------------------
#
# Project created by QtCreator 2019-11-21T18:21:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Embedded_Face_Recognition
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        recognition_model.cpp

HEADERS  += mainwindow.h \
    recognition_model.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/

LIBS += /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_videoio.so
