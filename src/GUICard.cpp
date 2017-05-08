/**
 * @file    GUICard.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Widget representing a card
 */

#include <iostream>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <GUICard.hpp>

/**
 * @file    cards.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Generated resource: SVG image with cards
 *
 * Docs is written in GUICard.cpp because the file is generated.
 */

#include "cards.hpp"

using namespace std;

namespace solitaire
{
    QSvgRenderer GUICard::renderer;

    GUICard::GUICard(int cardSize, unsigned int pileIndex, unsigned int cardIndex) {
        this->pileIndex = pileIndex;
        this->cardIndex = cardIndex;

        setContentsMargins(10, 10, 10, 10);
        setSize(cardSize);
        setHidden(false);
        setCardBack();

        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        if (!renderer.isValid()) {
            renderer.load(QString(":/cards.svgz"));

            if (!renderer.isValid()) {
                cerr << "Could not load SVG image" << endl;
            }
        }
    }

    void GUICard::setCardValue(card& card) {
		switch (card.getSuit()) {
            case CLUBS:
                element = "C";
                break;
            case DIAMONDS:
                element = "D";
                break;
            case HEARTS:
                element = "H";
                break;
            case SPADES:
                element = "S";
                break;
		}

		switch (card.getValue()) {
            case 10:
                element += "10";
                break;
            case 11:
                element += "J";
                break;
            case 12:
                element += "Q";
                break;
            case 13:
                element += "K";
                break;
            case 1:
                element += "A";
                break;
            default:
                element += (card.getValue() + '0');
                break;
		}
    }

    void GUICard::setCardEmpty() {
        element = "empty";
    }

    void GUICard::setCardBack() {
        element = "back";
    }

    void GUICard::paintEvent(QPaintEvent *e) {
        int w = width();
        int h = height();

        QSize size;

        if (isHidden()) {
            size.setWidth(w);
            size.setHeight(w*cardh2/cardw);
        }
        else {
            size.setWidth(w);
            size.setHeight(w*cardh/cardw);
        }

        if (size.height() > h) {
            if (isHidden()) {
                size.setHeight(h*cardh/cardh2);
                size.setWidth(h*cardw/cardh2);
            }
            else {
                size.setHeight(h);
                size.setWidth(h*cardw/cardh);
            }
        }
        else {
            if (isHidden())
                size.setHeight(w*cardh/cardw);
        }

        QPainter painter(this);

        int offset = (w - size.width())/2;

        if (!renderer.elementExists(element)) {
            cerr << "SVG element not found" << endl;
            return;
        }
 
        if (isBehind()) {
            QString helper;

            if (isBackBehind())
                helper = "helper2";
            else
                helper = "helper";

            if (!renderer.elementExists(element)) {
                cerr << "SVG element not found" << endl;
                return;
            }

            renderer.render(&painter, helper, QRectF(offset, 0, size.width(), size.height()));
        }

        renderer.render(&painter, element, QRectF(offset, 0, size.width(), size.height()));

        if (isMarked()) {
            if (!renderer.elementExists("mark")) {
                cerr << "SVG element not found" << endl;
                return;
            }

            renderer.render(&painter, QString("mark"), QRectF(offset, 0, size.width(), size.height()));
        }

        QWidget::paintEvent(e);
    }

    void GUICard::setHidden(bool hidden) {
        if (hidden)
            setMinimumSize(cardw, cardh2);
        else
            setMinimumSize(cardw, cardh);

        this->hidden = hidden;
    }

    void GUICard::setBehind(bool behind) {
        this->behind = behind;
    }

    void GUICard::setBackBehind(bool back) {
        this->back = back;
    }

    void GUICard::setMark(bool mark) {
        this->mark = mark;
    }
    
    void GUICard::setSize(int width) {
        cardw = width;
        cardh = width*3/2;
        cardh2 = width*4/9;

        setHidden(hidden);
    }

    unsigned int GUICard::getPileIndex() {
        return pileIndex;
    }

    unsigned int GUICard::getCardIndex() {
        return cardIndex;
    }

    bool GUICard::isHidden() {
        return hidden;
    }

    bool GUICard::isBehind() {
        return behind;
    }

    bool GUICard::isBackBehind() {
        return back;
    }

    bool GUICard::isMarked() {
        return mark;
    }
}
