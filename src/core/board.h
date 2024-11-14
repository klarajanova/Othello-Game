/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavièkový soubor k board.cpp
*/

#ifndef CORE_BOARD_H
#define CORE_BOARD_H

#include "field.h"

namespace Core
{
    /**
     *  @brief Board for game
     */
    class Board
    {
        public:
            Board(int size); ///< Initializes board with size * size

            Field *getField(int row, int col) { return field[row][col]; } ///< Gets Field from board at specified position
            int getSize() { return size; } ///< Gets size of the board

            void resetBoard(); ///< Resets board to inital state

        private:
            void setBoard();

        private:
            int size;
            Field ***field;
    };
}

#endif // CORE_BOARD_H
