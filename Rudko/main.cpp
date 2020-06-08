#include <iostream>
#include "unit.h"
#include "gfield.h"
#include "base.h"
#include "facade.h"

using namespace std;

int main(){
    Facade* facade = new Facade;
    string answer;
    cout << "\t\tСправка\n"
            ">>>Управление игроками\n"
            " Для управления введите координаты игрока и наравление движения.\n"
            "\tL - шаг влево\n"
            "\tR - шаг вправо\n"
            "\tU - шаг вперед\n"
            "\tD - шаг назад\n"
            "\t|-------|\n"
            "\t|-- U --|\n"
            "\t|-L @ R-|\n"
            "\t|-- D --|\n"
            "\t|-------|\n"
            " Для просмотра состоянийя базы введите base.\n"
            " Для добавления война на поле введите add координты и имя война.\n"
            " Для сохранения состояния программы в файл введиде save.\n"
            " Для считывания инфармации из файла введите display.\n"<< endl;
    cout << "Желаете начать игру?" << endl;
    cin >> answer;
    if(answer == "Да" || answer == "да" || answer == "la"){
        facade->NewGame();
        cout << "Чтобы начать введите play" << endl;
        cout << "Для выхода введите exit" << endl;
        cin >> answer;
        if(answer == "play")
            facade->Play();
        else {
            cout << "Всего хорошего!" << endl;
        }
    }
    else {
        cout << "Всего хорошего!" << endl;
    }
    return 0;
}

