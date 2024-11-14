/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Soubor pro funkce s manipulací hry
*/

#include <cmath>
#include "game.h"

Core::Game::Game(int boardSize, QString opponent, AI::Difficulty difficulty)
{
    board = new Board(boardSize);
    moves = new Moves(boardSize);

    player1 = new Human;
    player1->setBlack();
    player1->setDisks(boardSize * boardSize - 2);
    player1->increaseScore(2);

    if (opponent == "Human")
        player2 = new Human;
    else if (opponent == "Computer")
        player2 = new Computer(difficulty);
    player2->setWhite();
    player2->setDisks(boardSize * boardSize - 2);
    player2->increaseScore(2);

    player = player1;
}

bool Core::Game::checkMove(int row, int col)
{
    int diskRow = this->diskRow;
    int diskCol = this->diskCol;
    bool empty = false;
    bool disk = false;

    // Return false if move is not in horizontal, vertical or diagonal line
    if (!((diskRow - row) == 0 || (diskCol - col) == 0) &&
        !(std::abs(diskRow - row) == std::abs(diskCol - col)))
        return false;

    // Return false if move is on same place
    if (row == diskRow && col == diskCol)
        return false;

    // Return false if destination field is not empty
    if (!board->getField(row, col)->isEmpty())
        return false;

    while (diskRow != row || diskCol != col)
    {
        if (diskRow > row)
            diskRow--;
        else if (diskRow < row)
            diskRow++;

        if (diskCol > col)
            diskCol--;
        else if (diskCol < col)
            diskCol++;

        if (board->getField(diskRow, diskCol)->isWhite() && player->isWhite())
            return false;

        if (board->getField(diskRow, diskCol)->isBlack() && player->isBlack())
            return false;

        if (board->getField(diskRow, diskCol)->isEmpty() && empty)
            return false;

        if (!disk && diskRow == row && diskCol == col)
            return false;

        if (board->getField(diskRow, diskCol)->isEmpty())
            empty = true;

        if (!board->getField(diskRow, diskCol)->isEmpty())
            disk = true;
    }

    return true;
}

void Core::Game::placeDisk(int row, int col, bool addMove)
{
    // Check if move is valid
    if (!checkMove(row, col))
        return;

    // Add move to memory
    if (addMove)
        moves->addMove(diskRow, diskCol, row, col);

    // Place disk all the way till the end
    while (diskRow != row || diskCol != col)
    {
        if (diskRow > row)
            diskRow--;
        else if (diskRow < row)
            diskRow++;

        if (diskCol > col)
            diskCol--;
        else if (diskCol < col)
            diskCol++;

        if (player->isBlack())
        {
            if (board->getField(diskRow, diskCol)->isWhite())
            {
                if (player1->isWhite())
                    player1->decreaseScore(1);
                else if (player2->isWhite())
                    player2->decreaseScore(1);
            }
            
            board->getField(diskRow, diskCol)->setBlack();
        }
        else if (player->isWhite())
        {
            if (board->getField(diskRow, diskCol)->isBlack())
            {
                if (player1->isBlack())
                    player1->decreaseScore(1);
                else if (player2->isBlack())
                    player2->decreaseScore(1);
            }

            
            board->getField(diskRow, diskCol)->setWhite();
        }
        
        player->increaseScore(1);
    }

    // Remove disk from player
    player->setDisks(player->disks() - 1);

    // Deselect disk
    this->deselectDisk();
}

void Core::Game::redo()
{
    Move *move = moves->next();
    if (move == nullptr)
        return;

    int rowTo = move->rowTo();
    int colTo = move->colTo();
    int rowFrom = move->rowFrom();
    int colFrom = move->colFrom();

    this->selectDisk(rowFrom, colFrom);
    this->placeDisk(rowTo, colTo, false);
    this->switchTurn();
}

bool Core::Game::selectDisk(int row, int col)
{
    if (board->getField(row, col)->isEmpty())
        return false;
    if (player->isBlack() && board->getField(row, col)->isWhite())
        return false;
    if (player->isWhite() && board->getField(row, col)->isBlack())
        return false;

    diskRow = row;
    diskCol = col;

    return true;
}

void Core::Game::switchTurn()
{
    if (player == player1)
        player = player2;
    else if (player == player2)
        player = player1;

    if (player->canMove(this))
    {
        qDebug("Player can move");

        if (player->isComputer())
            AI::play(this, ((Computer *) player)->getDifficulty());
    }
    else
    {
        qDebug("Player can't move");

        if (!player1->canMove(this) && !player2->canMove(this))
        {
            ended = true;
            return;
        }
        
        this->switchTurn();
    }
}

void Core::Game::undo()
{
    Move *move = moves->previous();
    if (move == nullptr)
        return;

    int rowTo = move->rowTo();
    int colTo = move->colTo();
    int rowFrom = move->rowFrom();
    int colFrom = move->colFrom();

    // Remove placed disk
    board->getField(rowTo, colTo)->setEmpty();
    player->setDisks(player->disks() + 1);

    // Place disk all the way till the end
    while (rowTo != rowFrom || colTo != colFrom)
    {
        if (rowTo > rowFrom)
            rowTo--;
        else if (rowTo < rowFrom)
            rowTo++;

        if (colTo > colFrom)
            colTo--;
        else if (colTo < colFrom)
            colTo++;

        if (player->isBlack())
        {
            if (board->getField(rowTo, colTo)->isWhite())
            {
                if (player1->isWhite())
                    player1->decreaseScore(1);
                else if (player2->isWhite())
                    player2->decreaseScore(1);
            }

            board->getField(rowTo, colTo)->setBlack();
        }
        else if (player->isWhite())
        {
            if (board->getField(rowTo, colTo)->isBlack())
            {
                if (player1->isBlack())
                    player1->decreaseScore(1);
                else if (player2->isBlack())
                    player2->decreaseScore(1);
            }

            board->getField(rowTo, colTo)->setWhite();
        }
        
        player->increaseScore(1);
        player->setDisks(player->disks() - 1);
    }

    if (player->isWhite())
        board->getField(rowTo, colTo)->setBlack();
    else if (player->isBlack())
        board->getField(rowTo, colTo)->setWhite();

    this->switchTurn();
}

void Core::Game::deselectDisk()
{
    diskRow = NONE;
    diskCol = NONE;
}

int Core::Game::whoWon() {
    if (player1->score() > player2->score())
        return 1;
    else if (player1->score() < player2->score())
        return 2;
    else
        return 0;
}

void Core::Game::setAI(AI::Difficulty difficulty)
{
    if (player2->isComputer())
    {
        ((Computer *) player2)->setDifficulty(difficulty);
    }
}
