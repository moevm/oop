//
// Created by max on 25.03.20.
//

#include "Game.h"

void Game::runGame() {
    int x_field,y_field, max_number_of_objects,x,y;
    BaseAction base_action;
    UnitAction unit_action;
    cout << "Начало игры\n";
    while (1) {
        cout << "Введите размеры поля:";
        cin >> x_field >> y_field;
        if(x_field >= 5 && y_field >= 5)
            break;
        else
            cout << "Каждая компонента поля должна быть >= 5\n";
    }
    cout << "Введите максимальное количество объектов на поле\n";
    cin >> max_number_of_objects;
    Field f(max_number_of_objects,x_field,y_field);
    cout << "Создали поле\n";
    f.printField();
    base_action.setBase(&f);
    f.printField();
    int player_move;
    bool check = false;
    while (1){
        cout << "Сделвйте ход: \n";
        cout << "-1 - завершить игру\n";
        cout << "0 - пропустить ход\n";
        cout << "1 - Выбрать юнита\n";
        cout << "2 - Выбрать базу\n";
        cin >> player_move;
        if(player_move == -1)
            break;
        switch (player_move){//ход игрока
            case 0:
                check = true;
                break;
            case 1://выбрать юнита
                unit_action.run(check,&f);
                break;
            case 2:
                base_action.run(&f,check);
                break;;
        }
        if(check){
            f.printField();
            cout << "Ход закончен\n";
        }
        check = false;
    }
}