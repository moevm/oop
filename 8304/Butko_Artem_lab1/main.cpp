#include <iostream>
#include <locale>
#include "GameField.h"
#include "Units.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    size_t height, width;
    char id;
    int x, y, x1, y1;

    char choice = 'A';
    std::cout << "MEDIEVAL JAPAN (ver. 0.1)" << std::endl;
    std::cout << "Введите размеры игрового поля:" << std::endl;
    std::cout << " Высота: " << std::endl;
    std::cin >> height;
    std::cout << " Ширина: " << std::endl;
    std::cin >> width;
    if (height < 1 || width < 1)
        return 1;
    GameField Field(height, width);

    std::cout << "Что Вы хотите сделать?" << std::endl;
    while(choice != '0')
    {
        std::cout << "  1) Поставить юнита" << std::endl;
        std::cout << "  2) Переместить юнита" << std::endl;
        std::cout << "  3) Удалить юнита" << std::endl;
        std::cout << "  4) Вывести поле" << std::endl;
        std::cout << "  0) Выйти" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
            case '1':
                std::cout << "  Введите индификатор юнита (N, S, G, C, s, M):" << std::endl;
                std::cin >> id;
                std::cout << "  Введите позицию юнита:" << std::endl;
                std::cout << "  x = ";
                std::cin >> x;
                std::cout << "  y = ";
                std::cin >> y;
                Field.addUnit(id, x - 1, y - 1);
                break;
            case '2':
                std::cout << "  Введите начальную позицию юнита:" << std::endl;
                std::cout << "  x = ";
                std::cin >> x1;
                std::cout << "  y = ";
                std::cin >> y1;
                std::cout << "  Введите куда перемесиить юнита:" << std::endl;
                std::cout << "  x = ";
                std::cin >> x;
                std::cout << "  y = ";
                std::cin >> y;
                Field.moveUnit(x1 - 1, y1 - 1, x - 1, y - 1);
                break;
            case '3':
                std::cout << "  Введите позицию юнита:" << std::endl;
                std::cout << "  x = ";
                std::cin >> x;
                std::cout << "  y = ";
                std::cin >> y;
                Field.deleteUnit(x - 1, y - 1);
                break;
            case '4':
                std::cout << std::endl;
                Field.showField();
                std::cout << std::endl;
                break;
            default:
                break;
        }
    }
}
