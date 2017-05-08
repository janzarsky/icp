#include <iostream>
#include <string>
#include "Game.hpp"
#include "Card.hpp"
#include "Command.hpp"

using namespace std;

namespace solitaire
{
    class TUIGame
    {
        GAME game;
        string unicode(card& card);
        string unicode_back();
        string unicode_empty();
        string unicode_space();

    public:
        TUIGame();
        TUIGame(string filename);
        void printBoard();
        void undo();
        void executeCommand(Command& cmd);
        void saveGame(string filename);
    };
}
