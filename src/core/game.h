/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavièkový soubor k game.cpp
*/

#ifndef CORE_GAME_H
#define CORE_GAME_H

#include <QString>
#include "ai.h"
#include "board.h"
#include "moves.h"
#include "player.h"

namespace Core
{
    /**
     *  @brief Game
     */
    class Game
    {
        public:
            Game(int boardSize, QString opponent, AI::Difficulty difficulty = AI::NONE);    ///< Initialize game

            bool checkMove(int row, int col); ///< Checks if move is possible
            void deselectDisk(); ///< Deselect selected disk
            void placeDisk(int row, int col, bool addMove = true); ///< Place disk on defined position and adds move to history
            void redo(); ///< Redo move (1)
            bool selectDisk(int row, int col); ///< Selects disk on defined position
            void switchTurn(); ///< Switches turn
            void undo(); ///< Undo move (1)
            int whoWon(); ///< Return number of player who won the game
            
            void setAI(AI::Difficulty difficulty); ///< Sets AI difficulty
            void setPlayer (Player *player) { this->player = player; }  ///< Sets Player

            Moves *getMoves() { return moves; } ///< Returns Moves
            Board *getBoard() { return board; } ///< Returns Board
            Player *getPlayer() { return  player; } ///< Returns current playing Player
            Player *getPlayer1() { return player1; } ///< Returns Player 1
            Player *getPlayer2() { return player2; } ///< Returns Player 2
            bool end() { return ended; } ///< Checks if game ended
            int getSelectedDiskRow() { return diskRow; } ///< Returns number of row where disk is selected
            int getSelectedDiskCol() { return diskCol; } ///< Returns number of column where disk is selected
            bool isDiskSelected() { 
                return (diskRow != NONE && diskCol != NONE);
            } ///< Checks if any disk is selected


        private:
            const int NONE = -1;

            bool ended = false;
            int diskRow = NONE;
            int diskCol = NONE;
            Board *board;
            Moves *moves;
            Player *player, *player1, *player2;
    };
}

#endif // CORE_GAME_H
