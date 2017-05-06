#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>
#include <QString>
#include "GUICard.hpp"
#include "Game.hpp"
#include "Command.hpp"

using namespace std;

namespace solitaire
{
    class GUIGame: public QWidget
    {
        enum cmdStatusType { cmdNew, cmdFrom } cmdStatus = cmdNew;

        Q_OBJECT

        GAME game;
        Command cmd;
        QGridLayout *layout;
        GUICard *deck;
        GUICard *homes[NUM_OF_HOMES];
        QWidget *piles[NUM_OF_COLUMNS];
        QBoxLayout *pile_layouts[NUM_OF_COLUMNS];

        void initLayout();
        void repaint();

    private slots:
        void turnCard();

    public:
        GUIGame();
    };
}
