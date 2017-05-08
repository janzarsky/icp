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
    enum TUICommandType {
        help, game_cmd, new_game, close_game, switch_game, save, load, games,
        undo, hint, quit, empty, invalid
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
