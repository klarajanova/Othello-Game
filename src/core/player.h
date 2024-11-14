/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavièkový soubor k player.cpp
*/

#ifndef CORE_PLAYER_H
#define CORE_PLAYER_H

#include "ai.h"

namespace Core
{
    class Game;

    class Player
    {
        public:
            virtual bool isHuman() = 0;
            virtual bool isComputer() = 0;

            bool canMove(Game *game);
            const char *who();
            const char *difficulty();

            // Getters
            bool isBlack() { return (_color == BLACK); }
            bool isWhite() { return (_color == WHITE); }
            int disks() { return _disks; }
            int score() { return _score; }

            // Setters
            void setBlack() { _color = BLACK; }
            void setWhite() { _color = WHITE; }
            void setDisks(int disks) { _disks = disks; }
            void decreaseScore(int score) { _score -= score; }
            void increaseScore(int score) { _score += score; }

        private:
            enum Color { NONE, BLACK, WHITE };

            Color _color = NONE;
            int _score = 0;
            int _disks = 0;
    };

    class Human : public Player
    {
        public:
            Human() {}

            bool isHuman() { return true; }
            bool isComputer() { return false; }
    };

    class Computer : public Player
    {
        public:
            Computer(AI::Difficulty difficulty) {
                _difficulty = difficulty;
            }
            
            // Setters
            void setDifficulty(AI::Difficulty difficulty) {
                _difficulty = difficulty;
            }

            // Getters
            AI::Difficulty getDifficulty() { return _difficulty; }
            bool isHuman() { return false; }
            bool isComputer() { return true; }

        private:
            AI::Difficulty _difficulty = AI::NONE;
    };
}

#endif // CORE_PLAYER_H
