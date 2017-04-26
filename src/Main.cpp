#include <iostream>
#include "App.hpp"
#include "Exceptions.hpp"

using namespace std;
using namespace solitaire;

int main() {
    App app;

    try {
        cout << "app.NewGame()\n";
        app.NewGame();

        cout << "app.NewGame()\n";
        app.NewGame();

        cout << "app.NewGame()\n";
        app.NewGame();

        cout << "app.NewGame()\n";
        app.NewGame();

        cout << "app.NewGame()\n";
        app.NewGame();
    }
    catch (InvalidActionException& e) {
        cerr << "INVALID ACTION: " << e.message() << "\n";
    }
}
