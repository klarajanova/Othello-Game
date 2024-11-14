/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Soubor k manipulaci s pohyby
*/

#include <QtWidgets>
#include "moves.h"

Core::Moves::Moves(int boardSize)
{
    this->_boardSize = boardSize;

    move = new Move *[boardSize * boardSize];
    for (int i = 0; i < boardSize * boardSize; i++)
        move[i] = nullptr;
}

void Core::Moves::addMove(int rowFrom, int colFrom, int rowTo, int colTo)
{
    for (int i = _counter; move[i] != nullptr; i++)
    {
        delete move[i];
        move[i] = nullptr;
    }
    move[_counter++] = new Move(rowFrom, colFrom, rowTo, colTo);
}

void Core::Moves::saveToFile(QString opponent, QString difficulty)
{
    QString filename = QFileDialog::getSaveFileName();
    if (filename.isNull())
        return;

    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly);

    file->write(QByteArray::number(_boardSize) + "-"
                + opponent.toUtf8() + "-"
                + difficulty.toUtf8() + "\n");

    for (int i = 0; i < _counter; i++)
        file->write(
            QByteArray::number(move[i]->rowFrom()) + "-" +
            QByteArray::number(move[i]->colFrom()) + "-" +
            QByteArray::number(move[i]->rowTo()) + "-" +
            QByteArray::number(move[i]->colTo()) + "\n"
        );

    file->close();
}
