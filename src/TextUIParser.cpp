#include <iostream>
#include <sstream>
#include <string>
#include "TextUIParser.hpp"
#include "Exceptions.hpp"

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
            cmd.game_cmd.type = move_deck_pile;
        }
        else if (str == "turn" || str == "t") {
            cmd.type = game_cmd;
            cmd.game_cmd.type = turn_deck;
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

