#include <iostream>
#include "unit.h"
#include "gfield.h"
#include "base.h"
#include "ruls.h"
#include "facade.h"

using namespace std;

int main(){
    Facade* facade = new Facade;
    Ruls* ruls = new Ruls;
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
        int number;
        cout << "Выберите вариант игры, 1 или 2" << endl;
        cin >> number;
        while(1){
            if(number != 1 && number != 2){
                cout << "Выберите 1 или 2" << endl;
                cin >> number;
            }
            else {
                break;
            }
        }
        //facade->NewGame();
        cout << "Чтобы начать введите play" << endl;
        cout << "Для выхода введите exit" << endl;
        cin >> answer;
        if(answer == "play"){
            if(number == 1)
                ruls->Ruls1();
            if(number == 2){
                ruls->Ruls2();
            }
            //facade->Play();
        }
        else {
            cout << "Всего хорошего!" << endl;
        }
    }
    else {
        cout << "Всего хорошего!" << endl;
    }
    return 0;
}

