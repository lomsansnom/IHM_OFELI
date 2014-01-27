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
    dialogaddnode.cpp \
    dialogmodifynode.cpp \
    dialogsave.cpp \
    dialogaddcomment.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
        ui_mainwindow.h \
    dialogexec.h \
    ui_dialogexec.h \
    dialogaddnode.h \
    ui_dialogaddnode.h \
    dialogmodifynode.h \
    ui_dialogmodifynode.h \
    dialogsave.h \
    ui_dialogsave.h \
    dialogaddcomment.h \
    ui_dialogaddcomment.h \
    dialogabout.h \
    ui_dialogabout.h
FORMS    += mainwindow.ui \
    dialogexec.ui \
    dialogaddnode.ui \
    dialogmodifynode.ui \
    dialogsave.ui \
    dialogaddcomment.ui \
    dialogabout.ui

RC_FILE = IHM_OFELI.rc
ICON = icon.icns
