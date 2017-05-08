/**
 * @file    Main.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Main function - creates either GUI or TUI app
 */

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
    TUIApp app;
#else
    GUIApp app(argc, argv);
#endif

	return 0;
}
