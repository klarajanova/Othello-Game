/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
*/

#ifndef DIALOG_HISTORY_H
#define DIALOG_HISTORY_H

#include <QtWidgets>
#include "../core/game.h"
#include "../gui/gui_game.h"

namespace GUI
{
    class Game;
}

namespace Dialog
{
    class History : public QDialog
    {
        public:
            History(GUI::Game *game, QWidget *parent);
            void update();
            
        private:
            void addWidgets();
            void setDialog();
            void moveTo(int move);
            
        private:
            const QString TITLE = "History";
            
            Core::Game *coreGame;
            GUI::Game *guiGame;
            QListView *listView = new QListView;
            QStringList *list = new QStringList;
            QStringListModel *model = new QStringListModel;
            QVBoxLayout *mainLayout = new QVBoxLayout;
    };
}

#endif // DIALOG_HISTORY_H
