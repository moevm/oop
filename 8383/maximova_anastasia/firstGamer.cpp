#include "FirstGamer.h"
#include <ctime>
FirstGamer::FirstGamer() {
	name = '0';
	team = '0';
	width = 0;
	height = 0;
	exit = 0;
	x = 0;
	y = 0;
	answer = '0';
}

void FirstGamer::caseName() {
	cout << "Игрок №1, введите ваше имя (допустимая длина 20 символов).\n";
	cin >> name;
	cout << name << ", выберите за какую команду вы будете играть.\n";
	cout << "Если вы хотите играть за монстров введите \"m\".\n";
	cout << "Если вы хотите играть за героев введите \"h\".\n";
	if (!choice2()) team = 'h';
	else team = 'm';
	caseField();
}

bool FirstGamer::choice2() {
	do {
		exit = 0;
		cin >> answer;
		answer = tolower(answer);

		switch (answer) {
		case 'm':
			return 1;
			break;

		case 'h':
			return 0;
			break;

		default:
			cout << "Ошибка: введен неккоректный символ. Попробуйте еще раз.\n";
			exit = 1;
		}
	} while (exit == 1);
}

void FirstGamer::caseField() {
	system("cls");
	system("color 79");
	cout << endl << "Перед началом игры введите высоту и ширину игрового поля.\n";
	cin >> height >> width;
	field = new GameField(height, width);
	cout << "Построено поле высоты: " << field->getHeight() << " и ширины: " << field->getWidth() << ".\n";
	addPeople();
}
void FirstGamer::addPeople() {
	cout << "Добавление персонажей по умолчанию\n";
	int view;
	int i = field->getMaxUnits() * 2;
	srand(time(NULL));
	while (i != 0) {
		view = rand() % 2 + 5; //5 или 6
		x = rand() % field->getHeight();
		y = rand() % field->getWidth();
		if (field->addUnit(field->createUnit('p', view), x, y)) {
			i++; //Персонаж не создан!
		}
		else {
			if (view == 5) cout << "Создан охотник\n";
			else cout << "Создан человек\n";
		}
		i--;
	}
	field->printCurField();
	caseAddCommand();
}
void FirstGamer::caseAddCommand() {
	int command;
	//system("cls");
	system("color 1F");
	cout << endl << name << ", вам необходимо добавить " << field->getMaxUnits() << " персонажей на поле. \n";
	cout << "Для этого вам необходимо ввести три числа:\n";
	cout << "Первое: номер команды добавления\n";
	if (team == 'm') {
		cout << "ВАМПИР: команда для добавления \"1\".\n";
		cout << "ОБОРОТЕНЬ: команда для добавления \"2\".\n";
	}
	else {
		cout << "ЦЕЛИТЕЛЬ: команда для добавления \"3\".\n";
		cout << "МАГ: команда для добавления \"4\".\n";
	}
	cout << "Два числа - координаты расположения героя (x; y).\n";
	if (team == 'm') cout << "Ваше поле левое.\n";
	else cout << "Ваше поле правое\n";

	cin >> command >> x >> y;
	int i = field->getMaxUnits();
	while (i != 0) {
		while (!caseError(command)) {
			cout << "Введите снова:\n";
			cin >> command >> x >> y;
		}

		switch (command) {
		case 1:
			if (!field->addUnit(field->createUnit('m', 1), x, y)) {
				cout << "Создан Вампир\n";
			}
			else {
				cout << "Персонаж не создан!\n";
				i++;
			}
			break;

		case 2:
			if (!field->addUnit(field->createUnit('m', 2), x, y)) {
				cout << "Создан Оборотень\n";
			}
			else {
				cout << "Персонаж не создан!\n";
				i++;
			}
			break;

		case 3:
			if (!field->addUnit(field->createUnit('h', 3), x, y)) {
				cout << "Создан Целитель\n";
			}
			else {
				cout << "Персонаж не создан!\n";
				i++;
			}
			break;

		case 4:
			if (!field->addUnit(field->createUnit('h', 4), x, y)) {
				cout << "Создан Маг\n";
			}
			else {
				cout << "Персонаж не создан!\n";
				i++;
			}
			break;
		}
		i--;
		if (i) cin >> command >> x >> y;
	}
	field->printCurField();
}

