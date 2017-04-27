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
        Game game;
        string unicode(card& card);
        string unicode();

    public:
        GameUI();
        void printBoard();
        void executeCommand(Command& cmd);
    };
}
