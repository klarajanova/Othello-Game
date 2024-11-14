/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#include "othello.h"
#include "gui_game.h"
#include "../core/ai.h"
#include "../dialog/new_game.h"

Othello::Othello()
{
    this->setFixedSize(WIDTH, HEIGHT);
    this->setWindow();
    this->setWindowTitle(TITLE);
}

void Othello::setWindow()
{
    QVBoxLayout *mainLayout;
    QPushButton *button;
    QWidget *widget;

    mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);

    widget = new QWidget;
    widget->setLayout(mainLayout);
    widget->setStyleSheet(
        "QWidget { background-image: url(" + IMAGE_SPLAH + ") }"
        "QPushButton {"
            "color: #ffffff;"
            "font-weight: bold;"
            "height: 50px;"
            "border: 2px solid white;"
            "background-image: url(\"\");"
            "background-color: rgba(0, 0, 0, 0.5);"
        "}"
    );

    button = new QPushButton("New Game");
    connect(button, &QPushButton::clicked, this, &Othello::newGame);
    mainLayout->addWidget(button);

    button = new QPushButton("Load Game");
    connect(button, &QPushButton::clicked, this, &Othello::loadGame);
    mainLayout->addWidget(button);

    button = new QPushButton("Exit");
    connect(button, &QPushButton::clicked, this, &Othello::close);
    mainLayout->addWidget(button);

    this->setCentralWidget(widget);
}

void Othello::newGame()
{
    new Dialog::NewGame;
}

void Othello::loadGame() {
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isNull())
        return;

    QFile *file = new QFile(filename);
    file->open(QIODevice::ReadOnly);

    QTextStream stream(file);
    QString settings = stream.readLine();
    qint32 boardSize = settings.split('-').at(0).toInt();
    QString opponent = settings.split('-').at(1);
    
    Core::AI::Difficulty difficulty = Core::AI::NONE;
    if (settings.split('-').at(2) == "EASY")
        difficulty = Core::AI::EASY;
    else if (settings.split('-').at(2) == "INTERMEDIATE")
        difficulty = Core::AI::INTERMEDIATE;

    GUI::Game *game = new GUI::Game(boardSize, opponent);

    QString line;
    while (!(line = stream.readLine()).isEmpty()) {
        game->getCoreGame()->selectDisk(
            line.split('-').at(0).toInt(),
            line.split('-').at(1).toInt()
        );
        game->getCoreGame()->placeDisk(
            line.split('-').at(2).toInt(),
            line.split('-').at(3).toInt()
        );
        game->getCoreGame()->switchTurn();
    }
    
    game->getCoreGame()->setAI(difficulty);
    game->refreshGUI();

    file->close();
}
