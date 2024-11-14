/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#ifndef DIALOG_GAME_STATUS_H
#define DIALOG_GAME_STATUS_H

#include <QtWidgets>
#include "../core/game.h"

namespace Dialog
{
    class GameStatus : public QDialog
    {
        public:
            GameStatus(Core::Game *game, QWidget *parent);
            void update();

        private:
            void addWidgets();
            void setDialog();

        private:
            const int WIDTH = 350;
            const int HEIGHT = 125;
            const QString TITLE = "Game Status";

            Core::Game *game;
            QLabel *playing = new QLabel;
            QLabel *player1Score = new QLabel;
            QLabel *player1Disks = new QLabel;
            QLabel *player2Score = new QLabel;
            QLabel *player2Disks = new QLabel;
            QVBoxLayout *mainLayout = new QVBoxLayout;
    };
}

#endif // DIALOG_GAME_STATUS_H
