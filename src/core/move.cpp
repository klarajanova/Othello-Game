/*
    Autor:    Daniel Hlad�k    login: xhladi21
    Autor:    Kl�ra J�nov�     login: xjanov10
    Popis:    Soubor pro uchov�n� pohybu
*/

#include "move.h"

Core::Move::Move(int rowFrom, int colFrom, int rowTo, int colTo)
{
    this->_rowFrom = rowFrom;
    this->_colFrom = colFrom;
    this->_rowTo = rowTo;
    this->_colTo = colTo;
}
