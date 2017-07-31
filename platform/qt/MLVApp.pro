#-------------------------------------------------
#
# Project created by QtCreator 2017-07-12T15:09:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "MLV App"
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QMAKE_CFLAGS_RELEASE += -O3 -msse4.1 -mssse3 -msse3 -msse2 -msse
#QMAKE_CXXFLAGS_RELEASE += -O3 -msse4.1 -mssse3 -msse3 -msse2 -msse
#win32: QMAKE_CFLAGS_RELEASE += -msse2 -std=c99
#linux-g++*: QMAKE_CFLAGS_RELEASE += -msse2 -std=c99

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    ../../src/debayer/amaze_demosaic.c \
    ../../src/debayer/debayer.c \
    ../../src/imageio/bitmap/bitmap.c \
    ../../src/matrix/matrix.c \
    ../../src/mlv/camera_matrices.c \
    ../../src/mlv/frame_caching.c \
    ../../src/mlv/video_mlv.c \
    ../../src/processing/processing.c \
    ../../src/processing/raw_processing.c \
    InfoDialog.cpp \
    StatusDialog.cpp \
    Histogram.cpp \
    WaveFormMonitor.cpp


HEADERS += \
        MainWindow.h \
    ../../src/debayer/debayer.h \
    ../../src/debayer/helpersse2.h \
    ../../src/imageio/bitmap/bitmap.h \
    ../../src/imageio/structs/imagestruct.h \
    ../../src/imageio/imageio.h \
    ../../src/matrix/matrix.h \
    ../../src/mlv/mlv.h \
    ../../src/mlv/mlv_object.h \
    ../../src/mlv/raw.h \
    ../../src/mlv/video_mlv.h \
    ../../src/processing/processing_object.h \
    ../../src/processing/raw_processing.h \
    ../../src/mlv_include.h \
    InfoDialog.h \
    MyApplication.h \
    StatusDialog.h \
    SystemMemory.h \
    Histogram.h \
    WaveFormMonitor.h


FORMS += \
        MainWindow.ui \
    InfoDialog.ui \
    StatusDialog.ui

RESOURCES += \
    ressources.qrc

QMAKE_INFO_PLIST = Info.plist

DISTFILES += \
    Info.plist \
    FFmpeg/ffmpeg