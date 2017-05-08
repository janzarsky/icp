/**
 * @file    TUIParser.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Commandline interface parser
 */

#include <string>
#include "Command.hpp"

using namespace std;

namespace solitaire
{
    /**
     * TUI command type
     * 
     * All game commands (move, turn) are game_cmd type.
     */
    enum TUICommandType {
        help, game_cmd, new_game, close_game, switch_game, save, load, games,
        undo, hint, quit, empty, invalid
    };

    /**
     * TUI command
     * 
     * Used for storing game commands (move, turn) and general commands (new
     * game, close game, ...)
     */
    struct TUICommand
    {
        TUICommandType type;
        int switch_to;
        Command game_cmd;
        string filename;

        TUICommand(TUICommandType type): type{type}, game_cmd{} {}
        TUICommand() {}
    };

    /**
     * TUI parser
     * 
     * Reads command from user and creates TUICommand instance
     */
    class TUIParser
    {
    public:
        TUICommand getCommand();
    };
}
