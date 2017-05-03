#include <vector>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include "GUIGame.hpp"

using namespace std;

namespace solitaire
{
    class GUIApp
    {
		const unsigned int max_num_of_games = 4;

        QApplication app;
		QMainWindow mainWindow;
		QGridLayout gamesGrid;
		vector<GUIGame *> gameUIs;

		void initLayout();
		void addGame();

    public:
        GUIApp(int argc, char *argv[]);
    };
}
