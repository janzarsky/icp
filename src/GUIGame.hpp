/**
 * @file    GUIGame.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Widget containing single game board
 */

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
        GUICard *back;
        GUICard *homes[NUM_OF_HOMES];
        QWidget *piles[NUM_OF_COLUMNS];
        QBoxLayout *pile_layouts[NUM_OF_COLUMNS];
        QPalette activePal;
        QPalette inactivePal;
        int cardSize = 120;
        bool msgShown = false;

        void initLayout();
        void reloadValues();
        void sendCommand();

    private slots:
        void turnCard();
        void moveFromDeck();
        void moveToHome();
        void movePile();

    signals:
        void activated();

    protected:
        void mousePressEvent(QMouseEvent *event) override;

    public:
        GUIGame(int cardSize);
        GUIGame(int cardSize, string filename);
        void resizeEvent(QResizeEvent *event);
        void saveGame(string filename);
        void undoGame();
        void hintGame();
        void setActive(bool active);
        void setCardSize(int width);
    };
}
