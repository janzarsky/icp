#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QPalette>
#include <QString>
#include "GUIGame.hpp"
#include "Game.hpp"

using namespace std;

namespace solitaire
{
    GUIGame::GUIGame() {
        cout << "(constructor GUIGame)\n";
        initLayout();
        repaint();
    }

    void GUIGame::initLayout() {
        QPalette pal;
        pal.setColor(QPalette::Background, QColor::fromRgb(127,255,127));
        setAutoFillBackground(true);
        setPalette(pal);

        QPalette pal2;
        pal2.setColor(QPalette::Background, QColor::fromRgb(32,255,32));

        layout = new QVBoxLayout();

        QLabel *back = new QLabel("Back deck");
        back->setAutoFillBackground(true);
        back->setPalette(pal2);

        deck = new QLabel("Front deck");
        deck->setAutoFillBackground(true);
        deck->setPalette(pal2);

        QHBoxLayout *topBox = new QHBoxLayout();
        topBox->addWidget(back);
        topBox->addWidget(deck);

        for (unsigned int i = 0; i < NUM_OF_HOMES; i++) {
            homes[i] = new QLabel("Home");
            homes[i]->setAutoFillBackground(true);
            homes[i]->setPalette(pal2);
            topBox->addWidget(homes[i]);
        }

        layout->addLayout(topBox);

        QHBoxLayout *bottomBox = new QHBoxLayout();

        for (unsigned int i = 0; i < NUM_OF_COLUMNS; i++) {
            piles[i] = new QLabel("Pile");
            piles[i]->setAutoFillBackground(true);
            piles[i]->setPalette(pal2);
            bottomBox->addWidget(piles[i]);
        }

        layout->addLayout(bottomBox);

        setLayout(layout);
    }

    void GUIGame::repaint() {
        card deck_fronts = game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back();

        if (game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().size() > 0)
            deck->setText(unicode(game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back()));
        else
            deck->setText("[]");

        for (int i = 0; i < NUM_OF_HOMES; i++)
            if (game.piles[NUM_OF_COLUMNS + i].GetPile().size() > 0)
                homes[i]->setText(unicode(game.piles[NUM_OF_COLUMNS + i].GetPile().back()));
            else
                homes[i]->setText("[]");

/*
        int max_height = 0;
        int sizes[NUM_OF_COLUMNS];
        
        for (int i = 0; i < NUM_OF_COLUMNS; i++) {
            sizes[i] = game.piles[i].GetPile().size();

            if (sizes[i] > max_height)
                max_height = sizes[i];
        }

        for (int i = 0; i < max_height; i++) {
            for (int j = 0; j < NUM_OF_COLUMNS; j++) {
                if (i < sizes[j])
                    cout << unicode(game.piles[j].GetPile()[i]) << " ";
                else
                    cout << unicode_space() << " ";
            }

            cout << "\n";
        }

        cout << "\n";
*/
    }

    QString GUIGame::unicode(card& card) {
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
        
        return res;
    }
}
