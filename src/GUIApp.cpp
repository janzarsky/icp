#include <iostream>
#include "GUIApp.hpp"
#include "Exceptions.hpp"

using namespace std;

namespace solitaire
{
    GUIApp::GUIApp(int argc, char *argv[]) {
        cout << "(constructor GUIApp)\n";

        QApplication app(argc, argv);

        QLabel l("asdf");
        l.setWindowTitle("asdfsafd");
        l.resize(400, 400);
        l.show();
    }

    void GUIApp::executeCommand(UICommand cmd) {
        switch (cmd.type) {
            default:
                cout << "got command: " << cmd.type << "\n";
                break;
        }
    }
}

