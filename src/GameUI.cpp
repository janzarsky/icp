#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "GameUI.hpp"
#include "Card.hpp"
#include "Command.hpp"

using namespace std;

namespace solitaire
{
    GameUI::GameUI() {
        cout << "(constructor GameUI)\n";
    }

    string GameUI::unicode() {
        return "\U0001F0A0";
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
        // dummy content
        card deck_fronts = {CLUBS,3};
        card target_decks[4] = { {CLUBS,1}, {CLUBS,1}, {CLUBS,1}, {CLUBS,1} };
        vector<card> working_decks[7];
        working_decks[0].push_back({SPADES,1});
        working_decks[1].push_back({CLUBS,1});
        working_decks[1].push_back({SPADES,1});
        working_decks[2].push_back({CLUBS,1});
        working_decks[2].push_back({CLUBS,1});
        working_decks[2].push_back({SPADES,1});
        working_decks[3].push_back({CLUBS,1});
        working_decks[3].push_back({CLUBS,1});
        working_decks[3].push_back({CLUBS,1});
        working_decks[3].push_back({SPADES,1});
        working_decks[4].push_back({CLUBS,1});
        working_decks[4].push_back({CLUBS,1});
        working_decks[4].push_back({CLUBS,1});
        working_decks[4].push_back({CLUBS,1});
        working_decks[4].push_back({SPADES,1});
        working_decks[5].push_back({CLUBS,1});
        working_decks[5].push_back({CLUBS,1});
        working_decks[5].push_back({CLUBS,1});
        working_decks[5].push_back({CLUBS,1});
        working_decks[5].push_back({CLUBS,1});
        working_decks[5].push_back({SPADES,2});
        working_decks[6].push_back({CLUBS,1});
        working_decks[6].push_back({CLUBS,1});
        working_decks[6].push_back({CLUBS,1});
        working_decks[6].push_back({CLUBS,1});
        working_decks[6].push_back({CLUBS,1});
        working_decks[6].push_back({CLUBS,1});
        working_decks[6].push_back({SPADES,3});

        cout << unicode() << " " << unicode(deck_fronts) << "   ";

        for (int i = 0; i < 4; i++)
            cout << unicode(target_decks[i]) << " ";

        cout << "\n\n";

        int max_height = 0;
        int sizes[8];
        
        for (int i = 0; i < 7; i++) {
            sizes[i] = working_decks[i].size();

            if (sizes[i] > max_height)
                max_height = sizes[i];
        }

        for (int i = 0; i < max_height; i++) {
            for (int j = 0; j < 7; j++) {
                if (i < sizes[j])
                    cout << unicode(working_decks[j][i]) << " ";
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
