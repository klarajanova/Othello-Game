/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#ifndef OTHELLO_H
#define OTHELLO_H

#include <QtWidgets>

/**
 *  @brief xxx
 */

class Othello : public QMainWindow
{
    public:
        Othello();

    private:
        void setWindow();
        void newGame();
        void loadGame();

    private:
        const int WIDTH = 500;
        const int HEIGHT = 375;
        const QString TITLE = "Othello";
        const QString IMAGE_SPLAH = "assets/images/splash.png";
};

#endif // OTHELLO_H
