/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#include <QApplication>
#include "othello.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    (new Othello())->show();

    return app.exec();
}
