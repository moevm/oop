#include <iostream>
#include <QDebug>

#include "gamefield.h"
#include "unit.h"

using std::cout;
using std::endl;
using std::cin;

int main()
{
    int x, y; //, a; - понадобится в create_field
    cout << "Введите размер поля в формате: \nx y" << endl;
    cin >> x >> y;
    GameField *F = new GameField(x, y);

    //create_field

    int menu;

    F->fill_field();

    F->print_field();
    cout << endl;

    while(1){
        cout << "0. Выход" << endl;
        cout << "1. Вывести поле на экран" << endl;
        cout << "2. Добавить юнит на поле по координатам x, y. Тип юнита может быть 1, 2 или 3" << endl;
        cout << "3. Переместить юнит с координат x_from, y_from в координаты x_to, y_to" << endl;
        cout << "4. Удалить юнит с координат x, y" << endl;
        cout << "5. Узнать количество юнитов" << endl;
        cout << "6. Копировать поле" << endl;

        cin >> menu;

        switch (menu) {
        case 0:
            cout << "Okey!" << endl;
            return 0;
        case 1:
            cout << endl;
            F->print_field();
            cout << endl;
            break;
        case 2:
            int x_add, y_add, hero_code;
            cin >> x_add >> y_add >> hero_code;
            F->add_hero(x_add, y_add, hero_code);
            break;
        case 3:
            int x_from, y_from, x_to, y_to;
            cin >> x_from >> y_from >> x_to >> y_to;
            F->move_hero(x_from, y_from, x_to, y_to);
            break;
        case 4:
            int x_del, y_del;
            cin >> x_del >> y_del;
            F->delete_hero(x_del, y_del);
            break;
        case 5:
            cout << "Максимальное количество юнитов: " << F->get_unit_max() << endl;
            cout << "Количество юнитов на поле: " << F->get_unit_count() << endl;
            break;
        case 6:
            F->copy_field();
            break;
        default:
            break;
        }
    }


    return 0;
}
