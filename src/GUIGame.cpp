#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "GUIGame.hpp"

using namespace std;

namespace solitaire
{
    GUIGame::GUIGame(): QBoxLayout{QBoxLayout::TopToBottom} {
        cout << "(constructor GUIGame)\n";
        initLayout();
    }

    void GUIGame::initLayout() {
        QLabel *l = new QLabel("asdf");
        l->show();
        addWidget(l);
    }
}
