#pragma once
#include <string>
#include "Command.hpp"

using namespace std;

namespace solitaire
{
    enum UICommandType {
        help, game_cmd, new_game, close_game, switch_game, save, load, games,
        undo, quit, empty, invalid
    };

    struct UICommand
    {
        UICommandType type;
        int switch_to;
        Command game_cmd;
        string filename;

        UICommand(UICommandType type): type{type}, game_cmd{} {}
        UICommand() {}
    };

    class TUIParser
    {
    public:
        UICommand getCommand();
    };
}
