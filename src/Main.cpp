#include "Game.hpp"
#include "TextApp.hpp"
#include "GUIApp.hpp"

using namespace std;
using namespace solitaire;

int main(int argc, char **argv)
{
#ifdef GUI
    GUIApp app;
#else
    TextApp app;
#endif

	return 0;
}
