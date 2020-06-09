#include <iostream>
#include "unit.h"
#include "gfield.h"
#include "base.h"

using namespace std;

int main(){
    cout << "Введите размеры поля" << endl;
    int a, b, c, d;
    cin >> a >> b;
    GField* field = new GField(a, b);
    field->printField();
    cout << "Введите координаты базы" << endl;
    cin >> a >> b;
    Base* base = new Base(a-1, b-1, field);
    field->printField();
    cout << "Начальное число юнитов на поле" << endl;
    cin >> a;
    cout << "Имена юнитов:\n"
            "\t\t scorpio\n"
            "\t\t mammoth\n"
            "\t\t frog\n"
            "\t\t kangaroo\n"
            "\t\t swallow\n"
            "\t\t hawk" << endl;
    for(int i = 0; i < a; i++){
        int x,y;
        string name;
        cout << "Введите имя юнита и его координаты" << endl;
        cin >> name >> x >> y;
        base->CreatureUnit(x-1, y-1, name);
    }
    field->printField();

    return 0;
}

