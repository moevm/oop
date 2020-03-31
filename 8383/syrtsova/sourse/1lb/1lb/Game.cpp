#include "pch.h"
#include "Game.h"
#include "Units.h"
#include "Warlock.h"
#include "Archer.h"
#include "Warrior.h"
#include <string>
#include <iomanip>
#include "Map.h"
#include <Windows.h>
#include "Bases.h"
#include "Landscape.h"
#include "Neutral.h"

using namespace std;

Game::Game()
{
	choice_map();
	Map *field = new Map(x_max, y_max);
	//field = makeLandscape(x_max, y_max, field);
	Grass grass(x_max, y_max);
	Water water(x_max, y_max);
	Stones stones(x_max, y_max);
	grass.generation(field);
	stones.generation(field);
	water.generation(field);
	Bases *base = new Bases('B', 1000, 100);
	(*field).add_on_map(base->X, base->Y, base);

	Pab *pab = new Pab(x_max, y_max);
	(*field).add_on_map(pab->getX(), pab->getY(), pab);

	Tablet *tablet = new Tablet(x_max, y_max);
	(*field).add_on_map(tablet->getX(), tablet->getY(), tablet);

	Cave *cave = new Cave(x_max, y_max);
	(*field).add_on_map(cave->getX(), cave->getY(), cave);

	Ruin *ruin = new Ruin(x_max, y_max);
	(*field).add_on_map(ruin->getX(), ruin->getY(), ruin);
	while (true)
	{
		system("cls");
		(*field).print_map();
		int product = select(base, field);
		base->production(product, field);
	}
}

int Game::select(Bases* base, Map* field)
{
	cout << endl
		<< "Ресурсы на лучников: " << base->list.count_archer[0] << endl
		<< "Ресурсы на волшебников: " << base->list.count_warlock[0] << endl
		<< "Ресурсы на воинов: " << base->list.count_warrior[0] << endl
		<< "Численность войска: " << base->list.count_unit[0] + base->list.count_unit[1] + base->list.count_unit[2] << " единиц" << endl
		<< "Из них: " << endl
		<< "Лучники: " << base->list.count_unit[0] << " :: " << "Лук: " << base->list.count_archer[1] << " -_- " << "Арбалет: " << base->list.count_archer[2] << endl
		<< "Волшебники: " << base->list.count_unit[1] << " :: " << "Целитель: " << base->list.count_warlock[1] << " -_- " << "Маг: " << base->list.count_warlock[2] << endl
		<< "Воины: " << base->list.count_unit[1] << " :: " << "Мечники: " << base->list.count_warrior[1] << " -_- " << "Рыцари: " << base->list.count_warrior[2] << endl;
	string select[6] = { "{M} - Magician", "{H} - Healer", "{L} - Archer", "{A} - Arbalester", "{F} - Swordsman", "{G} - Spear" };
	int i;
	cout << "1 - {M} - Magician" << endl << "2 - {H} - Healer" << endl << "3 - {L} - Archer" << endl << "4 - {A} - Arbalester" << endl << "5 - {F} - Swordsman" << endl << "6 - {G} - Spear" << endl;
	cin >> i;
	cin.clear();
	while (cin.get() != '\n');
	return i;
}

void Game::choice_map()
{
	char choice = ' ';
	cout << "Выбор игрового поля:\n1-Поле стандартного размера 20х20\n2-Произвольное поле\n0-Выход\n";
	cin >> choice;
	cin.clear();
	while (cin.get() != '\n');
	switch (choice) {
	case '1':
		x_max = y_max = 20;
		break;
	case '2':
		cout << "Введите размер поля: ";
		cout << "x_max: ";
		cin >> x_max;
		cout << "y_max: ";
		cin >> y_max;
		break;
	case '0':
		exit;
	default:
		cout << "Некорректный ввод. Попробуйте еще раз.\nВыбор игрового поля:\n1-Поле стандартного размера 20х20\n2-Введите координаты поля: \n0-Выход\n";
		cin >> choice;
	}
}

/*Map* Game::makeLandscape(int x_max, int y_max, Map* field)
{
	Grass grass(x_max, y_max);
	Water water(x_max, y_max);
	Stones stones(x_max, y_max);
	grass.generation(field);
	stones.generation(field);
	water.generation(field);
	return field;
}
*/
