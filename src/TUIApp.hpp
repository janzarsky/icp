#include <vector>
#include <memory>
#include <string>
#include "TUIGame.hpp"
#include "TUIParser.hpp"

using namespace std;

namespace solitaire
{
    class TUIApp
    {
        const unsigned int max_num_of_games = 4;
        vector<unique_ptr<TUIGame>> gameUIs;
        unsigned int active_game = 0;
        TUIParser parser;

        void listenToCommands();
        void executeCommand(UICommand);
        
        void printHelp();
        void newGame();
        void closeGame();
        void switchGame(unsigned int);
        void saveGame(string filename);
        void loadGame(string filename);
        void printGames();
        void printActiveBoard();

    public:
        TUIApp();
    };
}
