/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#include "gui_game.h"
#include "../core/ai.h"
#include "../core/field.h"

GUI::Game::Game(int boardSize, QString opponent, Core::AI::Difficulty difficulty)
{
    this->resize(WIDTH, HEIGHT);
    this->setGUI(boardSize, opponent, difficulty);
    this->setWindowTitle(TITLE);
    this->show();
}

void GUI::Game::gameEnd()
{
    qDebug() << "GAME END";
    
    delete mainLayout;
    
    mainLayout = new QVBoxLayout;
    
    QLabel *label = new QLabel;
    
    if (game->whoWon() == 1)
        label->setText("Player1 Won!");
    else if (game->whoWon() == 2)
        label->setText("Player2 Won!");
    else
        label->setText("Tie!");
    
    label->setAlignment(Qt::AlignHCenter);
    label->setStyleSheet(
        "QLabel { border: 1px solid black; background-color: green; color: black; }"
    );
    
    mainLayout->addWidget(label);
    this->setLayout(mainLayout);
}

void GUI::Game::showMoves()
{
    QHBoxLayout *rowLayout, *fieldLayout;
    QLabel *labelField, *labelDisk;
    
    for (int i = 0; i < game->getBoard()->getSize(); i++)
    {
        for (int j = 0; j < game->getBoard()->getSize(); j++)
        {
            if ((game->getPlayer()->isBlack() && game->getBoard()->getField(i, j)->isBlack()) ||
                (game->getPlayer()->isWhite() && game->getBoard()->getField(i, j)->isWhite()))
            {
                game->selectDisk(i, j);

                for (int x = 0; x < game->getBoard()->getSize(); x++)
                {
                    rowLayout = (QHBoxLayout *) mainLayout->itemAt(x);
                    
                    for (int y = 0; y < game->getBoard()->getSize(); y++)
                    {
                        if (game->checkMove(x, y))
                        {
                            labelField = (QLabel *) rowLayout->itemAt(y)->widget();
                            fieldLayout = (QHBoxLayout *) labelField->layout();
                            labelDisk = (QLabel *) fieldLayout->itemAt(0)->widget();
                            
                            labelDisk->setStyleSheet("QLabel { color: rgba(0, 0, 0, 50%); }");
                        }
                    }
                }
                
                game->deselectDisk();
            }
        }
    }
}

void GUI::Game::setGUI(int boardSize, QString opponent, Core::AI::Difficulty difficulty)
{
    Core::Field *field;
    QHBoxLayout *rowLayout, *fieldLayout;
    QLabel *labelField, *labelDisk;

    game = new Core::Game(boardSize, opponent, difficulty);
    gameStatus = new Dialog::GameStatus(game, this);
    history = new Dialog::History(this, this);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    for (int i = 0; i < boardSize; i++)
    {
        // Layout for each row
        rowLayout = new QHBoxLayout;
        rowLayout->setSpacing(0);

        for (int j = 0; j < boardSize; j++)
        {
            // Get field from board
            field = game->getBoard()->getField(i, j);

            // Alloc memory
            fieldLayout = new QHBoxLayout;
            labelField = new QLabel;
            labelDisk = new QLabel;

            // Set style for field
            labelField->setStyleSheet(
                "QLabel { border: 1px solid black; background-color: green; }"
            );

            // Set style disk
            labelDisk->setScaledContents(true);
            labelDisk->setStyleSheet("QLabel { border: 0; }");
            if (field->isEmpty())
                labelDisk->setPixmap(QPixmap());
            else if (field->isBlack())
                labelDisk->setPixmap(PIXMAP_BLACKDISK);
            else if (field->isWhite())
                labelDisk->setPixmap(PIXMAP_WHITEDISK);

            fieldLayout->addWidget(labelDisk);
            labelField->setLayout(fieldLayout);

            rowLayout->addWidget(labelField);
        }

        mainLayout->addLayout(rowLayout);
    }

    this->setLayout(mainLayout);
}

