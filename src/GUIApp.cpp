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

        QScrollArea *scroll = new QScrollArea();
        scroll->setWidgetResizable(true);
        scroll->setWidget(window);

        newGameAct = new QAction("&New Game");
        newGameAct->setShortcuts(QKeySequence::New);
        connect(newGameAct, SIGNAL(triggered()), this, SLOT(newGameMenu()));

        loadGameAct = new QAction("&Load Game");
        loadGameAct->setShortcuts(QKeySequence::Open);
        connect(loadGameAct, SIGNAL(triggered()), this, SLOT(loadGame()));

        saveGameAct = new QAction("&Save Game");
        saveGameAct->setShortcuts(QKeySequence::Save);
        connect(saveGameAct, SIGNAL(triggered()), this, SLOT(saveGame()));

        closeGameAct = new QAction("&Close Game");
        closeGameAct->setShortcuts(QKeySequence::Close);
        connect(closeGameAct, SIGNAL(triggered()), this, SLOT(closeGame()));

        gameMenu = menuBar()->addMenu("&Game");
        gameMenu->addAction(newGameAct);
        gameMenu->addAction(loadGameAct);
        gameMenu->addAction(saveGameAct);
        gameMenu->addAction(closeGameAct);

		setCentralWidget(scroll);
		show();
	}

    void GUIMainWindow::newGameMenu() {
        newGame("");
    }

	void GUIMainWindow::newGame(string filename) {
		unsigned int size = gameUIs.size();

        if (size >= max_num_of_games)
            return;
		
		GUIGame *game;
        
        if (filename == "")
            game = new GUIGame();
        else
            try {
                game = new GUIGame(filename);
            }
            catch (invalid_argument& e) {
                // TODO
                return;
            }

		gameUIs.push_back(game);
		
        if (size == 0) {
		    gamesGrid.addWidget(game, 0, 0);
        }
        else if (size == 1) {
		    gamesGrid.addWidget(game, 0, 1);

            placeholder1 = new QWidget();
            gamesGrid.addWidget(placeholder1, 1, 0);

            placeholder2 = new QWidget();
            gamesGrid.addWidget(placeholder2, 1, 1);
        }
        else if (size == 2) {
            gamesGrid.removeWidget(placeholder1);
		    gamesGrid.addWidget(game, 1, 0);
        }
        else if (size == 3) {
            gamesGrid.removeWidget(placeholder2);
		    gamesGrid.addWidget(game, 1, 1);
        }
	}

    void GUIMainWindow::closeGame() {
		unsigned int size = gameUIs.size();

        if (size == 0)
            return;
		
		QWidget *w = gameUIs.back();
        gameUIs.pop_back();

		gamesGrid.removeWidget(w);

        if (size == 4) {
            placeholder2 = new QWidget();
            gamesGrid.addWidget(placeholder2, 1, 1);
        }
        else if (size == 3) {
            placeholder1 = new QWidget();
            gamesGrid.addWidget(placeholder1, 1, 0);
        }
        else if (size == 2) {
            gamesGrid.removeWidget(placeholder1);
            gamesGrid.removeWidget(placeholder2);
        }

        delete w;
    }

    void GUIMainWindow::loadGame() {
        QString filename = QFileDialog::getOpenFileName(this, "Load Game", "./", "Solitaire games (*.solitaire)");

        if (filename == "")
            return;

        // TODO use active game
        newGame(filename.toLocal8Bit().constData());
    }

    void GUIMainWindow::saveGame() {
        QString filename = QFileDialog::getSaveFileName(this, "Save Game", "./game.solitaire", "Solitaire games (*.solitaire)");

        // TODO use active game
        gameUIs.back()->saveGame(filename.toLocal8Bit().constData());
    }
}

