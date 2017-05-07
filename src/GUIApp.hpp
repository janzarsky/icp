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
		QAction *undoGameAct;
		QAction *newGameAct;
        QAction *closeGameAct;
		QAction *loadGameAct;
		QAction *saveGameAct;

        QWidget *placeholder1;
        QWidget *placeholder2;

        void newGame(string filename);

    private slots:
        void undoGame();
        void newGameMenu();
        void closeGame();
        void loadGame();
        void saveGame();

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
