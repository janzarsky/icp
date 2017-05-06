#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <Card.hpp>

using namespace std;

namespace solitaire
{
    class GUICard: public QPushButton
    {
        Q_OBJECT

        unsigned int pileIndex;
        unsigned int cardIndex;

    public:
        GUICard();
        GUICard(unsigned int pileIndex);
        GUICard(unsigned int pileIndex, unsigned int cardIndex);

        void setCardValue(card& card);
        void setCardEmpty();
        void setCardBack();
        unsigned int getPileIndex();
        unsigned int getCardIndex();
    };
}
