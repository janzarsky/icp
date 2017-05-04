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
        repaint();
        repaint();
    }

    void GUIGame::initLayout() {
        QPalette pal;
        pal.setColor(QPalette::Background, QColor::fromRgb(127,255,127));
        setAutoFillBackground(true);
        setPalette(pal);

        QPalette pal2;
        pal2.setColor(QPalette::Background, QColor::fromRgb(32,255,32));

        layout = new QGridLayout();

        QLabel *back = new QLabel("XX");
        back->setAutoFillBackground(true);
        back->setPalette(pal2);

        deck = new GUICard();
        deck->setAutoFillBackground(true);
        deck->setPalette(pal2);

        layout->addWidget(back, 0, 0);
        layout->addWidget(deck, 0, 1);

        for (unsigned int i = 0; i < NUM_OF_HOMES; i++) {
            homes[i] = new GUICard();
            homes[i]->setAutoFillBackground(true);
            homes[i]->setPalette(pal2);
            layout->addWidget(homes[i], 0, 3 + i);
        }

        for (unsigned int i = 0; i < NUM_OF_COLUMNS; i++) {
            pile_layouts[i] = new QVBoxLayout();

            piles[i] = new QWidget();
            piles[i]->setAutoFillBackground(true);
            piles[i]->setPalette(pal2);
            piles[i]->setLayout(pile_layouts[i]);

            layout->addWidget(piles[i], 1, i);
        }

        setLayout(layout);
    }

    void GUIGame::repaint() {
        QPalette pal;
        pal.setColor(QPalette::Background, QColor::fromRgb(0,195,0));

        card deck_fronts = game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back();

        if (game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().size() > 0)
            deck->setCardValue(game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back());
        else
            deck->setText("[]");

        for (int i = 0; i < NUM_OF_HOMES; i++)
            if (game.piles[NUM_OF_COLUMNS + i].GetPile().size() > 0)
                homes[i]->setCardValue(game.piles[NUM_OF_COLUMNS + i].GetPile().back());
            else
                homes[i]->setText("[]");

        for (int i = 0; i < NUM_OF_COLUMNS; i++) {
            QLayoutItem *child;
            while ((child = pile_layouts[i]->takeAt(0)) != 0) {
                delete child;
            }

            unsigned int pile_size = game.piles[i].GetPile().size();
            
            for (unsigned int j = 0; j < pile_size; j++) {
                GUICard *l = new GUICard();

                if (j >= pile_size - game.piles[i].shownCards)
                    l->setCardValue(game.piles[i].GetPile()[j]);
                else
                    l->setCardBack();

                l->setAutoFillBackground(true);
                l->setPalette(pal);
                pile_layouts[i]->addWidget(l);
            }
            
            QWidget *w = new QWidget();
            w->setAutoFillBackground(true);
            w->setPalette(pal);
            pile_layouts[i]->addWidget(w, 1);
        }
    }

}
