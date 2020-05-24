#include "GameSingleton.h"

void GameSingleton::startGame() {
	int typeOfGame = 0;
	int size = 0;
	int numOfMen = 0;
	int numOfElfs = 0;
	int numOfOrcs = 0;
	bool isNewGame = false;
	do {
		system("cls");
		isNewGame = false;

		cout << "Какой тип игры вам интересен?\n1 - игра без баз\n2 - игра с базами\n";
		cin >> typeOfGame;
		if (cin.fail() || (typeOfGame != 1 && typeOfGame != 2)) {
			cout << "Ошибка в считывании типа игры\n";
			return;
		}

		cout << "Вам предложено ввести количество орков, эльфов и людей.\n";
		cout << "Так как в игре 2 игрока: один за орков, а другой за людей и эльфов, то\n";
		cout << "количество людей и эльфов должно соответствовать количеству орков.\n";
		if (typeOfGame == 2)
			cout << "(Первый игрок за людей и эльфов, второй - за орков. 4 < Кол-во орков < 10)\n\n";
		else if (typeOfGame == 1)
			cout << "(Первый игрок за людей и эльфов, второй - за орков. 2 < Кол-во орков < 10)\n\n";

		cout << "Введите количество людей:\n";
		cin >> numOfMen;
		if (cin.fail() || numOfMen < 0) {
			cout << "Ошибка в считывании количества людей\n";
			return;
		}

		cout << "Введите количество эльфов:\n";
		cin >> numOfElfs;
		if (cin.fail() || numOfElfs < 0) {
			cout << "Ошибка в считывании количества эльфов\n";
			return;
		}

		numOfOrcs = numOfElfs + numOfMen;

		if (typeOfGame == 2 && (numOfOrcs <= 4 || numOfOrcs >= 10)) {
			cout << "Ошибка в количестве юнитов\n";
			return;
		}
		else if (typeOfGame == 1 && (numOfOrcs <= 2 || numOfOrcs >= 10)) {
			cout << "Ошибка в количестве юнитов\n";
			return;
		}

		cout << "Создается поле размерностью GxG. Введите G:\n";
		cin >> size;

		if (cin.fail()) {
			cout << "Ошибка в считывании размерности поля\n";
			return;
		}
		if (typeOfGame == 2) {
			while (size <= numOfOrcs + 3) {
				cout << "G введено неверно! Оно должно быть больше " << numOfOrcs + 3 << endl;
				cin >> size;
			}
		}
		else if (typeOfGame == 1) {
			while (size <= numOfOrcs + 1) {
				cout << "G введено неверно! Оно должно быть больше " << numOfOrcs + 1<< endl;
				cin >> size;
			}
		}

		if (typeOfGame == 1) {
			RuleWithout* rule1 = new RuleWithout();
			gameWithout = new Game<RuleWithout>(numOfOrcs, numOfMen, numOfElfs, size, *rule1);
			delete gameWithout;
		}
		else if (typeOfGame == 2) {
			RuleWith* rule2 = new RuleWith();
			gameWith = new Game<RuleWith>(numOfOrcs, numOfMen, numOfElfs, size, *rule2);
			delete gameWith;
		}

		cout << "Начать новую игру?\n1 - да\n2 - нет\n";
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