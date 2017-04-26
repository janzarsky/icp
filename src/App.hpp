#include <vector>
#include "GameUI.hpp"
#include "TextUIParser.hpp"

using namespace std;

namespace solitaire
{
    class App
    {
        const int max_num_of_games = 4;
        vector<GameUI> gameUIs;
        int active_game;
        TextUIParser parser;

        void listenToCommands();
        void executeCommand(UICommand);
        void newGame();
        void closeGame();
        void switchGame(int);
        void printGames();

    public:
        App();
    };
}
