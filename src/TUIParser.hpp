#pragma once
#include <string>
#include "Command.hpp"

using namespace std;

namespace solitaire
{
    enum TUICommandType {
        help, game_cmd, new_game, close_game, switch_game, save, load, games,
        undo, quit, empty, invalid
    };

    struct TUICommand
    {
        TUICommandType type;
        int switch_to;
        Command game_cmd;
        string filename;

        TUICommand(TUICommandType type): type{type}, game_cmd{} {}
        TUICommand() {}
    };

    class TUIParser
    {
    public:
        TUICommand getCommand();
    };
}
