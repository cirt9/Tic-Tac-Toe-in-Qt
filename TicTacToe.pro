#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T15:22:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacToe
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    button.cpp \
    field.cpp \
    board.cpp \
    player.cpp \
    cpuplayer.cpp

HEADERS  += \
    game.h \
    button.h \
    field.h \
    board.h \
    player.h \
    cpuplayer.h

FORMS    +=
