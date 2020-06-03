#include "GameSingleton.h"

void GameSingleton::startGame() {
    int typeOfGame = 0;
    int size = 0;

    int mens = 0;
    int elfs = 0;
    int orcs = 0;

    bool isNewGame = false;

    do {
        isNewGame = false;

        cout << "Тип игры:\n1 - игра без возможности построения баз\n2 - игра с возможностью построения баз\n";
        cin >> typeOfGame;
        if (cin.fail() || (typeOfGame != 1 && typeOfGame != 2)) {
            cout << "Ошибка в считывании типа игры\n";
            return;
        }

        cout << "Введите количество людей и эльфов (вы играете за них, а ваш оппонент за орков)" << endl;
        if (typeOfGame == 2) cout << "4 < Люди + эльфы < 10)\n\n";
        else if (typeOfGame == 1) cout << "2 < Люди + эльфы  < 10)\n\n";

        cout << "Введите количество людей:\n";
        cin >> mens;
        if (cin.fail() || mens < 0) {
            cout << "Ошибка в считывании количества людей\n";
            return;
        }

        cout << "Введите количество эльфов:\n";
        cin >> elfs;
        if (cin.fail() || elfs < 0) {
            cout << "Ошибка в считывании количества эльфов\n";
            return;
        }

        orcs = elfs + mens;

        if (typeOfGame == 2 && (orcs <= 4 || orcs >= 10)) {
            cout << "Ошибка в количестве юнитов\n";
            return;
        } else if (typeOfGame == 1 && (orcs <= 2 || orcs >= 10)) {
            cout << "Ошибка в количестве юнитов\n";
            return;
        }

        cout << "Введите ширину поля (поле квадратное):\n";
        cin >> size;

        if (cin.fail()) {
            cout << "Ошибка в считывании размерности поля\n";
            return;
        }
        if (typeOfGame == 2) {
            while (size <= orcs + 3) {
                cout << "Неверный размер! Должно быть больше " << orcs + 3 << endl;
                cin >> size;
            }
        } else if (typeOfGame == 1) {
            while (size <= orcs + 1) {
                cout << "Неверный размер! Должно быть больше " << orcs + 1 << endl;
                cin >> size;
            }
        }

        if (typeOfGame == 1) {
            RuleWithout* rule1 = new RuleWithout();
            gameWithout = new Game<RuleWithout>(orcs, mens, elfs, size, *rule1);
            delete gameWithout;
        }
        else if (typeOfGame == 2) {
            RuleWith* rule2 = new RuleWith();
            gameWith = new Game<RuleWith>(orcs, mens, elfs, size, *rule2);
            delete gameWith;
        }

        cout << "Начать новую игру:\n1 - да\n2 - нет\n";

        int tmp = 0;
        cin >> tmp;
        if (cin.fail()) {
            cout << "Ошибка при выборе\n";
            return;
        }

        if (tmp == 1) {
            isNewGame = true;
        }

    } while (isNewGame);
}