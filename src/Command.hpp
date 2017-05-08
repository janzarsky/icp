/**
 * @file    Command.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Structure for communication between user interface and game logic
 */

#pragma once

namespace solitaire
{
    enum CommandType
    {
        move,
        turn
    };

    struct Command
    {
        CommandType type;
        int from;
        int to;
        int count;
		bool revealed;

        Command(CommandType t):
			type{t}, from{0}, to{0}, count{0}, revealed{false} {}
        Command():
            type{move}, from{0}, to{0}, count{0}, revealed{false} {}
    };
}
