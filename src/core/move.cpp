/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Soubor pro uchování pohybu
*/

#include "move.h"

Core::Move::Move(int rowFrom, int colFrom, int rowTo, int colTo)
{
    this->_rowFrom = rowFrom;
    this->_colFrom = colFrom;
    this->_rowTo = rowTo;
    this->_colTo = colTo;
}
