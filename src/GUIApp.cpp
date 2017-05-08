/**
 * @file    GUIApp.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Main window containing games and menu bar
 */

#include <QtWidgets/QScrollArea>
#include <QString>
#include "GUIApp.hpp"

using namespace std;

namespace solitaire
{
    /**
     * Create GUI app and execute it
     */
    GUIApp::GUIApp(int argc, char *argv[]): QApplication(argc, argv) {
        mainWindow = new GUIMainWindow();

        exec();
    }

    /**
     * Create main window
     */
	GUIMainWindow::GUIMainWindow() {
        resize(QDesktopWidget().availableGeometry(this).size() * 0.8);

        gamesGrid.setSizeConstraint(QLayout::SetMinimumSize);
        gamesGrid.setContentsMargins(0, 0, 0, 0);
        gamesGrid.setSpacing(10);
        
		QWidget *window = new QWidget();
		window->setLayout(&gamesGrid);

        QScrollArea *scroll = new QScrollArea();
        scroll->setWidgetResizable(true);
        scroll->setWidget(window);

        undoGameAct = new QAction("&Undo");
        undoGameAct->setShortcuts(QKeySequence::Undo);
        connect(undoGameAct, SIGNAL(triggered()), this, SLOT(undoGame()));

        hintGameAct = new QAction("&Show hint");
        hintGameAct->setShortcut(QKeySequence("Ctrl+H"));
        connect(hintGameAct, SIGNAL(triggered()), this, SLOT(hintGame()));

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

        quitAct = new QAction("&Quit");
        quitAct->setShortcuts(QKeySequence::Quit);
        connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

        gameMenu = menuBar()->addMenu("&Game");
        gameMenu->addAction(undoGameAct);
        gameMenu->addAction(hintGameAct);
        gameMenu->addSeparator();
        gameMenu->addAction(newGameAct);
        gameMenu->addAction(loadGameAct);
        gameMenu->addAction(saveGameAct);
        gameMenu->addAction(closeGameAct);
        gameMenu->addSeparator();
        gameMenu->addAction(quitAct);

		setCentralWidget(scroll);
		show();
	}

    /**
     * Create new game
     */
    void GUIMainWindow::newGameMenu() {
        newGame("");
    }

    /**
     * Create new game and load state from file
     *
     * @param filename file name
     *
     * If the game cannot be loaded message is shown
     */
	void GUIMainWindow::newGame(string filename) {
		unsigned int size = gameUIs.size();

        int cardSize;
        
        if (size == 0)
            cardSize = largeCardSize;
        else
            cardSize = smallCardSize;

        if (size >= max_num_of_games)
            return;
		
		GUIGame *game;
        
        if (filename == "") {
            game = new GUIGame(cardSize);
        }
        else {
            try {
                game = new GUIGame(cardSize, filename);
            }
            catch (invalid_argument& e) {
                QMessageBox msg;
                msg.setText("Could not load game!");
                msg.exec();

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

        if (gameUIs.size() > 1) {
            for (unsigned int i = 0; i < gameUIs.size(); i++)
                if (i != active_game - 1) {
                    gameUIs[i]->setCardSize(smallCardSize);
                }
        }
	}

    /**
     * Close active game
     *
     * If there is no active game, nothing happens
     */
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

        // initialize with large enough number so in case of trouble the second
        // for loop will be skipped
        int hole = gameUIs.size();

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

        // correct card size
        if (gameUIs.size() == 1) {
            gameUIs[0]->setCardSize(largeCardSize);
        }
    }

    /**
     * Show file dialog and load selected game
     */
    void GUIMainWindow::loadGame() {
        QString filename = QFileDialog::getOpenFileName(this, "Load Game", "./", "Solitaire games (*.solitaire);;All files (*.*)");

        if (filename == "")
            return;

        newGame(filename.toLocal8Bit().constData());
    }

    /**
     * Show file dialog and save active game
     *
     * If there is no active game, nothing happens.
     */
    void GUIMainWindow::saveGame() {
        if (active_game == 0)
            return;

        QString filename = QFileDialog::getSaveFileName(this, "Save Game", "./game.solitaire", "Solitaire games (*.solitaire);;All files (*.*)");

        gameUIs[active_game - 1]->saveGame(filename.toLocal8Bit().constData());
    }

    /**
     * Revert last move in active game
     *
     * If there is no active game, nothing happens.
     */
    void GUIMainWindow::undoGame() {
        if (active_game == 0)
            return;

        gameUIs[active_game - 1]->undoGame();
    }

    /**
     * Show possible move in active game
     *
     * If there is no active game, nothing happens.
     */
    void GUIMainWindow::hintGame() {
        if (active_game == 0)
            return;

        gameUIs[active_game - 1]->hintGame();
    }

    /**
     * Set sender of this signal as an active game
     */
    void GUIMainWindow::activeGame() {
        GUIGame *game = qobject_cast<GUIGame *>(sender());

        for (unsigned int i = 0; i < gameUIs.size(); i++) {
            if (gameUIs[i] == game)
                active_game = i + 1;
        }

        setActiveGame();
    }

    /**
     * Update game interfaces so that they know if they are active
     */
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

    /**
     * Quit application
     */
    void GUIMainWindow::quit() {
        QApplication::quit();
    }
}

