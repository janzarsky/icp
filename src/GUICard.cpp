#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <GUICard.hpp>

using namespace std;

namespace solitaire
{
    GUICard::GUICard() {
        QPalette pal;
        pal.setColor(QPalette::Background, QColor::fromRgb(0,195,0));

        setAutoFillBackground(true);
        setPalette(pal);
    }

    void GUICard::setCardValue(card& card) {
        QString res;

		switch (card.getValue()) {
            case 11:
                res = "J";
                break;
            case 12:
                res = "Q";
                break;
            case 13:
                res = "K";
                break;
            case 1:
                res = "A";
                break;
            default:
                res = (card.getValue() + '0' - 1);
                break;
		}

		switch (card.getSuit()) {
            case CLUBS:
                res += "\u2663";
                break;
            case DIAMONDS:
                res += "\u2666";
                break;
            case HEARTS:
                res += "\u2665";
                break;
            case SPADES:
                res += "\u2660";
                break;
            default:
                res += "UNKNOWN";
                break;
		}
        
        setText(res);
    }

    void GUICard::setCardEmpty() {
        setText("[]");
    }

    void GUICard::setCardBack() {
        setText("XX");
    }
}
