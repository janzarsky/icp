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
        return "\U0001F0A0 ";
    }

    string GameUI::unicode_empty() {
        return "[]";
    }

    string GameUI::unicode_space() {
        return "  ";
    }

    string GameUI::unicode(card& card) {
        string res;

		switch (card.getValue()) {
            case 11:
                res = "J";
                break;
            case 12:
                res = "Q";
                break;
            case 13:
                res = "K";
                break;
            case 1:
                res = "A";
                break;
            default:
                res = (card.getValue() + '0' - 1);
                break;
		}

		switch (card.getSuit()) {
            case CLUBS:
                res += "\u2663";
                break;
            case DIAMONDS:
                res += "\u2666";
                break;
            case HEARTS:
                res += "\u2665";
                break;
            case SPADES:
                res += "\u2660";
                break;
            default:
                res += "UNKNOWN";
                break;
		}
        
        return res;
    }

    void GameUI::printBoard() {
        card deck_fronts = game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES]->GetPile().back();

        cout << unicode_back() << " ";

        if (game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES]->GetPile().size() > 0)
            cout << unicode(game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES]->GetPile().back()) << " ";
        else
            cout << unicode_empty() << " ";

        cout << unicode_space() << " ";

        for (int i = 0; i < NUM_OF_HOMES; i++)
            if (game.piles[NUM_OF_COLUMNS + i]->GetPile().size() > 0)
                cout << unicode(game.piles[NUM_OF_COLUMNS + i]->GetPile().back()) << " ";
            else
                cout << unicode_empty() << " ";

        cout << "\n\n";

        int max_height = 0;
        int sizes[NUM_OF_COLUMNS];
        
        for (int i = 0; i < NUM_OF_COLUMNS; i++) {
            sizes[i] = game.piles[i]->GetPile().size();

            if (sizes[i] > max_height)
                max_height = sizes[i];
        }

        for (int i = 0; i < max_height; i++) {
            for (int j = 0; j < NUM_OF_COLUMNS; j++) {
                if (i < sizes[j])
                    cout << unicode(game.piles[j]->GetPile()[i]) << " ";
                else
                    cout << unicode_space() << " ";
            }

            cout << "\n";
        }

        cout << "\n";
    }

    void GameUI::executeCommand(Command& cmd) {
        cout << "EXECUTE: ";

        if (cmd.type == move)
            cout << "move, from " << cmd.from << ", to " <<
                cmd.to << ", count " << cmd.count;
        else if (cmd.type == turn)
            cout << "turn";
        else
            cout << "unknown";

        cout << "\n";
    }
}
