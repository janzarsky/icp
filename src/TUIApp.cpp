/**
 * @file    TUIApp.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Commandline interface
 */

#include <iostream>
#include "TUIApp.hpp"

using namespace std;

namespace solitaire
{
    TUIApp::TUIApp() {
        listenToCommands();
    }

    /**
     * Listen to commands in a loop and execute them
     */
    void TUIApp::listenToCommands() {
        TUICommand cmd;
        
        while (true) {
            try {
                cmd = parser.getCommand();

                if (cmd.type == quit)
                    return;

                executeCommand(cmd);
            }
            catch (invalid_argument& e) {
                cout << "ERROR: Invalid command: " << e.what() << endl;
                printActiveBoard();
            }
        }
    }

    /**
     * Execute command
     * 
     * @param cmd   TUICommand obtained from TUIParser
     * 
     * Game commands (move, turn) are passed to active game UI.
     */
    void TUIApp::executeCommand(TUICommand cmd) {
        switch (cmd.type) {
            case invalid:
                cout << "ERROR: invalid command, type 'help' to show all commands" << endl;
                printActiveBoard();
                break;

            case empty:
                printActiveBoard();
                break;

            case help:
                printHelp();
                break;

            case new_game:
                newGame();
                printActiveBoard();
                break;

            case close_game:
                closeGame();
                break;

            case switch_game:
                switchGame(cmd.switch_to);
                printActiveBoard();
                break;

            case save:
                saveGame(cmd.filename);
                printActiveBoard();
                break;

            case load:
                loadGame(cmd.filename);
                printActiveBoard();
                break;

            case games:
                printGames();
                break;

            case undo:
                gameUIs[active_game - 1]->undo();
                printActiveBoard();
                break;

            case hint:
                gameUIs[active_game - 1]->hint();
                printActiveBoard();
                break;

            case game_cmd:
                gameUIs[active_game - 1]->executeCommand(cmd.game_cmd);

                if (gameUIs[active_game - 1]->hasEnded()) {
                    cout << "Congratulations, game finished!" << endl;
                    closeGame();
                }

                printActiveBoard();

                break;

            default:
                throw invalid_argument("Unknown command");
                break;
        }
    }

    /**
     * Print active board
     * 
     * Uses active_game, if active_game is 0 nothing happens
     */
    void TUIApp::printActiveBoard() {
        if (active_game == 0)
            return;

        cout << "Game number " << active_game << " board:" << endl;

        gameUIs[active_game - 1]->printBoard();
    }

    /**
     * Print help
     */
    void TUIApp::printHelp() {
        cout << "General commands:" << endl;
        cout << "help      show this help" << endl;
        cout << "new       start a new game" << endl;
        cout << "close     close active game" << endl;
        cout << "switch N  switch to game number N (1-4)" << endl;
        cout << "games     list currently played games" << endl;
        cout << "quit      quit the app" << endl;

        cout << endl << "Game commands:" << endl;
        cout << "move deck pileX     move card from deck to pile (1-7)" << endl;
        cout << "move deck homeX     move card from deck to home (1-4)" << endl;
        cout << "move pileX homeX    move card from pile (1-7) to home (1-4)" << endl;
        cout << "move pileX pileX N  move N cards (default is 1) from pile"
             << "(1-7) to another pile (1-7)" << endl;
        cout << "turn                turn 1 card from pile" << endl;
        cout << "undo                revert last move" << endl;
        cout << "hint                show possible move" << endl;
    }

    /**
     * Create new game
     *
     * @throws std::invalid_argument game cannot be created
     */
    void TUIApp::newGame() {
        if (gameUIs.size() < max_num_of_games)
            gameUIs.push_back(unique_ptr<TUIGame>(new TUIGame()));
        else
            throw invalid_argument("Reached maximum number of games");

        active_game = gameUIs.size();

        cout << "Created game number " << active_game << endl;
    }

    /**
     * Close active game
     *
     * @throws std::invalid_argument there is no active game
     */
    void TUIApp::closeGame() {
        if (active_game == 0)
            throw invalid_argument("No game played");

        gameUIs.erase(gameUIs.begin() + active_game - 1);

        cout << "Game number " << active_game << " closed" << endl;

        active_game = gameUIs.size();
    }

    /**
     * Switch to game
     *
     * @param game_num game number (usually 1 - 4)
     * @throws std::invalid_argument there is no game with number @p game_num
     */
    void TUIApp::switchGame(unsigned int game_num) {
        if (game_num == 0 || game_num > gameUIs.size())
            throw invalid_argument("Invalid game number");

        active_game = game_num;

        cout << "Switched to game number " << active_game << endl;
    }

    /**
     * Save active game to file
     *
     * @param filename file name
     * @throws std::invalid_argument there is no active game or the game cannot be saved
     */
    void TUIApp::saveGame(string filename) {
        if (active_game == 0)
            throw invalid_argument("No game played");

        try {
            gameUIs[active_game - 1]->saveGame(filename);
        }
        catch (invalid_argument& e) {
            throw invalid_argument("Error while saving game");
        }
    }

    /**
     * Create new game and load game state from file
     *
     * @param filename file name
     * @throws std::invalid_argument new game cannot be created or there is
     *      error reading the file
     */
    void TUIApp::loadGame(string filename) {
        if (gameUIs.size() >= max_num_of_games)
            throw invalid_argument("Reached maximum number of games");

        try {
            gameUIs.push_back(unique_ptr<TUIGame>(new TUIGame(filename)));
        }
        catch (invalid_argument& e) {
            throw invalid_argument("Error while loading game");
        }

        active_game = gameUIs.size();

        cout << "Loaded game number " << active_game << endl;
    }

    /**
     * Print list of currently played games
     */
    void TUIApp::printGames() {
        if (gameUIs.size() == 0) {
            cout << "No games are currently played" << endl;
            return;
        }

        cout << "Games number ";

        for (unsigned int i = 1; i <= gameUIs.size(); i++)
            cout << i << ", ";

        cout << "are currently played" << endl;
    }
}

