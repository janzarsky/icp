#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <GUICard.hpp>

using namespace std;

namespace solitaire
{
    GUICard::GUICard(unsigned int pileIndex, unsigned int cardIndex) {
        this->pileIndex = pileIndex;
        this->cardIndex = cardIndex;

        setFlat(true);
        setAutoFillBackground(true);
        setContentsMargins(10, 10, 10, 10);
    }

    GUICard::GUICard(unsigned int pileIndex): GUICard(pileIndex, 0) {}

    GUICard::GUICard(): GUICard(0) {}

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

    unsigned int GUICard::getPileIndex() {
        return pileIndex;
    }

    unsigned int GUICard::getCardIndex() {
        return cardIndex;
    }
}
