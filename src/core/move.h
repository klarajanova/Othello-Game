/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavièkový soubor k move.cpp
*/

#ifndef CORE_MOVE_H
#define CORE_MOVE_H

namespace Core
{
    class Move
    {
        public:
            Move(int rowFrom, int colFrom, int rowTo, int colTo); ///< Initializes Move

            int rowFrom() { return _rowFrom; } ///< Returns row of beginning of move
            int colFrom() { return _colFrom; } ///< Returns column of beginning of move
            int rowTo() { return _rowTo; } ///< Returns row of end of move
            int colTo() { return _colTo; } ///< Returns column of end of move

        private:
            int _rowFrom;
            int _colFrom;
            int _rowTo;
            int _colTo;
    };
}

#endif // CORE_MOVE_H
