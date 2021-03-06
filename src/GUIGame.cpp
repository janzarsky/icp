/**
 * @file    GUIGame.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Widget containing single game board
 */

#include <iostream>
#include "GUIGame.hpp"

using namespace std;

namespace solitaire
{
    /**
     * Create GUI game widget
     *
     * @param cardSize width of game cards
     */
    GUIGame::GUIGame(int cardSize) {
        this->cardSize = cardSize;
        initLayout();
        reloadValues();
    }

    /**
     * Create GUI game widget
     *
     * @param cardSize width of game cards
     * @param filename load game from file
     */
    GUIGame::GUIGame(int cardSize, string filename): game{filename} {
        this->cardSize = cardSize;
        initLayout();
        reloadValues();
    }

    /**
     * Create widgets
     */
    void GUIGame::initLayout() {
        activePal.setColor(QPalette::Background, QColor::fromRgb(137,141,141));
        inactivePal.setColor(QPalette::Background, QColor::fromRgb(112,115,115));

        setAutoFillBackground(true);
        setPalette(activePal);
        setMinimumSize(0, 0);

        layout = new QGridLayout();

        back = new GUICard(cardSize, 0, 0);
        back->setCardBack();
        connect(back, SIGNAL(clicked()), this, SLOT(turnCard()));

        deck = new GUICard(cardSize, 0, 0);
        connect(deck, SIGNAL(clicked()), this, SLOT(moveFromDeck()));

        layout->addWidget(back, 0, 0);
        layout->addWidget(deck, 0, 1);

        for (unsigned int i = 0; i < NUM_OF_HOMES; i++) {
            homes[i] = new GUICard(cardSize, i, 0);
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

    /**
     * Update cards so that the match the game state
     */
    void GUIGame::reloadValues() {
        back->setMark(false);
        back->setSize(cardSize);

        deck->setMark(false);
        deck->setSize(cardSize);

        if (game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES]->GetPile().size() > 0)
            deck->setCardValue(game.piles[NUM_OF_COLUMNS + NUM_OF_HOMES]->GetPile().back());
        else
            deck->setCardEmpty();

        for (int i = 0; i < NUM_OF_HOMES; i++) {
            homes[i]->setMark(false);
            homes[i]->setSize(cardSize);

            if (game.piles[NUM_OF_COLUMNS + i]->GetPile().size() > 0)
                homes[i]->setCardValue(game.piles[NUM_OF_COLUMNS + i]->GetPile().back());
            else
                homes[i]->setCardEmpty();
        }

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
                GUICard *card = new GUICard(cardSize, i, 0);
                card->setCardEmpty();
                card->setSize(cardSize);
                connect(card, &GUICard::clicked, this, &GUIGame::movePile);

                pile_layouts[i]->addWidget(card);
            }
            
            for (unsigned int j = 0; j < pile_size; j++) {
                GUICard *card = new GUICard(cardSize, i, j);
                card->setSize(cardSize);

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

        update();
    }

    /**
     * Turn card from deck
     */
    void GUIGame::turnCard() {
        setActive(true);
        activated();

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

    /**
     * Move card from deck
     */
    void GUIGame::moveFromDeck() {
        setActive(true);
        activated();

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

    /**
     * Move card to home
     */
    void GUIGame::moveToHome() {
        setActive(true);
        activated();

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

    /**
     * Move card from or to pile
     */
    void GUIGame::movePile() {
        setActive(true);
        activated();

        if (cmdStatus == cmdNew) {
            cmd.type = CommandType::move;

            GUICard *card = qobject_cast<GUICard *>(sender());

            cmd.from = card->getPileIndex();

            cmd.count = pile_layouts[cmd.from]->count() - card->getCardIndex() - 1;

            if ((unsigned int) cmd.count > game.piles[cmd.from]->shownCards) {
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

    /**
     * Send command to game
     *
     * When the game is finished, message is shown.
     */
    void GUIGame::sendCommand() {
        cmd.from++;
        cmd.to++;
        
        if (!game.End) {
            game.Play(cmd);
        }

        reloadValues();

        if (game.End && !msgShown) {
            msgShown = true;

            QMessageBox msg;
            msg.setText("Congratulations, game finished!");
            msg.exec();
        }
    }

    /**
     * Save game state to file
     *
     * In case of error, message is shown.
     */
    void GUIGame::saveGame(string filename) {
        try {
            game.Save(filename);
        }
        catch (invalid_argument& e) {
            QMessageBox msg;
            msg.setText("Could not save the game!");
            msg.exec();

            return;
        }
    }

    /**
     * Revert last command
     */
    void GUIGame::undoGame() {
        game.Backward();
        reloadValues();
    }

    /**
     * Show possible move
     *
     * Only source and destination pile is hinted, not the amount of cards.
     */
    void GUIGame::hintGame() {
        int from = 0;
        int to = 0;

        game.Help(from, to);

        if (from == 0 && to == 0)
            return;

        from--;
        to--;

        if (from < NUM_OF_COLUMNS) {
            for (int i = 0; i < pile_layouts[from]->count(); ++i) {
                QLayoutItem *item = pile_layouts[from]->itemAt(i);

                if (item->widget() != nullptr)
                    dynamic_cast<GUICard *>(item->widget())->setMark(true);
            }
        }
        else if (from == NUM_OF_COLUMNS + NUM_OF_HOMES) {
            deck->setMark(true);
        }

        if (to < NUM_OF_COLUMNS) {
            for (int i = 0; i < pile_layouts[to]->count(); ++i) {
                QLayoutItem *item = pile_layouts[to]->itemAt(i);

                if (item->widget() != nullptr)
                    dynamic_cast<GUICard *>(item->widget())->setMark(true);
            }
        }
        else if (to < NUM_OF_COLUMNS + NUM_OF_HOMES) {
            homes[to - NUM_OF_COLUMNS]->setMark(true);
        }
        else if (to == NUM_OF_COLUMNS + NUM_OF_HOMES) {
            back->setMark(true);
        }

        update();
    }

    /**
     * Visually set this game as active
     */
    void GUIGame::setActive(bool active) {
        if (active)
            setPalette(activePal);
        else
            setPalette(inactivePal);
    }

    /**
     * Set this game active on click
     */
    void GUIGame::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            setActive(true);
            activated();
        }
    }

    /**
     * Set card size
     *
     * @param width width of the card in pixels
     */
    void GUIGame::setCardSize(int width) {
        cardSize = width;

        reloadValues();
    }
}
