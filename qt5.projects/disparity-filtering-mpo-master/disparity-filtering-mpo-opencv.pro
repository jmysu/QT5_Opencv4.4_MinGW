#-------------------------------------------------
#
#      Disparity and depth maps with OpenCV
#
#    by AbsurdePhoton - www.absurdephoton.fr
#
#                v1.3 - 2019/06/03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = disparity-filtering-mpo-opencv
TEMPLATE = app

#LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

SOURCES +=  main.cpp\
            mainwindow.cpp \
            mpo.cpp \
            mat-image-tools.cpp \
    disparity.cpp \
    adjust.cpp

HEADERS  += mainwindow.h \
            mpo.h \
            mat-image-tools.h \
    disparity.h \
    adjust.h

FORMS    += mainwindow.ui \
    disparity.ui \
    adjust.ui

# we add the package opencv to pkg-config
#CONFIG += link_pkgconfig
#PKGCONFIG += opencv4
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
        -lopencv_videoio440 \
        -lopencv_ximgproc440 \
        -lopencv_stereo440
     }
}

QMAKE_CXXFLAGS += -std=c++11

# icons
RESOURCES += resources.qrc
