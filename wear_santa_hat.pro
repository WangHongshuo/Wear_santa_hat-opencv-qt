#-------------------------------------------------
#
# Project created by QtCreator 2017-12-24T20:41:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wear_santa_hat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ImageWidget.cpp \
    mat_qimage_convert.cpp \
    selectrect.cpp \
    wearsantahat.cpp

HEADERS += \
        mainwindow.h \
    ImageWidget.h \
    mat_qimage_convert.h \
    selectrect.h \
    wearsantahat.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += D:/opencv3.4/opencv_use/include\
               D:/opencv3.4/opencv_use/include/opencv\
               D:/opencv3.4/opencv_use/include/opencv2
LIBS += -L D:/opencv3.4/opencv_use/lib/libopencv_*.a
