TEMPLATE = app
TARGET = hra2016-cli
DESTDIR = ../build
OBJECTS_DIR = ../build/.hra2016-cli/.obj
QT += core widgets
CONFIG += console c++11 release

HEADERS += core/ai.h \
           core/board.h \
           core/field.h \
           core/game.h \
           core/move.h \
           core/moves.h \
           core/player.h
SOURCES += cli/main.cpp \
           core/ai.cpp \
           core/board.cpp \
           core/field.cpp \
           core/game.cpp \
           core/move.cpp \
           core/moves.cpp \
           core/player.cpp
