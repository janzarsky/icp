#pragma once
#include "Command.hpp"

namespace solitaire
{
    enum UICommandType {
        help, game_cmd, new_game, close_game, switch_game, games, quit, empty,
        invalid
    };

    struct UICommand
    {
        UICommandType type;
        int switch_to;
        Command game_cmd;

        UICommand(UICommandType type): type{type}, game_cmd{} {}
        UICommand() {}
    };

    class TextUIParser
    {
    public:
        UICommand getCommand();
    };
}
