/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Soubor pro funkce spojené s hráèem
*/

#include "game.h"
#include "player.h"

bool Core::Player::canMove(Game *game)
{
    Player *player = game->getPlayer();
    game->setPlayer(this);
    
    for (int i = 0; i < game->getBoard()->getSize(); i++)
    {
        for (int j = 0; j < game->getBoard()->getSize(); j++)
        {
            if ((this->isBlack() && game->getBoard()->getField(i, j)->isBlack()) ||
                (this->isWhite() && game->getBoard()->getField(i, j)->isWhite()))
            {
                game->selectDisk(i, j);

                for (int x = 0; x < game->getBoard()->getSize(); x++)
                {
                    for (int y = 0; y < game->getBoard()->getSize(); y++)
                    {
                        if (game->checkMove(x, y))
                        {
                            game->deselectDisk();
                            
                            game->setPlayer(player);
                            return true;
                        }
                    }
                }

                game->deselectDisk();
            }
        }
    }

    game->setPlayer(player);
    return false;
}

const char *Core::Player::who()
{
    if (this->isHuman())
        return "Human";
    else if (this->isComputer())
        return "Computer";
    
    return "Unknown";
}

const char *Core::Player::difficulty()
{
    if (this->isComputer())
    {
        switch (((Computer *) this)->getDifficulty())
        {
            case AI::EASY:
                return "EASY";
            case AI::INTERMEDIATE:
                return "INTERMEDIATE";
            default:
                return "NONE";
        }
    }
    
    return "NONE";
}
