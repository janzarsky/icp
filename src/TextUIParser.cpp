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

        string cmd_str;

        getline(ss, cmd_str, ' ');

        if (cmd_str == "help")
            cmd.type = help;
        else if (cmd_str == "exit")
            cmd.type = exit;
        else
            cmd.type = invalid;

        return cmd;
    }
}
