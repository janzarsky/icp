#include <iostream>
#include "App.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    App::App() {
        std::cout << "(constructor App)\n";

        listenToCommands();
    }

    void App::listenToCommands() {
        std::cout << "listenToCommands()\n";

        UICommand cmd;
        
        while (true) {
            cmd = parser.getCommand();

            if (cmd.type == quit)
                return;

            executeCommand(cmd);
        }
    }

    void App::executeCommand(UICommand cmd) {
        switch (cmd.type) {
            case invalid:
                cout << "invalid command, type 'help' to show all commands\n";
                break;

            case help:
                cout << "help - show this help\nexit - exit the app\n";
                break;

            case new_game:
                newGame();
                break;

            case close_game:
                closeGame();
                break;

            case switch_game:
                switchGame(cmd.switch_to);
                break;

            case games:
                printGames();
                break;

            default:
                cout << "got command: " << cmd.type << "\n";
                break;
        }
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

