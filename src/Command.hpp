#pragma once

namespace solitaire
{
    // deck = balicek vlevo nahore
    // final = 4 hromadky vpravo nahore
    // pile = 7 hromadek dole
    enum CommandType {
        move_deck_pile, // presun z balicku do pile
        move_deck_home,
        move_pile_pile,
        move_pile_home,
        turn_deck, // otoc kartu z balicku
        turn_pile // otoc kartu z pile, ktera je byla otocena dolu
    };

    struct Command
    {
        CommandType type;
        int from;
        int to;
        int count;

        Command(CommandType t): type{t}, from{0}, to{0}, count{0} {}
        Command() {}
    };
}
