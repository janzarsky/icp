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
        initLayout();
        reloadValues();
    }

    GUIGame::GUIGame(string filename): game{filename} {
        initLayout();
        reloadValues();
    }

    void GUIGame::initLayout() {
        QPalette pal;
        pal.setColor(QPalette::Background, QColor::fromRgb(64,64,64));
        setAutoFillBackground(true);
        setPalette(pal);
        setMinimumSize(0, 0);

        layout = new QGridLayout();

        GUICard *back = new GUICard();
        back->setCardBack();
        connect(back, SIGNAL(clicked()), this, SLOT(turnCard()));

        deck = new GUICard();
        connect(deck, SIGNAL(clicked()), this, SLOT(moveFromDeck()));

        layout->addWidget(back, 0, 0);
        layout->addWidget(deck, 0, 1);

        for (unsigned int i = 0; i < NUM_OF_HOMES; i++) {
            homes[i] = new GUICard(i);
            connect(homes[i], &GUICard::clicked, this, &GUIGame::moveToHome);

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
        //layout->setSpacing((width() - NUM_OF_COLUMNS*getCardSize().width())/6);
        //cout << width() << endl;
        update();
    }

    void GUIGame::reloadValues() {
        deck->setMark(false);

        if (game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES]->GetPile().size() > 0)
            deck->setCardValue(game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES]->GetPile().back());
        else
            deck->setCardEmpty();

        for (int i = 0; i < NUM_OF_HOMES; i++)
            if (game.piles[NUM_OF_COLUMNS + i]->GetPile().size() > 0)
                homes[i]->setCardValue(game.piles[NUM_OF_COLUMNS + i]->GetPile().back());
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

            unsigned int pile_size = game.piles[i]->GetPile().size();

            if (pile_size == 0) {
                GUICard *card = new GUICard(i);
                card->setCardEmpty();
                connect(card, &GUICard::clicked, this, &GUIGame::movePile);

                pile_layouts[i]->addWidget(card);
            }
            
            for (unsigned int j = 0; j < pile_size; j++) {
                GUICard *card = new GUICard(i, j);

                if (j >= pile_size - game.piles[i]->shownCards) {
                    card->setCardValue(game.piles[i]->GetPile()[j]);
                }
                else {
                    card->setCardBack();
                }

                if (j < pile_size - 1)
                    card->setHidden(true);

                if (j > 0) {
                    card->setBehind(true);

                    if (j <= pile_size - game.piles[i]->shownCards)
                        card->setBackBehind(true);
                }

                connect(card, &GUICard::clicked, this, &GUIGame::movePile);

                pile_layouts[i]->addWidget(card);
            }

            pile_layouts[i]->addStretch(0);
        }

        repaint();
    }

    void GUIGame::turnCard() {
        if (cmdStatus == cmdNew) {
            cmd.type = CommandType::turn;
            cmd.count = 1;
            cmd.from = 0;
            cmd.to = 0;

            sendCommand();

            cmdStatus = cmdNew;
        }
        else {
            cmdStatus = cmdNew;
        }
    }

    void GUIGame::moveFromDeck() {
        if (cmdStatus == cmdNew) {
            cmd.type = CommandType::move;
            cmd.from = NUM_OF_HOMES + NUM_OF_COLUMNS;
            cmd.count = 1;

            GUICard *card = qobject_cast<GUICard *>(sender());
            card->setMark(true);

            cmdStatus = cmdFrom;
        }
        else {
            reloadValues();
            cmdStatus = cmdNew;
        }
    }

    void GUIGame::moveToHome() {
        if (cmdStatus == cmdFrom) {
            if (cmd.count == 1) {
                GUICard *card = qobject_cast<GUICard *>(sender());

                cmd.to = NUM_OF_COLUMNS + card->getPileIndex();

                sendCommand();
            }
        }

        reloadValues();
        cmdStatus = cmdNew;
    }

    void GUIGame::movePile() {
        if (cmdStatus == cmdNew) {
            cmd.type = CommandType::move;

            GUICard *card = qobject_cast<GUICard *>(sender());

            cmd.from = card->getPileIndex();

            cmd.count = pile_layouts[cmd.from]->count() - card->getCardIndex() - 1;

            if (cmd.count > game.piles[cmd.from]->shownCards) {
                reloadValues();
                cmdStatus = cmdNew;
            }
            else {
                cmdStatus = cmdFrom;
                card->setMark(true);
            }
        }
        else {
            GUICard *card = qobject_cast<GUICard *>(sender());

            cmd.to = card->getPileIndex();

            sendCommand();

            reloadValues();
            cmdStatus = cmdNew;
        }
    }

    void GUIGame::sendCommand() {
        cout << "send command, type: ";

        if (cmd.type == CommandType::move)
            cout << "move, ";
        else if (cmd.type == CommandType::turn)
            cout << "turn, ";
        else
            cout << "unknown, ";

        cout << "from: " << cmd.from << ", to: " << cmd.to << ", count: " << cmd.count << endl;

        // fix
        cmd.from++;
        cmd.to++;

        game.Play(cmd);
        reloadValues();
    }

    void GUIGame::resizeEvent(QResizeEvent *event) {
        repaint();
    }

    void GUIGame::saveGame(string filename) {
        try {
            game.Save(filename);
        }
        catch (invalid_argument& e) {
            // TODO
            return;
        }
    }

    void GUIGame::undoGame() {
        game.Backward();
        reloadValues();
    }
}
