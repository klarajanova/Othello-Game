/*
    Autor:    Daniel Hladík    login: xhladi21
    Autor:    Klára Jánová     login: xjanov10
    Popis:    Hlavní soubor pro textovou verzi hry
*/

#include "../core/game.h"

#include <iostream>

using namespace std;

int newGameInfo()
{
    string answer="No";
    int boardSize=0;

    while(boardSize!=6 && boardSize!=8 && boardSize != 10 && boardSize != 12)
    {
        cout<<endl<<"Do you want to choose your own board size? (Yes/No)";
        cin>>answer;

        if(answer=="Yes")
        {
            cout<<endl<<"Input size of the board (6/8/10/12): ";
            cin>>boardSize;
            cin.clear();
            cin.ignore();
        }
        else if(answer=="No")
        {
            boardSize=8;
        }
    }
    return boardSize;
}

void printRoute(int boardSize, Core::Game *game)
{
    for(int i=0; i<boardSize; i++)
    {
        for(int j=0; j<boardSize; j++)
        {
             Core::Field *field=game->getBoard()->getField(i,j);

             if(field->isEmpty())
             {
                 cout<<"."; //misto E tecka pro lepsi prehlednost
             }
             else if(field->isBlack())
             {
                 cout<<"B";
             }
             else if(field->isWhite())
             {
                 cout<<"W";
             }
        }
        cout<<endl;
    }
}

int main()
{
    int row;
    int col;
    int boardSize;
    string opponent;

    cout<<"OTHELLO BOARD GAME "<<endl<<endl;

    do
    {
        cout<<"Pick an opponent (Human/Computer): ";
        cin>>opponent;
    } while(opponent!="Human" && opponent !="Computer");

    boardSize=newGameInfo(); //get size of the board
    Core::Game *game = new Core::Game(boardSize, opponent.c_str(),Core::AI::Difficulty::EASY);

    do
    {
      printRoute(boardSize, game); //print out board

      Core::Player *p1= game->getPlayer1();
      Core::Player *p2= game->getPlayer2();

      do
      {
          cout<<endl<<"Input coordinates of the disc you want to move:"<<endl;

          cout<<"R:";  //get next move
          cin>>row;
          cin.clear();
          cin.ignore();

          cout<<"C:";
          cin>>col;
          cin.clear();
          cin.ignore();
      } while(!game->selectDisk(row,col));

      do
      {
        cout<<"Input coordinates of the new position of the disc:"<<endl;

        cout<<"R:";  //get next move
        cin>>row;
        cin.clear();
        cin.ignore();

        cout<<"C:";
        cin>>col;
        cin.clear();
        cin.ignore();
      } while(!game->checkMove(row,col));

      game->placeDisk(row,col,true); //place disc

      bool _undo=false;
      bool _redo=false;
      string u;
      string r="No";

      int t1 = p1->score();
      int t2 = p2->score();

      cout<<"--------------------------------"<<endl        //print out score after each move
          <<"SCORE: "<<"("<< t1<< "/" << t2 << ")"<<endl
          <<"--------------------------------"<<endl;
      cout<<"--------------------------------"<<endl
          <<"Undo move? (Yes/No)";

      cin>>u;
      cin.clear();
      cin.ignore();

      if(u=="Yes")
      {
          _undo=true;
      }

      cout<<"--------------------------------"<<endl;

      if(_undo==true)
      {
          game->undo();

          cout<<"--------------------------------"<<endl<<
                "Redo move? (Yes/No)";

          cin>>r;
          cin.clear();
          cin.ignore();

          if(r=="Yes")
          {
              _redo=true;
          }

          if(_redo==true)
          {
              game->redo();
              cout<<"--------------------------------"<<endl;
          }
      }
      game->switchTurn();
    } while(!game->end());

    int winner=game->whoWon();

    if(winner==0)
    {
        cout<<endl<<"GAME OVER: It's a tie!" <<endl<<endl;
    }
    else if(winner==1)
    {
        cout<<endl<<"GAME OVER: Player 1 won!"<<endl<<endl;
    }
    else if(winner==2)
    {
        cout<<endl<<"------------------------"<<endl<<endl<<
                    "GAME OVER: Player 2 won !"<<endl<<endl;
    }

    return EXIT_SUCCESS;
}
