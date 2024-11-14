/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#ifndef DIALOG_NEW_GAME_H
#define DIALOG_NEW_GAME_H

#include <QtWidgets>
#include "../core/ai.h"

namespace Dialog
{
    class NewGame : public QDialog
    {
        public:
            NewGame();

        private:
            void addWidgets();
            void setDialog();
            void startGame();

        private:
            const QString TITLE = "New Game";

            int boardSize = 8;
            QString opponent = "Human";
            Core::AI::Difficulty difficulty = Core::AI::EASY;
            QVBoxLayout *mainLayout = new QVBoxLayout;
    };
}

#endif // DIALOG_NEW_GAME_H
