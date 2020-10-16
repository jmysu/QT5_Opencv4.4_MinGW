#-------------------------------------------------
#
# Project created by QtCreator 2019-10-29T09:10:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpencvCameraNI2
TEMPLATE = app
DESTDIR  = ..

CONFIG  += -std=c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp

HEADERS +=

FORMS +=

win32 {
    DEFINES += OPENCV440
    contains(DEFINES, "OPENCV440") {
     warning("Opencv440")
     INCLUDEPATH += D:\opencv440\install\include
     LIBS += -LD:\opencv440\install\x64\mingw\bin \
        -lopencv_core440 \
        -lopencv_highgui440 \
        -lopencv_imgproc440 \
        -lopencv_features2d440 \
        -lopencv_calib3d440 \
        -lopencv_imgcodecs440 \
        -lopencv_video440 \
        -lopencv_videoio440

     INCLUDEPATH +=  D:\OpenNI2\Include
     LIBS += -LD:\OpenNI2\Lib \
        -lopenni2
     }
}

DISTFILES +=
