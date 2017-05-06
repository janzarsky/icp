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
    class GUIMainWindow: public QMainWindow
    {
        Q_OBJECT

		const unsigned int max_num_of_games = 4;

		QGridLayout gamesGrid;
        vector<GUIGame *> gameUIs;

        QMenu *gameMenu;
		QAction *newGameAct;
        QAction *closeGameAct;

    private slots:
        void newGame();
        void closeGame();

    public:
        GUIMainWindow();
    };

    class GUIApp: public QApplication
    {
        GUIMainWindow *mainWindow;

    public:
        GUIApp(int argc, char *argv[]);
    };
}
