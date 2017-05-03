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
        Command() {}
    };
}
