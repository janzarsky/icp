#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <GUICard.hpp>

using namespace std;

namespace solitaire
{
    GUICard::GUICard() {
        frontPal.setColor(QPalette::Background, QColor::fromRgb(255, 255, 255));
        backPal.setColor(QPalette::Background, QColor::fromRgb(191, 191, 191));
        emptyPal.setColor(QPalette::Background, QColor::fromRgb(95, 95, 95));

        setAutoFillBackground(true);
        setPalette(backPal);
        setContentsMargins(10, 10, 10, 10);
    }

    void GUICard::setCardValue(card& card) {
        setPalette(frontPal);

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
        setPalette(emptyPal);

        setText("[]");
    }

    void GUICard::setCardBack() {
        setPalette(backPal);

        setText("XX");
    }
}
