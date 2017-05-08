######################################################################
# Automatically generated by qmake (3.1) Wed May 3 13:27:42 2017
######################################################################

TEMPLATE = app
DESTDIR = ..
INCLUDEPATH += .
QT += widgets svg gui
RESOURCES += resources.qrc
TARGET = hra2017

CONFIG += c++11

# Input
HEADERS += Card.hpp \
           Command.hpp \
           Game.hpp \
           GUIApp.hpp \
           GUICard.hpp \
           GUIGame.hpp \
           Pile_interface.hpp \
           Pile_Factory.hpp \
           Piles.hpp \
           TUIGame.hpp \
           TUIApp.hpp \
           TUIParser.hpp
SOURCES += Card.cpp \
           Game.cpp \
           GUIApp.cpp \
           GUICard.cpp \
           GUIGame.cpp \
           Main.cpp \
           TUIGame.cpp \
           TUIApp.cpp \
           TUIParser.cpp
