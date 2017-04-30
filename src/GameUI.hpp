#include <iostream>
#include <string>
#include "Game.hpp"
#include "Card.hpp"
#include "Command.hpp"

using namespace std;

namespace solitaire
{
    class GameUI
    {
        GAME game;
        string unicode(card& card);
        string unicode_back();
        string unicode_empty();
        string unicode_space();

    public:
        GameUI();
        void printBoard();
        void executeCommand(Command& cmd);
    };
}
