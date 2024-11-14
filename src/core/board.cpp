/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Soubor pro funkce s manipulací desky
*/

#include "board.h"

Core::Board::Board(int size)
{
    // Init variables
    this->size = size;

    // Set up board
    this->setBoard();
}

void Core::Board::setBoard()
{
    // Alloc memory
    field = new Field **[size];
    for (int i = 0; i < size; i++)
    {
        field[i] = new Field *[size];
        for (int j = 0; j < size; j++)
            field[i][j] = new Field;
    }

    // Put starting disks on board
    field[size/2 - 1][size/2 - 1]->setWhite();
    field[size/2 - 1][size/2]->setBlack();
    field[size/2][size/2 - 1]->setBlack();
    field[size/2][size/2]->setWhite();

}

void Core::Board::resetBoard()
{
    // Remove all disks from board
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            field[i][j]->setEmpty();

    // Put starting disks on board
    field[size/2 - 1][size/2 - 1]->setWhite();
    field[size/2 - 1][size/2]->setBlack();
    field[size/2][size/2 - 1]->setBlack();
    field[size/2][size/2]->setWhite();
}
