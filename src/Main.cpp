#include "Game.hpp"
#include "App.hpp"

using namespace std;
using namespace solitaire;

int main(int argc, char **argv)
{
	GAME game;
	for (auto c : game.piles) {
		PrintCards(c->GetPile());
		cout << string(40, '=')<<endl;
	}
	while (1) {
		cout << string(40, '+') << endl;
		game.ShowTable();
		cout << string(40, '+') << endl;
		game.Play();
	}

    /*App app;
	return 0;*/
}
