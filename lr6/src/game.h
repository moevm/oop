#include "field.h"
#include "rules.h"

#ifndef GAME_H
#define GAME_H

template <typename T>
class GameBase
{
protected:
    Field* gameField = nullptr;
    int loser;
};

template <typename Rules>
class Game: public GameBase<Rules>{

};

template <>
class Game<Rule1>: public GameBase<Rule1>{
    Rule1* rule1;
    static Game<Rule1> *game;
    Game<Rule1>(){

    }
public:
    static Game<Rule1>* getInst(){
        if (game == nullptr){
            game = new Game<Rule1>;
        }
        return game;
    }
    void createGame(){
        rule1 = new Rule1;
        this->gameField = rule1->createField();
    }
    void play(){                // тут будет цикл игры, в котором проверяется условие проигрыша и происходит передача действия определенному правилу
        Unit* unit = nullptr;
         while(true){
             int loser = rule1->isLose(gameField);
             if (!loser){
                 system("cls");
                 cout << "Change type of logging - '+'(no logging, logging in terminal, logging in file\n";
                 cout << "To save the game use 's', to load use 'd'\n";
                 cout << "   Player 1 keys:\n";
                 cout << "Create unit - 'u'\n";
                 cout << "Delete unit - 'f'\n";
                 cout << "Change current unit - 'TAB'\n";
                 cout << "Base info - 'm'\n\n";
                 cout << "   Player 2 keys:\n";
                 cout << "Create unit - 'n'\n";
                 cout << "Delete unit - ']'\n";
                 cout << "Change current unit - '-'\n";
                 cout << "Base info - 'l'\n\n";
                 cout << "Use arrows to move units, 'q' to quit\n\n";
                 if (unit)
                    gameField->printField(unit);
                 int gameFlag;
                 gameFlag = rule1->action();
                 if (gameFlag == 1){
                     delete this->gameField;
                     gameField = rule1->createField();
                     continue;
                 }
                 unit = rule1->getCurrentUnit();
             }
             else {
                 system("cls");
                 gameField->printField(unit);
                 if (loser == 1){
                     cout << "Player1 losed! Pathetic..." ;
                     break;
                 }
                 if (loser == 2){
                     cout << "Player2 losed! Pathetic..." ;
                     break;
                 }
             }
         }

    }
};

template<>
class Game<Rule2>: public GameBase<Rule2>{
    Rule2* rule2;
    static Game<Rule2> *game;
    Game<Rule2>(){

    }
public:
    static Game<Rule2>* getInst(){
        if (game == nullptr){
            game = new Game<Rule2>;
        }
        return game;
    }
    void createGame(){
        rule2 = new Rule2;
        this->gameField = rule2->createField();
    }
    void play(){
        Unit* unit = nullptr;
        int counter = 0;
        while(true){
            int loser = rule2->isLose(gameField);
            if (!loser){
                system("cls");
                cout << "Change type of logging - '+'(no logging, logging in terminal, logging in file\n";
                cout << "To save the game use 's', to load use 'd'\n";
                cout << "   Player 1 keys:\n";
                cout << "Create unit - 'u'\n";
                cout << "Delete unit - 'f'\n";
                cout << "Change current unit - 'TAB'\n";
                cout << "Base info - 'm'\n\n";
                cout << "   Player 2 keys:\n";
                cout << "Create unit - 'n'\n";
                cout << "Delete unit - ']'\n";
                cout << "Change current unit - '-'\n";
                cout << "Base info - 'l'\n\n";
                cout << "Use arrows to move units, 'q' to quit\n\n";
                cout << "Use 'g' to start new game\n";
                counter++;
                if (counter == 9){
                    counter = 0;
                    gameField->summonGold();
                }
                if (unit)
                    gameField->printField(unit);
                int gameFlag;
                gameFlag = rule2->action();
                if (gameFlag == 1){
                    delete this->gameField;
                    gameField = rule2->createField();
                    continue;
                }
                unit = rule2->getCurrentUnit();
            }
            else {
                if (loser)
                    break;
            }
        }
    }
};


#endif // GAME_H
