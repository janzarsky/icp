/**
 * @file    GUIApp.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Main window containing games and menu bar
 */

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

		static const unsigned int max_num_of_games = 4;
		static const unsigned int game_cols = 2;

        static const int smallCardSize = 80;
        static const int largeCardSize = 120;

		QGridLayout gamesGrid;
        vector<GUIGame *> gameUIs;
        unsigned int gameSlots[max_num_of_games] = { 0 };

        unsigned int active_game = 0;

        QMenu *gameMenu;
		QAction *undoGameAct;
		QAction *newGameAct;
        QAction *closeGameAct;
		QAction *loadGameAct;
		QAction *saveGameAct;
		QAction *quitAct;

        void newGame(string filename);
        void setActiveGame();

    private slots:
        void undoGame();
        void newGameMenu();
        void closeGame();
        void loadGame();
        void saveGame();
        void activeGame();
        void quit();

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
