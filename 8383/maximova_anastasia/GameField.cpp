#include "GameField.h"
#include <iostream>
#include "AbstractFactory.h"
#include "GameField.h"
using namespace std;

GameField::GameField()				//конструктор "по умолчанию"
{
	height = 10;
	width = 10;
	step = 1;
	maxUnits = 6;
}

GameField::GameField(int height, int width) : GameField() //делегирующие конструкторы
{
	if (height <= 3 || width <= 3) {
		std::cout << "Ошибка: неверно указан размер поля!\nСоздано поле стандартного размера.\n";
	}
	else {
		this->height = height;
		this->width = width;
		step = 1;
		if (width >= height && (int)((width / 2) * (0.2)) > step && height >= (width / 2)) {
			step = (int)((width / 2) * (0.2));
		}
		maxUnits = 6 * step;
	}
	createField();
}

GameField::GameField(const GameField& other) {
	this->height = other.height;
	this->width = other.width;
	this->step = other.step;

	this->field = new Object**[other.height];
	for (int i = 0; i < other.height; i++) {
		this->field[i] = new Object * [other.width];
		for (int j = 0; j < other.width; j++) {
			this->field[i][j] = other.field[i][j];
		}
	}
}

GameField::GameField(GameField&& other):field(nullptr), height(NULL), width(NULL), step(NULL) {

	swap(field, other.field);
	swap(height, other.height);
	swap(width, other.width);
	swap(step, other.step);

}

void GameField::createField() {
	field = new Object * *[height];
	for (int i = 0; i < height; i++) {
		field[i] = new Object * [width];
		for (int j = 0; j < width; j++) {
			field[i][j] = nullptr;
		}
	}
}

Unit* GameField::createUnit(char type, int view) {
	ConcreteFactoryMonster monster;
	ConcreteFactoryHero hero;
	ConcreteFactoryPeople people;
	switch (type) {
	case 'm':
		if (view == 1 || view == 2) return monster.createUnit(view);
		break;
	case 'h':
		if (view == 3 || view == 4)  return hero.createUnit(view);
		break;
	case 'p':
		if (view == 5 || view == 6)  return people.createUnit(view);
		break;
	default:
		cout << "Ошибка: " << view << " <-- такого вида не существует!\n"; //доработать момент
		break;
	}
}

int GameField::addUnit(Object* unit, int x, int y) {
	unit->setXY(x, y);
	if (field[x][y] == nullptr) {
		field[x][y] = unit;
		return 0;
	}
	else {
		cout << "Позиция занята!\n";
		return 1;
	}
}

int GameField::movingUnit(int x, int y, char course, int steps) { //'r' - право 'l' - лево 'd' - вниз 'u' - вверх
	switch (field[x][y]->getView()) {
	case 1:
		if (steps > 3) {
			cout << "Максимальное кол-во шагов для данного персонажа = 3.\n";
			return 1;
		}
		break;
	case 2:
		if (steps > 2) {
			cout << "Максимальное кол-во шагов для данного персонажа = 2.\n";
			return 1;
		}
		break;
	case 3:
		if (steps > 1) {
			cout << "Максимальное кол-во шагов для данного персонажа = 1.\n";
			return 1;
		}
		break;
	case 4:
		if (steps > 2) {
			cout << "Максимальное кол-во шагов для данного персонажа = 2.\n";
			return 1;
		}
		break;
	}
	steps *= step;

	if (course == 'r') {
		if (field[x][y + steps] == nullptr && (y + steps) < width) { //пока можно перемещаться только на свободные позиции
			swap(field[x][y], field[x][y + steps]);					 //можно перемещаться на поле противника
		}
	}
	else if (course == 'l') {
		if (field[x][y - steps] == nullptr && (y - steps) > -1) {
			swap(field[x][y], field[x][y - steps]);
		}
	}
	else if (course == 'd') {
		if (field[x + steps][y] == nullptr && (x + steps) < height) {
			swap(field[x][y], field[x + steps][y]);
		}
	}
	else if (course == 'u') {
		if (field[x - steps][y] == nullptr && (x - steps) > -1) {
			swap(field[x][y], field[x - steps][y]);
		}
	}
	else if (course == 'a') {
		if (field[x - steps][y + steps] == nullptr && (y + steps) < width && (x - steps) > -1) {
			swap(field[x][y], field[x - steps][y + steps]);
		}
	}
	else if (course == 'b') {
		if (field[x - steps][y - steps] == nullptr && (y - steps) > -1 && (x - steps) > -1) {
			swap(field[x][y], field[x - steps][y - steps]);
		}
	}
	else if (course == 'c') {
		if (field[x + steps][y + steps] == nullptr && (y + steps) < width && (x + steps) < height) {
			swap(field[x][y], field[x + steps][y + steps]);
		}
	}
	else if (course == 'f') {
		if (field[x + steps][y - steps] == nullptr && (y - steps) > -1 && (x + steps) < height) {
			swap(field[x][y], field[x + steps][y - steps]);
		}
	}
	else {
		cout << "Невозможно выполнить перемещение на заданную позицию!\n";
		return 1;
	}
	return 0;
}

int GameField::deleteUnit(int x, int y) {
	if (field[x][y] != nullptr) {
		delete field[x][y];
		field[x][y] = nullptr;
		return 0;
	}
	else {
		cout << "На позиции нет юнита для удаления!\n";
		return 1;
	}
}

void GameField::printCurField() {
	int k = 0;
	system("cls");
	system("color 5F");
	cout << "  ";
	for (int i = 0; i < width; i++) {
		if (i < 10) cout << "  " << i << " ";
		else if (i == 10) cout << "  " << i << "  ";
		else cout << i << "  ";
	}
	cout << "\n" << "  -";
	for (int i = 0; i < width; i++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		if (k <= 9) cout << k++ << " ";
		else cout << k++;
		for (int j = 0; j < width; j++) {
			if (field[i][j] == nullptr) {
				cout << "|   ";
			}
			if (field[i][j] != nullptr) {
				cout << "| " << field[i][j]->getName() << " ";
			}
			if (j == width - 1) cout << "|";
		}

		cout << "\n" << "  -";
		for (int i = 0; i < width; i++) {
			cout << "----";
		}
		cout << endl;
	}
}

int GameField::getHeight() {
	return height;
}

int GameField::getWidth() {
	return width;
}

int GameField::getStep() {
	return step;
}

int GameField::getMaxUnits() {
	return maxUnits;
}

GameField::~GameField() {
	for (int i = 0; i < height; i++) {
		delete[] field[i];
	}
	delete[] field;
}
