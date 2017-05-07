#include <iostream>
#include "TextApp.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    TextApp::TextApp(int argc, char *argv[]) {
        cout << "(constructor TextApp, argc=" << argc << ", argv=" << argv << ")" << endl;

        listenToCommands();
    }

    void TextApp::listenToCommands() {
        cout << "listenToCommands()" << endl;

        UICommand cmd;
        
        while (true) {
            try {
                cmd = parser.getCommand();

                if (cmd.type == quit)
                    return;

                executeCommand(cmd);
            }
            catch (InvalidActionException& e) {
                cout << "ERROR: Invalid command: " << e.message() << endl;
            }
        }
    }

    void TextApp::executeCommand(UICommand cmd) {
        switch (cmd.type) {
            case invalid:
                cout << "ERROR: invalid command, type 'help' to show all commands" << endl;
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

            case game_cmd:
                gameUIs[active_game - 1]->executeCommand(cmd.game_cmd);
                printActiveBoard();
                break;

            default:
                cout << "got command: " << cmd.type << endl;
                printActiveBoard();
                break;
        }
    }

    void TextApp::printActiveBoard() {
        if (active_game > 0) {
            cout << "Game number " << active_game << " board:" << endl;

            gameUIs[active_game - 1]->printBoard();
        }
    }

    void TextApp::printHelp() {
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
    }

    void TextApp::newGame() {
        if (gameUIs.size() < max_num_of_games)
            gameUIs.push_back(unique_ptr<GameUI>(new GameUI()));
        else
            throw InvalidActionException("Reached maximum number of games");

        active_game = gameUIs.size();

        cout << "Created game number " << active_game << endl;
    }

    void TextApp::closeGame() {
        gameUIs.erase(gameUIs.begin() + active_game - 1);

        cout << "Game number " << active_game << " closed" << endl;

        active_game = gameUIs.size();
    }

    void TextApp::switchGame(unsigned int game_num) {
        if (game_num == 0 || game_num > gameUIs.size())
            throw InvalidActionException("Invalid game number");

        active_game = game_num;

        cout << "Switched to game number " << active_game << endl;
    }

    void TextApp::saveGame(string filename) {
        try {
            gameUIs[active_game - 1]->saveGame(filename);
        }
        catch (invalid_argument& e) {
            throw InvalidActionException("Error while saving game");
        }
    }

    void TextApp::loadGame(string filename) {
        if (gameUIs.size() >= max_num_of_games)
            throw InvalidActionException("Reached maximum number of games");

        try {
            gameUIs.push_back(unique_ptr<GameUI>(new GameUI(filename)));
        }
        catch (invalid_argument& e) {
            throw InvalidActionException("Error while loading game");
        }

        active_game = gameUIs.size();

        cout << "Loaded game number " << active_game << endl;
    }

    void TextApp::printGames() {
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

