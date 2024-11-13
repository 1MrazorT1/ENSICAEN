QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

TARGET = GrandPrix
TEMPLATE = app
CONFIG += c++11

DEFINES += GP_VERSION=4.0.4

INCLUDEPATH += include
SOURCES += \
    src/logger.cpp \
    src/main.cpp\
    src/grandprix.cpp \
    src/gpcontrolview.cpp \
    src/gpmapview.cpp \
    src/gpmapselector.cpp \
    src/gpcontrol.cpp \
    src/gpdriverselector.cpp \
    src/finishdialog.cpp \
    src/gpprogression.cpp \
    src/car.cpp \
    src/headless.cpp \
    src/stderrview.cpp

HEADERS  += \
    include/grandprix.h \
    include/gpcontrolview.h \
    include/gpmapview.h \
    include/gpmapselector.h \
    include/gpcontrol.h \
    include/gpdriverselector.h \
    include/finishdialog.h \
    include/gpprogression.h \
    include/car.h \
    include/headless.h \
    include/logger.h \
    include/stderrview.h

FORMS    += \
    ui/grandprix.ui \
    ui/gpcontrolview.ui \
    ui/gpmapview.ui \
    ui/gpmapselector.ui \
    ui/gpdriverselector.ui \
    ui/finishdialog.ui \
    ui/gpprogression.ui \
    ui/stderrview.ui

RESOURCES += res.qrc

OBJECTS_DIR=.obj
MOC_DIR=.moc
UI_DIR=.ui
RCC_DIR=.rcc

# QMAKE_CXXFLAGS_DEBUG += -fsanitize=address
# QMAKE_LFLAGS_DEBUG +=  -fsanitize=address
