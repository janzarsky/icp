/**
 * @file    GUICard.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Widget representing a card
 */

#include <iostream>
#include "GUICard.hpp"

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

    /**
     * Create card widget
     *
     * @param cardSize card width in pixels
     * @param pileIndex pile index
     * @param cardIndex position of card within the pile
     */
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

    /**
     * Set SVG element ID using game card
     *
     * @param card game card
     */
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

    /**
     * Set SVG element ID to empty card
     */
    void GUICard::setCardEmpty() {
        element = "empty";
    }

    /**
     * Set SVG element ID to back of the card
     */
    void GUICard::setCardBack() {
        element = "back";
    }

    /**
     * Paint card image on the button
     * 
     * Method uses common SVG renderer and computes image position using
     * provided card size and available space.
     */
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
 
    /*
     * Set card as hidden behind other cards (in the middle of pile) so that
     * only top is visible
     */
    void GUICard::setHidden(bool hidden) {
        if (hidden)
            setMinimumSize(cardw, cardh2);
        else
            setMinimumSize(cardw, cardh);

        this->hidden = hidden;
    }

    /*
     * Set that there is a card behind this card (used for corner rendering)
     */
    void GUICard::setBehind(bool behind) {
        this->behind = behind;
    }

    /*
     * Set that the card behind is not yet turn (back pattern is visible)
     */
    void GUICard::setBackBehind(bool back) {
        this->back = back;
    }

    /*
     * Set that there should be a frame renderer around the card
     * (e.g. when selected)
     */
    void GUICard::setMark(bool mark) {
        this->mark = mark;
    }
    
    /*
     * Set card with and compute other dimensions
     *
     * @param width width in pixels
     */
    void GUICard::setSize(int width) {
        cardw = width;
        cardh = width*3/2;
        cardh2 = width*4/9;

        setHidden(hidden);
    }

    /**
     * Get card pile index
     */
    unsigned int GUICard::getPileIndex() {
        return pileIndex;
    }

    /**
     * Get card position in pile
     */
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
