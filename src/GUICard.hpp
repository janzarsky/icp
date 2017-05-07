#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtSvg>
#include <Card.hpp>

using namespace std;

namespace solitaire
{
    class GUICard: public QPushButton
    {
        Q_OBJECT

        static QSvgRenderer renderer;

        int cardw = 120;
        int cardh = 180;
        int cardh2 = 53;

        unsigned int pileIndex;
        unsigned int cardIndex;
        bool hidden = false;
        bool behind = false;
        bool back = false;
        QString element;

    public:
        GUICard();
        GUICard(unsigned int pileIndex);
        GUICard(unsigned int pileIndex, unsigned int cardIndex);

        QSize sizeHint();
        void paintEvent(QPaintEvent *e);

        void setCardValue(card& card);
        void setCardEmpty();
        void setCardBack();
        void setHidden(bool hidden);
        void setBehind(bool behind);
        void setBackBehind(bool back);
        unsigned int getPileIndex();
        unsigned int getCardIndex();
        bool isHidden();
        bool isBehind();
        bool isBackBehind();
    };
}
