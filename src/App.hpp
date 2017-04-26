#include <vector>
#include "GameUI.hpp"

using namespace std;

namespace solitaire
{
    class App
    {
        const int max_num_of_games = 4;
        vector<GameUI> gameUIs;

    public:
        App();
        void NewGame();
    };
}
