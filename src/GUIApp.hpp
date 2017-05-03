#include <vector>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "TextUIParser.hpp"

using namespace std;

namespace solitaire
{
    class GUIApp
    {
        void executeCommand(UICommand);

    public:
        GUIApp(int argc, char *argv[]);
    };
}
