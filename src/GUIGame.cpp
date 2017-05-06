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
        pal.setColor(QPalette::Background, QColor::fromRgb(64,64,64));
        setAutoFillBackground(true);
        setPalette(pal);

        layout = new QGridLayout();

        GUICard *back = new GUICard();
        back->setCardBack();

        deck = new GUICard();

        layout->addWidget(back, 0, 0);
        layout->addWidget(deck, 0, 1);

        for (unsigned int i = 0; i < NUM_OF_HOMES; i++) {
            homes[i] = new GUICard();
            layout->addWidget(homes[i], 0, 3 + i);
        }

        for (unsigned int i = 0; i < NUM_OF_COLUMNS; i++) {
            pile_layouts[i] = new QVBoxLayout();
            pile_layouts[i]->setContentsMargins(0, 0, 0, 0);
            pile_layouts[i]->setSpacing(0);

            piles[i] = new QWidget();
            piles[i]->setLayout(pile_layouts[i]);

            layout->addWidget(piles[i], 1, i);
        }

        setLayout(layout);
    }

    void GUIGame::repaint() {
        card deck_fronts = game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back();

        if (game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().size() > 0)
            deck->setCardValue(game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES].GetPile().back());
        else
            deck->setText("[]");

        for (int i = 0; i < NUM_OF_HOMES; i++)
            if (game.piles[NUM_OF_COLUMNS + i].GetPile().size() > 0)
                homes[i]->setCardValue(game.piles[NUM_OF_COLUMNS + i].GetPile().back());
            else
                homes[i]->setCardEmpty();

        for (int i = 0; i < NUM_OF_COLUMNS; i++) {
            QLayoutItem *child;
            while ((child = pile_layouts[i]->takeAt(0)) != 0) {
                if (child->layout() != 0)
                    delete child->layout();
                else if (child->widget() != 0)
                    delete child->widget();

                delete child;
            }

            unsigned int pile_size = game.piles[i].GetPile().size();
            
            for (unsigned int j = 0; j < pile_size; j++) {
                GUICard *l = new GUICard();

                if (j >= pile_size - game.piles[i].shownCards)
                    l->setCardValue(game.piles[i].GetPile()[j]);
                else
                    l->setCardBack();

                l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

                pile_layouts[i]->addWidget(l);
            }

            pile_layouts[i]->addStretch(0);
        }
    }

}
