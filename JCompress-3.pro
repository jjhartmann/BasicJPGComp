#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T10:22:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JCompress-3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    compression.cpp \
    umatrix.cpp \
    blocktransform.cpp

HEADERS  += mainwindow.h \
    compression.h \
    umatrix.h \
    blocktransform.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../opt/local/lib/release/ -lopencv_core -lopencv_calib3d -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videostab
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../opt/local/lib/debug/ -lopencv_core -lopencv_calib3d -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videostab
else:unix: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lopencv_core -lopencv_calib3d -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videostab

INCLUDEPATH += $$PWD/../../../../../../opt/local/include/
DEPENDPATH += $$PWD/../../../../../../opt/local/include/

