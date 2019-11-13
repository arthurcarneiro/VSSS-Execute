#-------------------------------------------------
#
# Project created by QtCreator 2019-07-23T00:36:14
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisionSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        configuracao.cpp \
    constantes_campo.cpp \
    players_config.cpp

INCLUDEPATH +=C:\opencv\build\include # C:\OpenCV3\opencv\opencv_bin2\install\include

LIBS += -L"C:\opencv-build\install\x86\mingw\bin"
LIBS += -llibopencv_core320 -llibopencv_highgui320 -llibopencv_imgproc320 -llibopencv_features2d320 -llibopencv_calib3d320 -llibopencv_imgcodecs320 -llibopencv_video320 -llibopencv_videoio320 -llibopencv_videostab320

HEADERS += \
        mainwindow.h \
        configuracao.h \
    constantes_campo.h \
    players_config.h

FORMS += \
        mainwindow.ui \
        configuracao.ui




