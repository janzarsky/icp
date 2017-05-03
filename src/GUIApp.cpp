#include <iostream>
#include "GUIApp.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    GUIApp::GUIApp() {
        cout << "(constructor GUIApp)\n";
    }

    void GUIApp::executeCommand(UICommand cmd) {
        switch (cmd.type) {
            default:
                cout << "got command: " << cmd.type << "\n";
                break;
        }
    }
}

