#pragma once

namespace solitaire
{
    // deck = balicek vlevo nahore
    // final = 4 hromadky vpravo nahore
    // pile = 7 hromadek dole
    enum CommandType {
        turn_deck, // otoc kartu z balicku
        move_deck_pile, // presun z balicku do pile
        move_deck_final,
        move_pile_pile,
        move_pile_final,
        turn_pile // otoc kartu z pile, ktera je byla otocena dolu
    };

    struct Command
    {
        CommandType type;
        Command(CommandType t): type{t} {}
        Command() {}
    };
}
