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

        const int cardw = 120;
        const int cardh = 180;
        const int cardh2 = 53;

        unsigned int pileIndex;
        unsigned int cardIndex;
        bool hidden = false;
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
        unsigned int getPileIndex();
        unsigned int getCardIndex();
        bool isHidden();
    };
}
