/**
 * @file    GUICard.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Widget representing a card
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtSvg>
#include <QString>
#include <Card.hpp>

using namespace std;

namespace solitaire
{
    class GUICard: public QPushButton
    {
        Q_OBJECT

        static QSvgRenderer renderer;

        int cardw;
        int cardh;
        int cardh2;

        unsigned int pileIndex;
        unsigned int cardIndex;
        bool hidden = false;
        bool behind = false;
        bool back = false;
        bool mark = false;
        QString element;

    public:
        GUICard(int cardSize, unsigned int pileIndex, unsigned int cardIndex);

        void paintEvent(QPaintEvent *e);

        void setCardValue(card& card);
        void setCardEmpty();
        void setCardBack();
        void setHidden(bool hidden);
        void setBehind(bool behind);
        void setBackBehind(bool back);
        void setMark(bool mark);
        void setSize(int width);
        unsigned int getPileIndex();
        unsigned int getCardIndex();
        bool isHidden();
        bool isBehind();
        bool isBackBehind();
        bool isMarked();
    };
}
