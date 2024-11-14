/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#include "game_status.h"

Dialog::GameStatus::GameStatus(Core::Game *game, QWidget *parent)
    : QDialog(parent)
{
    this->game = game;
    this->setDialog();
    this->addWidgets();
}

void Dialog::GameStatus::update()
{
    if (game->getPlayer()->isWhite())
        playing->setText(QString("White"));
    else if (game->getPlayer()->isBlack())
        playing->setText(QString("Black"));

    player1Score->setText(QString::number(game->getPlayer1()->score()));
    player1Disks->setText(QString::number(game->getPlayer1()->disks()));

    player2Score->setText(QString::number(game->getPlayer2()->score()));
    player2Disks->setText(QString::number(game->getPlayer2()->disks()));
}

void Dialog::GameStatus::setDialog()
{
    this->resize(WIDTH, HEIGHT);
    this->setWindowTitle(TITLE);
}

void Dialog::GameStatus::addWidgets()
{
    QHBoxLayout *hBoxLayout, *columns;
    QVBoxLayout *left, *right;

    mainLayout->setAlignment(Qt::AlignCenter);

    columns = new QHBoxLayout;

    left = new QVBoxLayout;
    left->setAlignment(Qt::AlignCenter);

    left->addWidget(new QLabel("Playing: "));
    left->addStretch();

    left->addWidget(new QLabel("Player 1"));

    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(new QLabel("Score: "));
    hBoxLayout->addWidget(player1Score);
    left->addLayout(hBoxLayout);

    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(new QLabel("Disks remaining: "));
    hBoxLayout->addWidget(player1Disks);
    left->addLayout(hBoxLayout);

    columns->addLayout(left);
    columns->addStretch();

    right = new QVBoxLayout;
    right->setAlignment(Qt::AlignCenter);

    right->addWidget(playing);
    right->addStretch();

    right->addWidget(new QLabel("Player 2"));

    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(new QLabel("Score: "));
    hBoxLayout->addWidget(player2Score);
    right->addLayout(hBoxLayout);

    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(new QLabel("Disks remaining: "));
    hBoxLayout->addWidget(player2Disks);
    right->addLayout(hBoxLayout);

    columns->addLayout(right);


    mainLayout->addLayout(columns);


    this->update();

    this->setLayout(mainLayout);
}