void GUI::Game::mousePressEvent(QMouseEvent *event)
{
    if (game->end())
        return;
    
    // GUI Fix
    if (((QLabel *) this->childAt(event->x(), event->y()))->children().count() != 0)
        return;
    
    int row = event->y() / (this->height() / game->getBoard()->getSize());
    int col = event->x() / (this->width() / game->getBoard()->getSize());

    if (game->getPlayer()->isComputer())
    {
        qDebug("Computer is playing");
        return;
    }

    // If disk is not selected and belongs to player then select it
    if(!game->isDiskSelected())
    {
        if (game->selectDisk(row, col))
        {

            ((QLabel *)((QLabel *) this->childAt(event->x(), event->y()))
                ->parentWidget())
                ->setStyleSheet(
                    "QLabel {"
                        "border: 1px solid black;"
                        "background-color: darkgreen;"
                    "}"
                );
        }
        else
        {
            qDebug() << "This is not your disk";
        }
    }
    // Check move and if it's valid place disks
    else if (game->isDiskSelected() && game->checkMove(row, col))
    {
        game->placeDisk(row, col);
        game->switchTurn();
        this->refreshGUI();

        if (game->end())
            this->gameEnd();
    }
    // If selected disk is clicked then deselect it
    else if (game->isDiskSelected() &&
             game->getSelectedDiskRow() == row &&
             game->getSelectedDiskCol() == col)
    {
        game->deselectDisk();
        ((QLabel *)((QLabel *) this->childAt(event->x(), event->y()))
            ->parentWidget())
            ->setStyleSheet(
                "QLabel {"
                    "border: 1px solid black;"
                    "background-color: green;"
                "}"
            );
    }
}

void GUI::Game::refreshGUI()
{
    Core::Field *field;
    QHBoxLayout *rowLayout, *fieldLayout;
    QLabel *labelField, *labelDisk;

    for (int i = 0; i < game->getBoard()->getSize(); i++)
    {
        rowLayout = (QHBoxLayout *) mainLayout->itemAt(i);

        for (int j = 0; j < game->getBoard()->getSize(); j++)
        {
            labelField = (QLabel *) rowLayout->itemAt(j)->widget();
            fieldLayout = (QHBoxLayout *) labelField->layout();
            labelDisk = (QLabel *) fieldLayout->itemAt(0)->widget();

            // Remove selection
            labelField->setStyleSheet(
                "QLabel { border: 1px solid black; background-color: green; }"
            );
            
            // Remove hint
            labelDisk->setStyleSheet("QLabel { border: 0px; }");

            // Get field from board
            field = game->getBoard()->getField(i, j);

            if (field->isEmpty())
                labelDisk->setPixmap(QPixmap());
            else if (field->isBlack())
                labelDisk->setPixmap(PIXMAP_BLACKDISK);
            else if (field->isWhite())
                labelDisk->setPixmap(PIXMAP_WHITEDISK);
        }
    }

    gameStatus->update();
    history->update();
}

void GUI::Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_H)
    {
        history->show();
    }
    else if (event->key() == Qt::Key::Key_I)
    {
        gameStatus->show();
    }
    else if (event->key() == Qt::Key::Key_R)
    {
        game->redo();
        this->refreshGUI();
    }
    else if (event->key() == Qt::Key::Key_S)
    {
        game->getMoves()->saveToFile(game->getPlayer2()->who(),
                                     game->getPlayer2()->difficulty());
    }
    else if (event->key() == Qt::Key::Key_U)
    {
        game->undo();
        this->refreshGUI();
    }
    else if (event->key() == Qt::Key::Key_Control)
    {
        this->showMoves();
    }
}

void GUI::Game::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Control)
    {
        this->refreshGUI();
    }
}

void GUI::Game::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    gameStatus->close();
    history->close();
}
