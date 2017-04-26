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
        TextUIParser parser;

        void newGame();
        void listenToCommands();
        void executeCommand(UICommand);

    public:
        App();
    };
}
