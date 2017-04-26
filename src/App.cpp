#include <iostream>
#include "App.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    App::App() {
        std::cout << "(constructor App)\n";
    }

    void App::NewGame() {
        GameUI new_game;

        if (gameUIs.size() < max_num_of_games)
            gameUIs.push_back(new_game);
        else
            throw InvalidActionException("Reached maximum number of games");
    }
}

