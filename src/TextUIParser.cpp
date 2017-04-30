#include <iostream>
#include <sstream>
#include <string>
#include "TextUIParser.hpp"
#include "Exceptions.hpp"
#include "Game.hpp"

using namespace std;

namespace solitaire
{
    UICommand TextUIParser::getCommand() {
        UICommand cmd;

        cout << "solitaire> ";

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
        // game commands
        else if (str == "move" || str == "m") {
            cmd.type = game_cmd;

            try {
                getline(ss, str, ' ');

                if (str == "deck") {
                    getline(ss, str, ' ');

                    if (str.substr(0, 4) == "pile") {
                        // move deck pileX
                        cmd.game_cmd.type = move_deck_pile;
                        cmd.game_cmd.to = stoi(str.substr(4));

                        if (cmd.game_cmd.to < 1 || cmd.game_cmd.to > NUM_OF_COLUMNS)
                            cmd.type = invalid;
                    }
                    else if (str.substr(0, 4) == "home") {
                        // move deck homeX
                        cmd.game_cmd.type = move_deck_home;
                        cmd.game_cmd.to = stoi(str.substr(4));

                        if (cmd.game_cmd.to < 1 || cmd.game_cmd.to > NUM_OF_HOMES)
                            cmd.type = invalid;
                    }
                    else {
                        cmd.type = invalid;
                    }
                    
                }
                else if (str.substr(0, 4) == "pile") {
                    getline(ss, str, ' ');
                    
                    cmd.game_cmd.from = stoi(str.substr(4));

                    if (cmd.game_cmd.from < 1 || cmd.game_cmd.from > NUM_OF_COLUMNS)
                        cmd.type = invalid;

                    if (str.substr(0, 4) == "pile") {
                        // move pileX pileX
                        cmd.game_cmd.type = move_pile_pile;
                        cmd.game_cmd.to = stoi(str.substr(4));

                        if (cmd.game_cmd.to < 1 || cmd.game_cmd.to > NUM_OF_COLUMNS)
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
                            }
                        }
                    }
                    else if (str.substr(0, 4) == "home") {
                        // move pileX homeX
                        cmd.game_cmd.type = move_pile_home;
                        cmd.game_cmd.to = stoi(str.substr(4));

                        if (cmd.game_cmd.to < 1 || cmd.game_cmd.to > NUM_OF_HOMES)
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

            try {
                getline(ss, str, ' ');

                if (str == "deck") {
                    // turn deck
                    cmd.game_cmd.type = turn_deck;
                }
                else if (str.substr(0, 4) == "pile") {
                    // turn pileX
                    cmd.game_cmd.from = stoi(str.substr(4));

                    if (cmd.game_cmd.from < 1 || cmd.game_cmd.from > NUM_OF_COLUMNS)
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
                throw InvalidActionException("Expected argument");
            }
        }

        return cmd;
    }
}

