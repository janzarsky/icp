#include <iostream>
#include <sstream>
#include <string>
#include "TextUIParser.hpp"

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

        if (str == "help")
            cmd.type = help;
        else if (str == "quit")
            cmd.type = quit;
        else if (str == "new")
            cmd.type = new_game;
        else if (str == "close")
            cmd.type = close_game;
        else if (str == "switch")
            cmd.type = switch_game;
        else if (str == "games")
            cmd.type = games;
        else
            cmd.type = invalid;

        if (cmd.type == switch_game) {
            getline(ss, str, ' ');

            cmd.switch_to = stoi(str);
        }

        return cmd;
    }
}
