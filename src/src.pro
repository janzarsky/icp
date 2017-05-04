######################################################################
# Automatically generated by qmake (3.1) Wed May 3 13:27:42 2017
######################################################################

TEMPLATE = app
DESTDIR = ..
INCLUDEPATH += .
QT += widgets

gui {
TARGET = hra2017
}

tui {
TARGET = hra2017-cli
DEFINES += TUI
}

# Input
HEADERS += Card.hpp \
           Command.hpp \
           Exceptions.hpp \
           Game.hpp \
           GameUI.hpp \
           GUIApp.hpp \
           Pile.hpp \
           Pile_interface.hpp \
           Piles.hpp \
           TextApp.hpp \
           TextUIParser.hpp
SOURCES += Card.cpp \
           Game.cpp \
           GameUI.cpp \
           GUIApp.cpp \
           GUIGame.cpp \
           Main.cpp \
           Pile.cpp \
           TextApp.cpp \
           TextUIParser.cpp