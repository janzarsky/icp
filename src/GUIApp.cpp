#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QPalette>
#include "GUIApp.hpp"
#include "Game.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    GUIApp::GUIApp(int argc, char *argv[]): QApplication(argc, argv) {
        mainWindow = new GUIMainWindow();

        exec();
    }

	GUIMainWindow::GUIMainWindow() {
        gamesGrid.setSizeConstraint(QLayout::SetMinimumSize);
        gamesGrid.setContentsMargins(0, 0, 0, 0);
        gamesGrid.setSpacing(0);

		QWidget *window = new QWidget();
		window->setLayout(&gamesGrid);

        newGameAct = new QAction("&New Game");
        newGameAct->setShortcuts(QKeySequence::New);
        connect(newGameAct, SIGNAL(triggered()), this, SLOT(newGame()));

        closeGameAct = new QAction("&Close Game");
        closeGameAct->setShortcuts(QKeySequence::Close);
        connect(closeGameAct, SIGNAL(triggered()), this, SLOT(closeGame()));

        gameMenu = menuBar()->addMenu("&Game");
        gameMenu->addAction(newGameAct);
        gameMenu->addAction(closeGameAct);

		setCentralWidget(window);
		show();
	}

	void GUIMainWindow::newGame() {
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
	}

    void GUIMainWindow::closeGame() {
		unsigned int size = gameUIs.size();

        if (size == 0)
            throw InvalidActionException("There is no game played");
		
		QWidget *w = gameUIs.back();
        gameUIs.pop_back();

		gamesGrid.removeWidget(w);

        delete w;
    }

}

