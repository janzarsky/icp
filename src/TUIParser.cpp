/**
 * @file    TUIParser.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Commandline interface parser
 */

#include <iostream>
#include <sstream>
#include <string>
#include "TUIParser.hpp"
#include "Game.hpp"

using namespace std;

namespace solitaire
{
    TUICommand TUIParser::getCommand() {
        TUICommand cmd;

        cout << "solitaire> " << flush;

        string line;

        getline(cin, line);

        stringstream ss{line};

        string str;

        getline(ss, str, ' ');

        // UI commands
        if (str == "help" || str == "h")
            cmd.type = help;
        else if (str == "quit" || str == "q")
            cmd.type = quit;
        else if (str == "new" || str == "n")
            cmd.type = new_game;
        else if (str == "close" || str == "c")
            cmd.type = close_game;
        else if (str == "switch" || str == "s")
            cmd.type = switch_game;
        else if (str == "games" || str == "g")
            cmd.type = games;
        else if (str == "save") {
            cmd.type = save;

            getline(ss, str, ' ');
            cmd.filename = str;
        }
        else if (str == "undo") {
            cmd.type = undo;
        }
        else if (str == "load") {
            cmd.type = load;

            getline(ss, str, ' ');
            cmd.filename = str;
        }
        else if (str == "hint") {
            cmd.type = hint;
        }
        // game commands
        else if (str == "move" || str == "m") {
            cmd.type = game_cmd;
            cmd.game_cmd.type = move;

            try {
                getline(ss, str, ' ');

                if (str == "deck") {
                    cmd.game_cmd.from = NUM_OF_COLUMNS + NUM_OF_HOMES;

                    getline(ss, str, ' ');

                    if (str.substr(0, 4) == "pile") {
                        // move deck pileX
                        cmd.game_cmd.to = stoi(str.substr(4)) - 1;

                        if (cmd.game_cmd.to < 0 || cmd.game_cmd.to >= NUM_OF_COLUMNS)
                            cmd.type = invalid;
                    }
                    else if (str.substr(0, 4) == "home") {
                        // move deck homeX
                        cmd.game_cmd.to = stoi(str.substr(4)) + NUM_OF_COLUMNS - 1;

                        if (cmd.game_cmd.to < NUM_OF_COLUMNS ||
                            cmd.game_cmd.to >= NUM_OF_COLUMNS + NUM_OF_HOMES)
                            cmd.type = invalid;
                    }
                    else {
                        cmd.type = invalid;
                    }

                    cmd.game_cmd.count = 1;
                    
                }
                else if (str.substr(0, 4) == "pile") {
                    cmd.game_cmd.from = stoi(str.substr(4)) - 1;

                    if (cmd.game_cmd.from < 0 || cmd.game_cmd.from >= NUM_OF_COLUMNS)
                        cmd.type = invalid;

                    getline(ss, str, ' ');

                    if (str.substr(0, 4) == "pile") {
                        // move pileX pileX
                        cmd.game_cmd.to = stoi(str.substr(4)) - 1;

                        if (cmd.game_cmd.to < 0 ||
                            cmd.game_cmd.to >= NUM_OF_COLUMNS)
                            cmd.type = invalid;

                        if (ss.eof()) {
                            cmd.game_cmd.count = 1;
                        }
                        else {
                            getline(ss, str);

                            if (str.empty()) {
                                cmd.game_cmd.count = 1;
                            }
                            else {
                                cmd.game_cmd.count = stoi(str);

                                if (cmd.game_cmd.count < 1)
                                    cmd.type = invalid;
                            }
                        }
                    }
                    else if (str.substr(0, 4) == "home") {
                        // move pileX homeX
                        cmd.game_cmd.to = stoi(str.substr(4)) + NUM_OF_COLUMNS - 1;
                        cmd.game_cmd.count = 1;

                        if (cmd.game_cmd.to < NUM_OF_COLUMNS ||
                            cmd.game_cmd.to >= NUM_OF_COLUMNS + NUM_OF_HOMES)
                            cmd.type = invalid;
                    }
                    else {
                        cmd.type = invalid;
                    }
                }
                else {
                    cmd.type = invalid;
                }
            }
            catch (out_of_range& e) {
                cmd.type = invalid;
            }
            catch (invalid_argument& e) {
                cmd.type = invalid;
            }
        }
        else if (str == "turn" || str == "t") {
            cmd.type = game_cmd;
            cmd.game_cmd.type = turn;
            cmd.game_cmd.count = 1;
        }
        // other commands
        else if (str == "")
            cmd.type = empty;
        else
            cmd.type = invalid;

        if (cmd.type == switch_game) {
            getline(ss, str, ' ');

            try {
                cmd.switch_to = stoi(str);
            }
            catch (invalid_argument& e) {
                throw invalid_argument("Expected argument");
            }
        }

        return cmd;
    }
}

