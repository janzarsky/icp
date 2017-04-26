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

            if (cmd.type == exit)
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

            case exit:
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
    }
}

