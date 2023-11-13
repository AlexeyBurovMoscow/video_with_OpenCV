#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T10:16:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SearchGUI
TEMPLATE = app

CONFIG += C++11

SOURCES += main.cpp\
        searchgui.cpp \
    GUI/renderwindow.cpp \
    Core/capturemodule.cpp \
    GUI/selectionwindow.cpp \
    GUI/controlwindow.cpp

HEADERS  += searchgui.h \
    GUI/renderwindow.h \
    Core/capturemodule.h \
    GUI/selectionwindow.h \
    Core/irenderprocess.h \
    GUI/controlwindow.h

FORMS    += searchgui.ui

INCLUDEPATH += D:\OpenCV\install\include

OPENCVPATH = D:\OpenCV

LIBS += $$OPENCVPATH\bin\libopencv_core310.dll
LIBS += $$OPENCVPATH\bin\libopencv_calib3d310.dll
LIBS += $$OPENCVPATH\bin\libopencv_features2d310.dll
LIBS += $$OPENCVPATH\bin\libopencv_flann310.dll
LIBS += $$OPENCVPATH\bin\libopencv_highgui310.dll
LIBS += $$OPENCVPATH\bin\libopencv_objdetect310.dll
LIBS += $$OPENCVPATH\bin\libopencv_video310.dll
LIBS += $$OPENCVPATH\bin\libopencv_videoio310.dll
LIBS += $$OPENCVPATH\bin\libopencv_videostab310.dll
LIBS += $$OPENCVPATH\bin\opencv_ffmpeg310.dll
LIBS += $$OPENCVPATH\bin\libopencv_imgproc310.dll
LIBS += $$OPENCVPATH\bin\libopencv_imgcodecs310.dll
LIBS += $$OPENCVPATH\bin\libopencv_ml310.dll

RESOURCES += \
    res.qrc
