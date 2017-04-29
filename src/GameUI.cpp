#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "GameUI.hpp"
#include "Card.hpp"
#include "Command.hpp"
#include "Game.hpp"

using namespace std;

namespace solitaire
{
    GameUI::GameUI() {
        cout << "(constructor GameUI)\n";
    }

    string GameUI::unicode_back() {
        return "\U0001F0A0";
    }

    string GameUI::unicode_empty() {
        return "\U0001F0DF";
    }

    string GameUI::unicode(card& card) {
        static const char * unicodes[14][4] = {
            { "\U0001F0A1", "\U0001F0B1", "\U0001F0C1", "\U0001F0D1" },
            { "\U0001F0A2", "\U0001F0B2", "\U0001F0C2", "\U0001F0D2" },
            { "\U0001F0A3", "\U0001F0B3", "\U0001F0C3", "\U0001F0D3" },
            { "\U0001F0A4", "\U0001F0B4", "\U0001F0C4", "\U0001F0D4" },
            { "\U0001F0A5", "\U0001F0B5", "\U0001F0C5", "\U0001F0D5" },
            { "\U0001F0A6", "\U0001F0B6", "\U0001F0C6", "\U0001F0D6" },
            { "\U0001F0A7", "\U0001F0B7", "\U0001F0C7", "\U0001F0D7" },
            { "\U0001F0A8", "\U0001F0B8", "\U0001F0C8", "\U0001F0D8" },
            { "\U0001F0A9", "\U0001F0B9", "\U0001F0C9", "\U0001F0D9" },
            { "\U0001F0AA", "\U0001F0BA", "\U0001F0CA", "\U0001F0DA" },
            { "\U0001F0AB", "\U0001F0BB", "\U0001F0CB", "\U0001F0DB" },
            { "\U0001F0AC", "\U0001F0BC", "\U0001F0CC", "\U0001F0DC" },
            { "\U0001F0AD", "\U0001F0BD", "\U0001F0CD", "\U0001F0DD" },
            { "\U0001F0AE", "\U0001F0BE", "\U0001F0CE", "\U0001F0DE" },
        };

        return unicodes[card.getValue()][card.getSuit()];
    }

    void GameUI::printBoard() {
        card deck_fronts = game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back();

        cout << unicode_back() << " ";

        if (game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().size() > 0)
            cout << unicode(game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back());
        else
            cout << unicode_empty();

        cout << "   ";

        for (int i = 0; i < NUM_OF_HOMES; i++)
            if (game.piles[NUM_OF_COLUMNS + i].GetPile().size() > 0)
                cout << unicode(game.piles[NUM_OF_COLUMNS + i].GetPile().back()) << " ";
            else
                cout << unicode_empty() << " ";

        cout << "\n\n";

        int max_height = 0;
        int sizes[NUM_OF_COLUMNS];
        
        for (int i = 0; i < NUM_OF_COLUMNS; i++) {
            sizes[i] = game.piles[i].GetPile().size();

            if (sizes[i] > max_height)
                max_height = sizes[i];
        }

        for (int i = 0; i < max_height; i++) {
            for (int j = 0; j < NUM_OF_COLUMNS; j++) {
                if (i < sizes[j])
                    cout << unicode(game.piles[j].GetPile()[i]) << " ";
                else
                    cout << "  ";
            }

            cout << "\n";
        }

        cout << "\n";
    }

    void GameUI::executeCommand(Command& cmd) {
        cout << "executing game comand type " << cmd.type << "\n";
    }
}
