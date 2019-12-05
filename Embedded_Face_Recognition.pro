#-------------------------------------------------
#
# Project created by QtCreator 2019-11-21T18:21:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Embedded_Face_Recognition
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
        recognition_model.cpp \
        facecapture.cpp \
        facecapturemodel.cpp \
        capturer.cpp \
    haar_face_detector.cpp

HEADERS  += mainwindow.h \
            recognition_model.h \
            facecapture.h \
            facecapturemodel.h \
            capturer.h \
    haar_face_detector.h

FORMS    += mainwindow.ui \
            facecapture.ui

QMAKE_CXXFLAGS += -fopenmp

INCLUDEPATH += /usr/include/

LIBS += /usr/lib/libopencv_imgproc.so \
        /usr/lib/libopencv_highgui.so \
        /usr/lib/libopencv_core.so \
        /usr/lib/libopencv_videoio.so \
        /usr/lib/libopencv_ml.so \
        /usr/lib/libopencv_objdetect.so \
        /usr/lib/libopencv_imgcodecs.so \
        -fopenmp
