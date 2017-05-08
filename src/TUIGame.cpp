/**
 * @file    TUIGame.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Commandline game interface
 */

#include <iostream>
#include <sstream>
#include <vector>
#include "TUIGame.hpp"

using namespace std;

namespace solitaire
{
    /**
     * Create new TUI game
     */
    TUIGame::TUIGame() {}

    /**
     * Load game from file
     */
    TUIGame::TUIGame(string filename): game{filename} {}

    /**
     * Get string for card back
     */
    string TUIGame::unicode_back() {
        return " \U0001F0A0 ";
    }

    /**
     * Get string for empty card
     */
    string TUIGame::unicode_empty() {
        return "[ ]";
    }

    /**
     * Get string for no card
     */
    string TUIGame::unicode_space() {
        return "   ";
    }

    /**
     * Get string for card
     */
    string TUIGame::unicode(card& card) {
        string res;

		switch (card.getValue()) {
            case 10:
                res = "10";
                break;
            case 11:
                res = " J";
                break;
            case 12:
                res = " Q";
                break;
            case 13:
                res = " K";
                break;
            case 1:
                res = " A";
                break;
            default:
                res = (card.getValue() + '0');
                res = " " + res;
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

    /**
     * Print game board
     */
    void TUIGame::printBoard() {
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

            cout << endl;
        }

        cout << endl;
    }

    /**
     * Revert last move
     */
    void TUIGame::undo() {
        game.Backward();
    }

    /**
     * Show possible move
     */
    void TUIGame::hint() {
        int from = 0;
        int to = 0;

        game.Help(from, to);

        if (from == 0 && to == 0) {
            cout << "Unable to show hint" << endl;
        }
        else if (from == 12 && to == 12) {
            cout << "Turn deck" << endl;
        }
        else {
            cout << "Move some cards from ";

            if (from <= NUM_OF_COLUMNS)
                cout << "pile" << from;
            else if (from <= NUM_OF_COLUMNS + NUM_OF_HOMES)
                cout << "home" << from - NUM_OF_COLUMNS;
            else
                cout << "deck";

            cout << " to ";

            if (to <= NUM_OF_COLUMNS)
                cout << "pile" << to;
            else if (to <= NUM_OF_COLUMNS + NUM_OF_HOMES)
                cout << "home" << to - NUM_OF_COLUMNS;

            cout << endl;
        }
    }

    /**
     * Execute game command
     *
     * @param cmd game command
     */
    void TUIGame::executeCommand(Command& cmd) {
        cmd.from++;
        cmd.to++;

        if (!game.End)
            game.Play(cmd);
    }

    /**
     * Save game to file
     *
     * @param filename file name
     */
    void TUIGame::saveGame(string filename) {
        game.Save(filename);
    }

    /**
     * Has game ended?
     */
    bool TUIGame::hasEnded() {
        return game.End;
    }
}
