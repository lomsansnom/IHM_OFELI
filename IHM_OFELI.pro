#-------------------------------------------------
#
# Project created by QtCreator 2013-10-08T13:24:32
#
#-------------------------------------------------

QT += core
QT += gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM_OFELI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogexec.cpp \
    dialogresults.cpp \
    dialogaddnode.cpp \
    dialogmodifynode.cpp

HEADERS  += mainwindow.h\
        ui_mainwindow.h \
    dialogexec.h \
    ui_dialogexec.h \
    dialogresults.h \
    ui_dialogresults.h \
    dialogaddnode.h \
    dialogmodifynode.h
FORMS    += mainwindow.ui \
    dialogexec.ui \
    dialogresults.ui \
    dialogaddnode.ui \
    dialogmodifynode.ui
