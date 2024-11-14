/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Soubor pro funkce umìlé inteligence
*/

#include "ai.h"
#include "game.h"

void Core::AI::play(Game *game, Difficulty difficulty)
{
    switch (difficulty)
    {
        case EASY:
            easy(game);
            break;
        case INTERMEDIATE:
            intermediate(game);
            break;
        default:
            break;
    }
}

void Core::AI::easy(Game *game)
{
    for (int i = 0; i < game->getBoard()->getSize(); i++)
    {
        for (int j = 0; j < game->getBoard()->getSize(); j++)
        {
            if ((game->getPlayer()->isBlack() && game->getBoard()->getField(i, j)->isBlack()) ||
                (game->getPlayer()->isWhite() && game->getBoard()->getField(i, j)->isWhite()))
            {
                game->selectDisk(i, j);

                for (int x = 0; x < game->getBoard()->getSize(); x++)
                {
                    for (int y = 0; y < game->getBoard()->getSize(); y++)
                    {
                        if (game->checkMove(x, y))
                        {
                            game->placeDisk(x, y);
                            game->switchTurn();
                            return;
                        }
                    }
                }
            }
        }
    }
}

void Core::AI::intermediate(Game *game)
{
    for (int i = game->getBoard()->getSize() - 1; i >= 0; i--)
    {
        for (int j = game->getBoard()->getSize() - 1; j >= 0; j--)
        {
            if ((game->getPlayer()->isBlack() && game->getBoard()->getField(i, j)->isBlack()) ||
                (game->getPlayer()->isWhite() && game->getBoard()->getField(i, j)->isWhite()))
            {
                game->selectDisk(i, j);

                for (int x = game->getBoard()->getSize() - 1; x >= 0; x--)
                {
                    for (int y = game->getBoard()->getSize() - 1; y >= 0; y--)
                    {
                        if (game->checkMove(x, y))
                        {
                            game->placeDisk(x, y);
                            game->switchTurn();
                            return;
                        }
                    }
                }
            }
        }
    }
}
