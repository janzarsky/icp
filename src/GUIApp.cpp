#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include <QPalette>
#include "GUIApp.hpp"
#include "Game.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    GUIApp::GUIApp(int argc, char *argv[]): app{argc, argv} {
        cout << "(constructor GUIApp)\n";
		initLayout();
    }

	void GUIApp::initLayout() {
        gamesGrid.setSizeConstraint(QLayout::SetMinimumSize);

        addGame();
        addGame();
        addGame();

		QWidget *window = new QWidget();
		window->setLayout(&gamesGrid);

		mainWindow.setCentralWidget(window);
		mainWindow.show();

		app.exec();
	}

	void GUIApp::addGame() {
		unsigned int size = gameUIs.size();

        if (size >= max_num_of_games)
            throw InvalidActionException("Reached maximum number of games");
		
		GUIGame *game = new GUIGame();

		gameUIs.push_back(game);
		
		int x = 0;
		int y = 0;

		switch (size) {
			case 0:
				x = 0;
				y = 0;
				break;
			case 1:
				x = 1;
				y = 0;
				break;
			case 2:
				x = 0;
				y = 1;
				break;
			case 3:
				x = 1;
				y = 1;
				break;
		}

		gamesGrid.addWidget(game, x, y);

/*
        QPalette pal;
        pal.setColor(QPalette::Background, QColor::fromRgb(0,255,0));

        QLabel *l = new QLabel("asdf");
        l->setAutoFillBackground(true);
        l->setPalette(pal);

        gamesGrid.addWidget(l, x, y);
        */
	}
}

