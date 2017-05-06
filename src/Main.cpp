#include "Game.hpp"
#ifdef TUI
#include "TextApp.hpp"
#else
#include "GUIApp.hpp"
#endif

using namespace std;
using namespace solitaire;

int main(int argc, char *argv[])
{
#ifdef TUI
    TextApp app(argc, argv);
#else
    GUIApp app(argc, argv);
#endif

	return 0;
}
