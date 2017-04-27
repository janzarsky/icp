#include <iostream>
#include <string>
#include "Game.hpp"

using namespace std;

namespace solitaire
{
    class GameUI
    {
        Game game;
        string unicode(pair<int,int>);

    public:
        GameUI();
        void printBoard();
    };
}