bool FirstGamer::caseError(int command) {

	if (team == 'm') {
		if (command < 1 || command > 2) {
			cout << "Ошибка ведена неверная команда!\n";
			return 0;
		}
		if (y > (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь разместить юнитов на поле соперника!\n";
			return 0;
		}
	}
	else if (team == 'h') {
		if (command < 3 || command > 4) {
			cout << "Ошибка ведена неверная команда!\n";
			return 0;
		}
		if (y < (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь разместить юнитов на поле соперника!\n";
			return 0;
		}
	}
	if (x < 0 || y < 0) {
		cout << "Ошибка: введены отрицательные координаты!\n";
		return 0;
	}
	else if (x > field->getWidth() - 1 || y > field->getHeight() - 1) {
		cout << "Ошибка: координаты выходят из области поля!\n";
		return 0;
	}
	return 1;
}

void FirstGamer::caseDeleteUnit() { //возможно и не нужна, но пока для примера удаления
	exit = 1;
	while (exit) {
		cout << "Введите координаты юнита, которого хотите удалить.\n";
		cin >> x >> y;
		while (!caseError() || field->deleteUnit(x, y)) {
			cout << "Введите снова:\n";
			cin >> x >> y;
		}
		cout << "Юнит удален!\n";
		field->printCurField();
		cout << "Введите 0, если хотите прекратить удаление.\n";
		cout << "Введите 1, если хотите продолжить удаление.\n";
		cin >> exit;
	}
}

bool FirstGamer::caseError() {

	if (team == 'm') {
		if (y > (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь удалить юнита соперника!\n";
			return 0;
		}
	}
	else if (team == 'h') {
		if (y < (field->getWidth() - 1) / 2) {
			cout << "Ошибка: вы пытаетесь удалить юнита соперника!\n";
			return 0;
		}
	}
	if (x < 0 || y < 0) {
		cout << "Ошибка: введены отрицательные координаты!\n";
		return 0;
	}
	else if (x > field->getWidth() - 1 || y > field->getHeight() - 1) {
		cout << "Ошибка: координаты выходят из области поля!\n";
		return 0;
	}
	return 1;
}

void FirstGamer::caseMovUnit() {
	int steps;
	char a;
	cout << "Для того, чтобы переместить юнита на другую позицию, необходимо ввести:\n";
	cout << "Текущие координаты расположения юнита (x, y);\n";
	cout << "Количество шагов (из допустимого).\n";
	cout << "Длина одного шага равна " << field->getStep() << endl;
	cout << "Допустим количество шагов:\n Вампир : от 1 до 3.\n";
	cout << "Оборотень: от 1 до 2.\n Целитель: 1 шаг.\n Маг: от 1 до 2 шагов.\n";
	exit = 1;
	while (exit) { 
	cout << "Направление движения юнитов:\n"; //пока все юниты ходят по всем направлениям
	cout << "\"l\" - влево; \"r\" - вправо; \"u\" - вверх; \"d\" - вниз\n";
	cout << "\"a\" - диагональ вверх-направо; \"b\" - диагональ вверх-налево;\n";
	cout << "\"c\" - диагональ вниз-направо; \"f\" - диагональ вниз-налево.\n";
	cin >> x >> y >> a >> steps;
	while (caseError(a, steps) || field->movingUnit(x, y, a, steps)) {
		cout << "Введите снова\n";
		cin >> x >> y >> a >> steps;
	}
	field->printCurField();
	cout << "Введите 0, если хотите прекратить перемещение.\n";
	cout << "Введите 1, если хотите продолжить перемещение.\n";
	cin >> exit;
	}
}

bool FirstGamer::caseError(char a, int steps) {
	if (x < 0 || y < 0 || x > field->getHeight() - 1 || y > field->getWidth() - 1) {
		cout << "Ошибка: данной позиции не существует!\n";
		return 1;
	}
	if (a == 'r' || a == 'l' || a == 'u' || a == 'd' || a == 'a' || a == 'b' || a == 'c' || a == 'f') {
	}
	else {
		cout << "Ошибка: команды не существует!\n";
		return 1;
	}
	if (steps < 0 || steps > 3) {
		cout << "Ошибка: недопустимое количество шагов!\n";
		return 1;
	}
	return 0;
}

void FirstGamer::saveField() {
	GameField copy(*field);
	copy.printCurField();
	cout << "Игровое поле сохранено.\n";
}

string FirstGamer::getName() {
	return name;
}

char FirstGamer::getTeam() {
	return team;
} 