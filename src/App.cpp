#include <iostream>
#include "App.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    App::App() {
        cout << "(constructor App)\n";

        listenToCommands();
    }

    void App::listenToCommands() {
        cout << "listenToCommands()\n";

        UICommand cmd;
        
        while (true) {
            try {
                cmd = parser.getCommand();

                if (cmd.type == quit)
                    return;

                executeCommand(cmd);
            }
            catch (InvalidActionException& e) {
                cout << "Invalid command: " << e.message() << "\n";
            }
        }
    }

    void App::executeCommand(UICommand cmd) {
        switch (cmd.type) {
            case invalid:
                cout << "invalid command, type 'help' to show all commands\n";
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

            case games:
                printGames();
                break;

            default:
                cout << "got command: " << cmd.type << "\n";
                printActiveBoard();
                break;
        }
    }

    void App::printActiveBoard() {
        if (active_game > 0) {
            cout << "Game number " << active_game << " board:\n";

            gameUIs[active_game - 1].printBoard();
        }
    }

    void App::printHelp() {
        cout << "help - show this help\n";
        cout << "new - start a new game\n";
        cout << "close - close active game\n";
        cout << "switch <num> - switch to game number <num>\n";
        cout << "games - list currently played games\n";
        cout << "quit - quit the app\n";
    }

    void App::newGame() {
        GameUI new_game;

        if (gameUIs.size() < max_num_of_games)
            gameUIs.push_back(new_game);
        else
            throw InvalidActionException("Reached maximum number of games");

        active_game = gameUIs.size();

        cout << "Created game number " << active_game << "\n";
    }

    void App::closeGame() {
        gameUIs.erase(gameUIs.begin() + active_game - 1);

        cout << "Game number " << active_game << " closed\n";

        active_game = gameUIs.size();
    }

    void App::switchGame(int game_num) {
        if (game_num <= 0 || game_num > gameUIs.size())
            throw InvalidActionException("Invalid game number");

        active_game = game_num;

        cout << "Switched to game number " << active_game << "\n";
    }

    void App::printGames() {
        if (gameUIs.size() == 0) {
            cout << "No games are currently played\n";
            return;
        }

        cout << "Games number ";

        for (int i = 1; i <= gameUIs.size(); i++)
            cout << i << ", ";

        cout << "are currently played\n";
    }
}

