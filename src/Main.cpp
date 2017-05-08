#include "Game.hpp"
#ifdef TUI
#include "TUIApp.hpp"
#else
#include "GUIApp.hpp"
#endif

using namespace std;
using namespace solitaire;

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
#ifdef TUI
    TUIApp app();
#else
    GUIApp app(argc, argv);
#endif

	return 0;
}
