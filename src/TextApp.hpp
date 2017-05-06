#include <vector>
#include <memory>
#include "GameUI.hpp"
#include "TextUIParser.hpp"

using namespace std;

namespace solitaire
{
    class TextApp
    {
        const unsigned int max_num_of_games = 4;
        vector<unique_ptr<GameUI>> gameUIs;
        unsigned int active_game = 0;
        TextUIParser parser;

        void listenToCommands();
        void executeCommand(UICommand);
        
        void printHelp();
        void newGame();
        void closeGame();
        void switchGame(unsigned int);
        void printGames();
        void printActiveBoard();

    public:
        TextApp(int argc, char *argv[]);
    };
}
