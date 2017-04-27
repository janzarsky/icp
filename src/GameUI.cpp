#include <iostream>
#include "GameUI.hpp"

using namespace std;

namespace solitaire
{
    GameUI::GameUI() {
        cout << "(constructor GameUI)\n";
    }

    void GameUI::printBoard() {
        cout << "//// board ////\n";
    }
}
