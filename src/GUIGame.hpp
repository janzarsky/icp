#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QString>
#include "GUICard.hpp"
#include "Game.hpp"

using namespace std;

namespace solitaire
{
    class GUIGame: public QWidget
    {
        GAME game;
        QGridLayout *layout;
        GUICard *deck;
        GUICard *homes[NUM_OF_HOMES];
        QWidget *piles[NUM_OF_COLUMNS];
        QBoxLayout *pile_layouts[NUM_OF_COLUMNS];

        void initLayout();
        void repaint();

    public:
        GUIGame();
    };
}
