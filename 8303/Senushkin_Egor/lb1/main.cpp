#include <iostream>
#include "Map/Field.h"
#include "Unit/LongRange/Archer.h"
#include "Unit/LongRange/Wizard.h"
#include "Unit/SwordMan/LongSwordMan.h"
#include "Unit/SwordMan/ShildMan.h"
#include "Unit/Rider/SpearHorse.h"
#include "Unit/Rider/HeavyCavalry.h"
#include "Unit/Factory/LongRangeFactory.h"
#include "Unit/Factory/RiderFactory.h"
#include "Unit/Factory/SwordManFactory.h"
#include "Map/Point.h"



using namespace std;

int main() {
    int n, m;
    cout << "Введите размеры поля" << endl;
    cin >> n >> m;

    LongRangeFactory LRF;
    RiderFactory RF;
    SwordManFactory SMF;

    Field game(n, m);
    game.print();

    char command;
    do{
        cout << "Что вы хотите сделать?\nЕсли хотите добавить юнита нажмите 'a', если хотите удалить юнита нажмите 'd', если хотите переместить юнита нажите 'm', если хотите выйти нажмите 'e'\n";
        cin >> command;

        switch (command)
        {
            case 'a':
            {
                int type, x, y;
                cout << "Какого юнита вы хотите добавить и куда?\n"
                        "Лучник: 1\n"
                        "Маг: 2\n"
                        "Пехотинец с щитом: 3\n"
                        "Пехотиниц с двуручным мечом: 4\n"
                        "Тяжелый всадник: 5\n"
                        "Всадник с копьем: 6\n";
                cin >> type;
                if (type <= 0 || type >= 7)
                {
                    cout << "Такого юнита нет\n";
                    break;
                }
                cout << "Введите координаты куда вы хотите добавить юнита {x;y}\n";
                cin >> x >> y;

                switch (type)
                {
                    case 1:
                        game.addObject(LRF.createLotHealth(), x, y);
                        game.print();
                        break;
                    case 2:
                        game.addObject(LRF.createDamageDelear(), x, y);
                        game.print();
                        break;
                    case 3:
                        game.addObject(SMF.createLotHealth(), x, y);
                        game.print();
                        break;
                    case 4:
                        game.addObject(SMF.createDamageDelear(), x, y);
                        game.print();
                        break;
                    case 5:
                        game.addObject(RF.createLotHealth(), x, y);
                        game.print();
                        break;
                    case 6:
                        game.addObject(RF.createDamageDelear(), x, y);
                        game.print();
                        break;
                }
                break;
            }
            case 'd':
            {
                int x, y;
                cout << "Введите координаты юнита которого хотите удалить {x,y}\n";
                game.print();
                cin >> x >> y;
                game.deleteObject(x, y);
                game.print();
                break;
            }
            case 'm':
            {
                int x1, y1, x2, y2;
                cout << "Введите координаты юнита которого хотите передвинуть {x,y} и координаты, куда хотите его поставить {x,y}\n";
                game.print();
                cin >> x1 >> y1 >> x2 >> y2;
                game.moveObject(Point(x1, y1), Point(x2, y2));
                game.print();
                break;
            }
            case 'e':
                break;
            default:
                cout << "Такой команды нет\n";

        }


    }while(command != 'e');


    return 0;
}