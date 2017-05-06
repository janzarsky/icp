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
    public:
        GUICard();
        void setCardValue(card& card);
        void setCardEmpty();
        void setCardBack();
    };
}
