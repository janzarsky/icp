#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QString>
#include "Game.hpp"

using namespace std;

namespace solitaire
{
    class GUIGame: public QWidget
    {
        GAME game;
        QGridLayout *layout;
        QLabel *deck;
        QLabel *homes[NUM_OF_HOMES];
        QLabel *piles[NUM_OF_COLUMNS];

        void initLayout();
        void repaint();
        QString unicode(card& card);

    public:
        GUIGame();
    };
}
