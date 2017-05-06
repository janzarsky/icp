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

        unsigned int index;

    public:
        GUICard();
        GUICard(unsigned int index);
        void setCardValue(card& card);
        void setCardEmpty();
        void setCardBack();
        unsigned int getIndex();
    };
}
