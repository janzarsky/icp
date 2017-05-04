#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <Card.hpp>

using namespace std;

namespace solitaire
{
    class GUICard: public QLabel
    {
    public:
        GUICard();
        void setCardValue(card& card);
        void setCardEmpty();
        void setCardBack();
    };
}
