#include "pch.h"
#include "Bases.h"
#include "ctime"
#include "Map.h"
#include <iostream>
#include <conio.h>

enum allClasses
{
	magician = 1,
	healer, 
	archer, 
	arbalester, 
	swordsman, 
	spear
};

Bases::Bases(char N, int health, int res) : name(N), health(health), resources(res) 
{ 
	object = name;
	X = 1;
	Y = 1;
	initialization(res);
	XY.x = X + 1;
	XY.y = Y + 1;
	ester = 100;
}

int rand(int &res)
{
	srand(time(0));
	int pers = int(res*0.1) + rand() % int(res - res*0.1);
	if (pers == 0 && res >= 10)
		pers += 10;
	if (pers > res*0.5)
		pers -= pers * 0.2;
	res -= pers;
	return pers;
}

void Bases::initialization(int resources)
{
	int res = resources;
	list.count_warrior[0] = rand(res);
	list.count_archer[0] = rand(res);
	list.count_warlock[0] = rand(res);
}

Swordsman* Bases::createSwordsman(Map *field) {
	Swordsman *sword = new Swordsman(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, sword);
	field->iterator->mas[this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0]]->setUnit(sword);
	system("cls");
	(*field).print_map();
	sword->managment(field);
	return sword;
}
Spear* Bases::createSpear(Map *field) {
	Spear *sp = new Spear(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, sp);
	field->iterator->mas[this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0]]->setUnit(sp);
	system("cls");
	(*field).print_map();
	sp->managment(field);
	return sp;
}

Magician* Bases::createMagician(Map *field) {
	Magician *mag = new Magician(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, mag);
	field->iterator->mas[this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0]]->setUnit(mag);
	system("cls");
	(*field).print_map();
	mag->managment(field);
	return mag;
}


Healer* Bases::createHealer(Map *field) {
	Healer *heal = new Healer(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, heal);
	field->iterator->mas[this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0]]->setUnit(heal);
	system("cls");
	(*field).print_map();
	heal->managment(field);
	return heal;
}
Archer* Bases::createArcher(Map *field) {
	Archer *arh = new Archer(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, arh);
	field->iterator->mas[this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0]]->setUnit(arh);
	system("cls");
	(*field).print_map();
	arh->managment(field);
	return arh;
}
Arbalester* Bases::createArbalester(Map *field) {
	Arbalester *arb = new Arbalester(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, arb);
	field->iterator->mas[this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0]]->setUnit(arb);
	system("cls");
	(*field).print_map();
	arb->managment(field);
	return arb;
}

