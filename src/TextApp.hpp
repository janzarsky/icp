#include <vector>
#include "GameUI.hpp"
#include "TextUIParser.hpp"

using namespace std;

namespace solitaire
{
    class TextApp
    {
        const int max_num_of_games = 4;
        vector<GameUI> gameUIs;
        int active_game = 0;
        TextUIParser parser;

        void listenToCommands();
        void executeCommand(UICommand);
        
        void printHelp();
        void newGame();
        void closeGame();
        void switchGame(int);
        void printGames();
        void printActiveBoard();

    public:
        TextApp();
    };
}
