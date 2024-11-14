/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavièkový soubor k field.cpp
*/

#ifndef CORE_FIELD_H
#define CORE_FIELD_H

namespace Core
{
    class Field
    {
        public:
            Field() {}
            ~Field() {}

            bool isEmpty() { return (_disk == EMPTY); } ///< Checks if field is empty
            bool isBlack() { return (_disk == BLACK); } ///< Checks on field is black player's disk
            bool isWhite() { return (_disk == WHITE); }	///< Checks on field is white player's disk

            void setEmpty() { _disk = EMPTY; }	///< Make field empty
            void setBlack() { _disk = BLACK; }	///< Put black disk on field
            void setWhite() { _disk = WHITE; }	///< Put white disk on field

        private:
            enum Disk { EMPTY, BLACK, WHITE };

            Disk _disk = EMPTY;
    };
}

#endif // CORE_FIELD_H
