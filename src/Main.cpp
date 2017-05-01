#include "Game.hpp"

using namespace std;

//main for CONSOLE version of game
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
	return 0;
}
