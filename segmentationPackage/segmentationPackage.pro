#-------------------------------------------------
#
# Project created by QtCreator 2016-09-08T00:28:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = segmentationPackage
TEMPLATE = app

DESTDIR = ../segmentationPackage/lib/

CONFIG += console c++11

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

QMAKE_CXXFLAGS_RELEASE *= -O3

CCFLAG += -O3

INCLUDEPATH += /usr/local/include/opencv /usr/local/include/opencv2

LIBS += -L/usr/local/lib/ -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_objdetect -lopencv_shape -lopencv_video -lopencv_calib3d -lopencv_features2d -lopencv_ml -lopencv_flann -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core


SOURCES += main.cpp\
        mainwindow.cpp \
    meanshiftsegmentation.cpp \
    egbis.cpp \
    graphcut.cpp \
    gco/GCoptimization.cpp \
    gco/graph.cpp \
    gco/LinkedBlockList.cpp \
    gco/maxflow.cpp \
    seamcarving.cpp \
    bg_sub.cpp \
    motion_seg.cpp

HEADERS  += mainwindow.h \
    meanshiftsegmentation.h \
    egbis.h \
    egbis/convolve.h \
    egbis/disjoint-set.h \
    egbis/filter.h \
    egbis/image.h \
    egbis/imconv.h \
    egbis/imutil.h \
    egbis/misc.h \
    egbis/pnmfile.h \
    egbis/segment-graph.h \
    egbis/segment-image.h \
    graphcut.h \
    gco/block.h \
    gco/energy.h \
    gco/GCoptimization.h \
    gco/graph.h \
    gco/LinkedBlockList.h \
    seamcarving.h \
    bg_sub.h \
    motion_seg.h

FORMS    += mainwindow.ui \
    meanshiftsegmentation.ui \
    graphcut.ui \
    seamcarving.ui

DISTFILES += \
    segmentationPackage/lib/segmentationPackage \
    gco/GCO_README.TXT \
    egbis/COPYING

RESOURCES += segmentationPackage.qrc
