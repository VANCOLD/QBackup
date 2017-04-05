QT += core
QT -= gui

TARGET = QTuxBackup
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    qdirnode.cpp \
    qxmlparser.cpp \
    qbackupmanager.cpp \
    gdrive.cpp \
    qdropbox.cpp

HEADERS += \
    qdirnode.h \
    qxmlparser.h \
    abstractsave.h \
    qbackupmanager.h \
    gdrive.h \
    qdropbox.h
