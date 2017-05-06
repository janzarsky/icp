#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <Card.hpp>

using namespace std;

namespace solitaire
{
    class GUICard: public QLabel
    {
        QPalette frontPal;
        QPalette backPal;
        QPalette emptyPal;

    public:
        GUICard();
        void setCardValue(card& card);
        void setCardEmpty();
        void setCardBack();
    };
}
