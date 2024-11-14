/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#ifndef GUI_GAME_H
#define GUI_GAME_H

#include <QtWidgets>
#include "../core/game.h"
#include "../dialog/game_status.h"
#include "../dialog/history.h"

namespace Dialog
{
    class History;
}

namespace GUI
{
    class Game : public QWidget
    {
        public:
            Game(int boardSize, QString opponent, Core::AI::Difficulty difficulty = Core::AI::NONE);

            Core::Game *getCoreGame() { return game; }
            void refreshGUI();
            void gameEnd();

        private:
            void showMoves();
            void setGUI(int boardSize, QString opponent, Core::AI::Difficulty difficulty = Core::AI::NONE);
            void mousePressEvent(QMouseEvent* event);
            void keyPressEvent(QKeyEvent *event);
            void keyReleaseEvent(QKeyEvent *event);
            void closeEvent(QCloseEvent *event);

        private:
            const int WIDTH = 500;
            const int HEIGHT = 500;
            const QString TITLE = "Othello - Game";

            const QPixmap PIXMAP_BLACKDISK =
                QPixmap("assets/images/black_disk.png");
            const QPixmap PIXMAP_WHITEDISK =
                QPixmap("assets/images/white_disk.png");

            Core::Game *game;
            Dialog::GameStatus *gameStatus;
            Dialog::History *history;
            QVBoxLayout *mainLayout = new QVBoxLayout;
    };
}

#endif // GUI_GAME_H
