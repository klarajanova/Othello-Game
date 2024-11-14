/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#include "history.h"
#include "../core/moves.h"

Dialog::History::History(GUI::Game *game, QWidget *parent)
    : QDialog(parent)
{
    this->coreGame = game->getCoreGame();
    this->guiGame = game;
    this->setDialog();
    this->addWidgets();
}

void Dialog::History::update()
{
    qDebug() << coreGame->getMoves()->count();
    
    list->clear();
    
    for (int i = 0; i < coreGame->getMoves()->count(); i++)
        list->append(QString("Move ") + QString::number(i));
    
    model->setStringList(*list);
    listView->scrollToBottom();
}

void Dialog::History::setDialog()
{
    this->setWindowTitle(TITLE);
}

void Dialog::History::addWidgets()
{
    model->setStringList(*list);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listView->setModel(model);
    mainLayout->addWidget(listView);
    
    connect(listView, &QAbstractItemView::doubleClicked, this, [=](){
        qDebug() << listView->currentIndex().row();
        moveTo(listView->currentIndex().row());
    });
    
    this->update();
    
    this->setLayout(mainLayout);
}

void Dialog::History::moveTo(int move)
{
    while (coreGame->getMoves()->count() != move)
        coreGame->undo();
    
    guiGame->refreshGUI();
}
