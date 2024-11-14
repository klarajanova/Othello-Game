/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#include "new_game.h"
#include "../gui/gui_game.h"

Dialog::NewGame::NewGame()
{
    this->setDialog();
    this->addWidgets();
    this->exec();
}

void Dialog::NewGame::addWidgets()
{
    QGroupBox *groupBox, *difficultyGroupBox = new QGroupBox("Difficulty:");
    QHBoxLayout *buttonLayout, *radioLayout;
    QPushButton *button;
    QRadioButton *radioButton;

    groupBox = new QGroupBox("Opponent:");
    radioLayout = new QHBoxLayout;

    radioButton = new QRadioButton("Human");
    radioButton->setChecked(true); // Human is default value for opponent
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        opponent = "Human";
        difficultyGroupBox->setVisible(false);
        this->adjustSize();
    });
    radioLayout->addWidget(radioButton);

    radioButton = new QRadioButton("Computer");
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        opponent = "Computer";
        difficultyGroupBox->setVisible(true);
    });
    radioLayout->addWidget(radioButton);

    groupBox->setLayout(radioLayout);
    mainLayout->addWidget(groupBox);

    radioLayout = new QHBoxLayout;

    radioButton = new QRadioButton("Easy");
    radioButton->setChecked(true); // Easy is default value for difficulty
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        difficulty = Core::AI::EASY;
    });
    radioLayout->addWidget(radioButton);

    radioButton = new QRadioButton("Intermediate");
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        difficulty = Core::AI::INTERMEDIATE;
    });
    radioLayout->addWidget(radioButton);

    difficultyGroupBox->setVisible(false);
    difficultyGroupBox->setLayout(radioLayout);
    mainLayout->addWidget(difficultyGroupBox);


    groupBox = new QGroupBox("Board size:");
    radioLayout = new QHBoxLayout;

    radioButton = new QRadioButton("6");
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        boardSize = 6;
    });
    radioLayout->addWidget(radioButton);

    radioButton = new QRadioButton("8");
    radioButton->setChecked(true); // 8 is default value for board size
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        boardSize = 8;
    });
    radioLayout->addWidget(radioButton);

    radioButton = new QRadioButton("10");
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        boardSize = 10;
    });
    radioLayout->addWidget(radioButton);

    radioButton = new QRadioButton("12");
    connect(radioButton, &QRadioButton::clicked, this, [=]() {
        boardSize = 12;
    });
    radioLayout->addWidget(radioButton);

    groupBox->setLayout(radioLayout);
    mainLayout->addWidget(groupBox);


    // Bottom buttons
    buttonLayout = new QHBoxLayout;

    button = new QPushButton("Start Game");
    connect(button, &QPushButton::clicked, this, &Dialog::NewGame::startGame);
    buttonLayout->addWidget(button);

    button = new QPushButton("Close");
    connect(button, &QPushButton::clicked, this, &Dialog::NewGame::close);
    buttonLayout->addWidget(button);

    mainLayout->addLayout(buttonLayout);
}

void Dialog::NewGame::setDialog()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setLayout(mainLayout);
    this->setWindowTitle(TITLE);
}

void Dialog::NewGame::startGame()
{
    new GUI::Game(boardSize, opponent, difficulty);
    this->close();
}
