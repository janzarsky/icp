#include <iostream>
#include "TextApp.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    TextApp::TextApp() {
        cout << "(constructor TextApp)\n";

        listenToCommands();
    }

    void TextApp::listenToCommands() {
        cout << "listenToCommands()\n";

        UICommand cmd;
        
        while (true) {
            try {
                cmd = parser.getCommand();

                if (cmd.type == quit)
                    return;

                executeCommand(cmd);
            }
            catch (InvalidActionException& e) {
                cout << "ERROR: Invalid command: " << e.message() << "\n";
            }
        }
    }

    void TextApp::executeCommand(UICommand cmd) {
        switch (cmd.type) {
            case invalid:
                cout << "ERROR: invalid command, type 'help' to show all commands\n";
                break;

            case empty:
                printActiveBoard();
                break;

            case help:
                printHelp();
                break;

            case new_game:
                newGame();
                printActiveBoard();
                break;

            case close_game:
                closeGame();
                break;

            case switch_game:
                switchGame(cmd.switch_to);
                printActiveBoard();
                break;

            case games:
                printGames();
                break;

            case game_cmd:
                gameUIs[active_game].executeCommand(cmd.game_cmd);
                break;

            default:
                cout << "got command: " << cmd.type << "\n";
                printActiveBoard();
                break;
        }
    }

    void TextApp::printActiveBoard() {
        if (active_game > 0) {
            cout << "Game number " << active_game << " board:\n";

            gameUIs[active_game - 1].printBoard();
        }
    }

    void TextApp::printHelp() {
        cout << "General commands:\n";
        cout << "help      show this help\n";
        cout << "new       start a new game\n";
        cout << "close     close active game\n";
        cout << "switch N  switch to game number N (1-4)\n";
        cout << "games     list currently played games\n";
        cout << "quit      quit the app\n";

        cout << "\nGame commands:\n";
        cout << "move deck pileX     move card from deck to pile (1-7)\n";
        cout << "move deck homeX     move card from deck to home (1-4)\n";
        cout << "move pileX homeX    move card from pile (1-7) to home (1-4)\n";
        cout << "move pileX pileX N  move N cards (default is 1) from pile"
             << "(1-7) to another pile (1-7)\n";
        cout << "turn deck           turn 1 card from the deck\n";
        cout << "turn pileX          turn 1 card from pile (1-7)\n";
    }

    void TextApp::newGame() {
        GameUI new_game;

        if (gameUIs.size() < max_num_of_games)
            gameUIs.push_back(new_game);
        else
            throw InvalidActionException("Reached maximum number of games");

        active_game = gameUIs.size();

        cout << "Created game number " << active_game << "\n";
    }

    void TextApp::closeGame() {
        gameUIs.erase(gameUIs.begin() + active_game - 1);

        cout << "Game number " << active_game << " closed\n";

        active_game = gameUIs.size();
    }

    void TextApp::switchGame(int game_num) {
        if (game_num <= 0 || game_num > gameUIs.size())
            throw InvalidActionException("Invalid game number");

        active_game = game_num;

        cout << "Switched to game number " << active_game << "\n";
    }

    void TextApp::printGames() {
        if (gameUIs.size() == 0) {
            cout << "No games are currently played\n";
            return;
        }

        cout << "Games number ";

        for (int i = 1; i <= gameUIs.size(); i++)
            cout << i << ", ";

        cout << "are currently played\n";
    }
}

