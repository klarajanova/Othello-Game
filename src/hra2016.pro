TEMPLATE = app
TARGET = hra2016
DESTDIR = ../build
OBJECTS_DIR = ../build/.hra2016/.obj
QT += core widgets
CONFIG += c++11 release

HEADERS += core/ai.h \
           core/board.h \
           core/field.h \
           core/game.h \
           core/move.h \
           core/moves.h \
           core/player.h \
           dialog/game_status.h \
           dialog/history.h \
           dialog/new_game.h \
           gui/gui_game.h \
           gui/othello.h
SOURCES += core/ai.cpp \
           core/board.cpp \
           core/field.cpp \
           core/game.cpp \
           core/move.cpp \
           core/moves.cpp \
           core/player.cpp \
           dialog/game_status.cpp \
           dialog/history.cpp \
           dialog/new_game.cpp \
           gui/gui_game.cpp \
           gui/main.cpp \
           gui/othello.cpp