void Bases::production(int selsect, Map *field)
{
	if ((*field).isUnit(XY.x, XY.y))
	{
		cout << endl << "Поле занято другим юнитом!";
		cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
		_getch();
		return;
	}
	switch(selsect)
	{
	case  allClasses::arbalester:
		{
		if (cost_arbalester <= list.count_archer[0]) {
			list.count_archer[0] -= cost_arbalester;
			list.count_archer[1]++;
			list.count_unit[0]++;
			count_units++;
			field->iterator->count++;
			//создание арбалетчика
			army = army + units[allClasses::arbalester] + "_" + std::to_string(this->list.count_archer[1]) + '\t' + " ID :: " + std::to_string(this->list.count_unit[0] + this->list.count_unit[1] + this->list.count_unit[2]) + "\n";
			createArbalester(field);
		}
		else
		{
			cout << endl << "Недостаточно ресурсов для выбранного юнита!";
			cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
			_getch();
		}
	} break;
	case allClasses::archer:
	{
		if (cost_archer <= list.count_archer[0]) {
			list.count_archer[0] -= cost_archer;
			list.count_archer[2] ++;
			list.count_unit[0]++;
			count_units++;
			field->iterator->count++;
			//создание лучника
			army = army + units[allClasses::archer] + "_" + std::to_string(this->list.count_archer[2]) + '\t' + " ID :: " + std::to_string(this->list.count_unit[0] + this->list.count_unit[1] + this->list.count_unit[2]) + "\n";
			createArcher(field);
		}
		else
		{
			cout << endl << "Недостаточно ресурсов для выбранного юнита!";
			cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
			_getch();
		}
	} break;
	case allClasses::swordsman:
	{
		if (cost_swordsman <= list.count_warrior[0]) {
			list.count_warrior[0] -= cost_swordsman;
			list.count_warrior[1] ++;
			list.count_unit[1]++;
			count_units++;
			field->iterator->count++;
			//создание мечника
			army = army + units[allClasses::swordsman] + "_" + std::to_string(this->list.count_warrior[1]) + '\t' + " ID :: " + std::to_string(this->list.count_unit[0] + this->list.count_unit[1] + this->list.count_unit[2]) +  "\n";
			createSwordsman(field);
		}
		else
		{
			cout << endl << "Недостаточно ресурсов для выбранного юнита!";
			cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
			_getch();
		}
	}break;
	case allClasses::spear:
	{
		if (cost_spear <= list.count_warrior[0]) {
			list.count_warrior[0] -= cost_spear;
			list.count_warrior[2] ++;
			list.count_unit[1]++;
			count_units++;
			field->iterator->count++;
			//создание рыцаря
			army = army + units[allClasses::spear] + "_" + std::to_string(this->list.count_warrior[2]) + '\t' + " ID :: " + std::to_string(this->list.count_unit[0] + this->list.count_unit[1] + this->list.count_unit[2])  + "\n";
			createSpear(field);
		}
		else
		{
			cout << endl << "Недостаточно ресурсов для выбранного юнита!";
			cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
			_getch();
		}
	}break;
	case allClasses::healer:
	{
		if (cost_healer <= list.count_warlock[0]) {
			list.count_warlock[0] -= cost_healer;
			list.count_warlock[1] ++;
			list.count_unit[2]++;
			count_units++;
			field->iterator->count++;
			//создание хиллера
			createHealer(field);
			army = army + units[allClasses::healer] + "_" + std::to_string(this->list.count_warlock[1]) + '\t' + " ID :: " + std::to_string(this->list.count_unit[0] + this->list.count_unit[1] + this->list.count_unit[2]) + "\n";
		}
		else
		{
			cout << endl << "Недостаточно ресурсов для выбранного юнита!";
			cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
			_getch();
		}
	}break;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case allClasses::magician:
	{
		if (cost_magician <= list.count_warlock[0]) {
			list.count_warlock[0] -= cost_magician;
			list.count_warlock[2] ++;
			list.count_unit[2]++;
			count_units++;
			field->iterator->count++;
			//создание мага
			Units* unit = createMagician(field);
			army = army + units[allClasses::magician] + "_" + std::to_string(this->list.count_warlock[2]) + '\t' + " ID :: " + std::to_string(this->list.count_unit[0] + this->list.count_unit[1] + this->list.count_unit[2])  + "\n";
		}
		else
		{
			cout << endl << "Недостаточно ресурсов для выбранного юнита!";
			cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
			_getch();
		}
	}break;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

int Bases::getEster()
{
	return ester;
}
int Bases::getHealth()
{
	return health;
}

bool Bases::getShild()
{
	return shild;
}

void Bases::activateShild()
{
	ester-=30;
	shild = true;
	cout << endl << "Щит активен!";
	cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
	_getch();
}


void Bases::equipment()
{
	cout << endl << "1 - Активировать божественный щит" << endl << "2 - Поддержка флота";
}

void Bases::functional(Map* field)
{
	using namespace std;
	int chois;
	cout << endl << "1 - Состояние базы" << endl << "2 - Состояние войска" << endl << "3 - Создание юнита" << endl << "4 - Снаряжение" << endl;
	cout << "Выбор действия: ";
	cin >> chois;
	switch (chois)
	{
	case 1: { showState();  } break;
	case 2: {
		showResour();
		cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
		_getch(); 
	} break;
	case 3: 
	{
		int product = selectUnit(field);
		production(product, field);
	} break;
	case 4: { activateShild(); }
	default:
		{
			cout << "Некорректный ввод!" << endl;
		}
		break;
	}
}

void Bases::showState()
{
	using namespace std;
	cout << endl << "Состояние базы: " << getHealth() << " HP" << endl
		<< "Особый ресурс: " << getEster() << " единиц" << endl
		<< "Ресуры на юнитов: " << this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0];
	cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
	_getch();
}

int Bases::selectUnit(Map* field)
{
	using namespace std;
	showResour();
	string select[6] = { "{M} - Magician", "{H} - Healer", "{L} - Archer", "{A} - Arbalester", "{F} - Swordsman", "{G} - Spear" };
	int i;
	cout << "1 - {M} - Magician" << endl << "2 - {H} - Healer" << endl << "3 - {L} - Archer" << endl << "4 - {A} - Arbalester" << endl << "5 - {F} - Swordsman" << endl << "6 - {G} - Spear" << endl;
	cout << "Выбор типа юнита: "; cin >> i;
	cin.clear();
	while (cin.get() != '\n');
	return i;
}

void Bases::showResour()
{
	using namespace std;
	cout<<  endl
		<<  "Общие ресурсы: " << this->list.count_warrior[0] + this->list.count_warlock[0] + this->list.count_archer[0] << '\t' << '\t'
		<<  "Численность войска: " << count_units << " единиц" << endl
		<<  "Из них: " << '\t' << '\t' << '\t'
		<<  "Из них: " << endl
		<<  "Ресурсы на лучников: " << this->list.count_archer[0] << '\t' << '\t'
		<<  "Лучники: " << this->list.count_unit[0] << " :: " << "Лук: " << this->list.count_archer[1] << " -_- " << "Арбалет: " << this->list.count_archer[2] << endl
		<<  "Ресурсы на волшебников: " << this->list.count_warlock[0] << '\t'
		<<  "Волшебники: " << this->list.count_unit[1] << " :: " << "Целитель: " << this->list.count_warlock[1] << " -_- " << "Маг: " << this->list.count_warlock[2] << endl
		<<  "Ресурсы на воинов: " << this->list.count_warrior[0] << '\t' << '\t'
		<<  "Воины: " << this->list.count_unit[1] << " :: " << "Мечники: " << this->list.count_warrior[1] << " -_- " << "Рыцари: " << this->list.count_warrior[2] << endl;
}

void Bases::showAllUnits ()
{
	if (army == "")
		cout << "Войско ещё не создано!";
	else
		cout << army;
}

