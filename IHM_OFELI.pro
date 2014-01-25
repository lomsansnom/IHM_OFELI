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
    dialogaddcomment.cpp

HEADERS  += mainwindow.h\
        ui_mainwindow.h \
    dialogexec.h \
    ui_dialogexec.h \
    ui_dialogresults.h \
    dialogaddnode.h \
    dialogmodifynode.h \
    dialogsave.h \
    dialogaddcomment.h
FORMS    += mainwindow.ui \
    dialogexec.ui \
    dialogaddnode.ui \
    dialogmodifynode.ui \
    dialogsave.ui \
    dialogaddcomment.ui

RC_FILE = IHM_OFELI.rc
ICON = icon.icns
