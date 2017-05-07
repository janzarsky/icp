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

        undoGameAct = new QAction("&Undo");
        undoGameAct->setShortcuts(QKeySequence::Undo);
        connect(undoGameAct, SIGNAL(triggered()), this, SLOT(undoGame()));

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
        gameMenu->addAction(undoGameAct);
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
        
        if (filename == "") {
            game = new GUIGame();
        }
        else {
            try {
                game = new GUIGame(filename);
            }
            catch (invalid_argument& e) {
                // TODO
                return;
            }
        }

		gameUIs.push_back(game);

        active_game = gameUIs.size();

        connect(game, &GUIGame::activated, this, &GUIMainWindow::activeGame);
		
        for (unsigned int i = 0; i < max_num_of_games; i++) {
            if (gameSlots[i] == 0) {
                gamesGrid.addWidget(game, i/game_cols, i%game_cols);

                gameSlots[i] = active_game;
                break;
            }
        }

        setActiveGame();
	}

    void GUIMainWindow::closeGame() {
		unsigned int size = gameUIs.size();

        if (size == 0)
            return;

        if (active_game == 0)
            return;

		QWidget *w = gameUIs[active_game - 1];

        gameUIs.erase(gameUIs.begin() + active_game - 1);

		gamesGrid.removeWidget(w);

        delete w;

        int hole;

        // correct game slots
        for (unsigned int i = 0; i < max_num_of_games; i++) {
            if (gameSlots[i] == active_game) {
                hole = i;
                gameSlots[i] = 0;
            }
            else if (gameSlots[i] > active_game) {
                gameSlots[i]--;
            }
        }

        // correct holes in game grid
        for (unsigned int i = hole + 1; i < gameUIs.size() + 1; i++) {
            gamesGrid.removeWidget(gameUIs[gameSlots[i] - 1]);
            gamesGrid.addWidget(gameUIs[gameSlots[i] - 1], (i - 1)/game_cols, (i - 1)%game_cols);

            gameSlots[i - 1] = gameSlots[i];
            gameSlots[i] = 0;
        }

        // correct active game
        for (unsigned int i = max_num_of_games; i > 0; i--) {
            if (gameSlots[i - 1] != 0) {
                active_game = gameSlots[i - 1];
                setActiveGame();
                break;
            }
        }
    }

    void GUIMainWindow::loadGame() {
        QString filename = QFileDialog::getOpenFileName(this, "Load Game", "./", "Solitaire games (*.solitaire)");

        if (filename == "")
            return;

        newGame(filename.toLocal8Bit().constData());
    }

    void GUIMainWindow::saveGame() {
        if (active_game == 0)
            return;

        QString filename = QFileDialog::getSaveFileName(this, "Save Game", "./game.solitaire", "Solitaire games (*.solitaire)");

        gameUIs[active_game - 1]->saveGame(filename.toLocal8Bit().constData());
    }

    void GUIMainWindow::undoGame() {
        if (active_game == 0)
            return;

        gameUIs[active_game - 1]->undoGame();
    }

    void GUIMainWindow::activeGame() {
        GUIGame *game = qobject_cast<GUIGame *>(sender());

        for (unsigned int i = 0; i < gameUIs.size(); i++) {
            if (gameUIs[i] == game)
                active_game = i + 1;
        }

        setActiveGame();
    }

    void GUIMainWindow::setActiveGame() {
        for (unsigned int i = 0; i < gameUIs.size(); i++) {
            if (i == active_game - 1) {
                gameUIs[i]->setActive(true);
            }
            else {
                gameUIs[i]->setActive(false);
            }
        }
    }
}

