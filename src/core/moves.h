/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavièkový soubor k moves.cpp
*/

#ifndef CORE_MOVES_H
#define CORE_MOVES_H

#include "move.h"

namespace Core
{
    class Moves
    {
        public:
            Moves(int boardSize); ///< Intializes Moves for history

            int count() { return _counter; } ///< Returns number of stored moves

            void addMove(int rowFrom, int colFrom, int rowTo, int colTo); ///< Adds move to Moves
            void saveToFile(QString opponent, QString difficulty); ///< Save Moves to file
            Move *next()
            {
                if (move[_counter] != nullptr)
                    return move[_counter++];
                else
                    return nullptr;
            } ///< Moves index to next Move
            Move *previous()
            {
                if (_counter > 0)
                    return move[--_counter];
                else
                    return nullptr;
            } ///< Moves index to previous move

        private:
            int _counter = 0;
            int _boardSize = 0;
            Move **move;

    };
}

#endif // CORE_MOVES_H
