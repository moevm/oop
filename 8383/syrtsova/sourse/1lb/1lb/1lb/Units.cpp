#include "pch.h"
#include "Units.h"
#include <iostream>
#include <windows.h>
#include "Map.h"
#include "Attribute.h"

Units::Units(char N, const int &h, const int &ar, const int &at, const int &r) 
{
	/*Name name(N);
	Health health(h);
	Armor armor(ar);
	Attack attack(at);
	Radius radius(r);*/

	name.setAtrib(N);
	health.setAtrib(h);
	armor.setAtrib(ar);
	attack.setAtrib(at);
	radius.setAtrib(r);
	object = name.returnName();
	link = this;
}

Units* Units::getLink(Map* field)
{
	Units *un;
	for (int i = 1; i <= field->iterator->count; ++i)
	{
		un = field->iterator->mas[i]->getUnit();
		if (un->XY.x == this->_xy.x && un->XY.y == this->_xy.y)
		{
			return un;
		}
	}
}


void Units::printStats()
{
	cout << endl << "Обозначение на карте: " << name.returnName() 
		 << endl << "Количество HP: " << health.returnHealth() << '\t' << '\t'
		 <<			"Величина брони: " << armor.returnArmor() 
		 << endl << "Сила атаки: " << attack.returnAttack() << '\t' << '\t' << '\t'
		 <<			"Радиус атаки: " << radius.returnRadius() << endl;
}


bool Units::rules(Map *field, int x, int y)
{
	if ((*field).isUnit(x, y)) return false;
	int type = (*field).isLandscape(x, y);
	if (((type != 2)  && (type != 0)) || (type == 4)) return false;
	if ((*field).isBase(x, y)) return false;
	return true;
}


void Units::managment(Map *field)
{
	int select;
	while (true)
	{
		cout << endl << "1. Перемещение" << endl << "2. Использование способности" << endl << "3. Оставить юнита в покое" << endl;
		cout << "Выбор действия: "; cin >> select;
		switch (select)
		{
		case 1: movie(field); break;
		case 2: useSkill(field); break;
		case 3: return;
		default:
			cout << endl << "Некорректный ввод";
			break;
		}
	}
}

void Units::useSkill(Map *field)
{
	printStats();
	this->showSkills();
	while (true)
	{
		if (GetAsyncKeyState(1))
		{
			this->selectSkill(1, field);
		}
		if (GetAsyncKeyState(2))
		{
			this->selectSkill(2, field);
		}
		if (GetAsyncKeyState(3))
		{
			this->selectSkill(1, field);
		}
		if (GetAsyncKeyState(4))
		{
			this->selectSkill(1, field);
		}

		Sleep(10);
		if (GetAsyncKeyState(VK_SPACE))
		{
			cin.clear();
			return;
		}
	}
}


void Units::selectLine ()
{
	cout << endl << "Выбор направления: "
		<< endl << "1. Вверхний левая клетка: " << '\t'  
		<< "2. Вверхняя клетка: " << '\t' << '\t'
		<< "3. Вверхняя правая клетка: "
		<< endl << "4. левая клетка: " << '\t' << '\t' 
		<< "5. Центральная клетка: " << '\t' << '\t'
		<< "6. Парвая клетка: "
		<< endl << "7. Нижняя левая клетка: " << '\t' 
		<< "8. Нижняя правая клетка: " << '\t'
		<< "9. Нижняя левая клетка: ";
	int chois;
	switch (chois)
	{
	case 1:
	{
		_xy.x = XY.x - 1;
		_xy.x = XY.y - 1;
	}break;
	case 2:
	{
		_xy.x = XY.x;
		_xy.x = XY.y - 1;
	}break;
	case 3:
	{
		_xy.x = XY.x + 1;
		_xy.x = XY.y - 1;
	}break;
	case 4:
	{
		_xy.x = XY.x - 1;
		_xy.x = XY.y;
	}break;
	case 5:
	{
		_xy.x = XY.x;
		_xy.x = XY.y;
	}break;
	case 6:
	{
		_xy.x = XY.x + 1;
		_xy.x = XY.y;
	}break;
	case 7:
	{
		_xy.x = XY.x - 1;
		_xy.x = XY.y + 1;
	}break;
	case 8:
	{
		_xy.x = XY.x;
		_xy.x = XY.y + 1;
	}break;
	case 9:
	{
		_xy.x = XY.x + 1;
		_xy.x = XY.y + 1;
	}break;

	default: cout << endl << "Некорректный ввод!";
		break;
	}
}


void Units::movie(Map *field)
{
	//printStats();
	this->showSkills();
	while (true)
	{
		Sleep(10);
		if ((GetAsyncKeyState(VK_UP) && (rules(field, XY.x, (XY.y-1)))))
		{
			if (!field->isNeutral((XY.x), (XY.y - 1)))
			{
				(*field).remove_from_map(this->XY.x, this->XY.y);
				this->XY.y = this->XY.y - 1;
				system("cls");
				(*field).add_on_map(this->XY.x, this->XY.y, this);
				(*field).print_map();
				printStats();
			//	this->showSkills();
			}
			else
			{
				cout <<endl<< "Невозможно перемещение. Поле сверху занято!";
			}
		}
		if ((GetAsyncKeyState(VK_DOWN) && (rules(field, XY.x, (XY.y + 1)))))
		{
			if (!field->isNeutral((XY.x), (XY.y + 1)))
			{
				(*field).remove_from_map(this->XY.x, this->XY.y);
				this->XY.y = this->XY.y + 1;
				system("cls");
				(*field).add_on_map(this->XY.x, this->XY.y, this);
				(*field).print_map();
				printStats();
			//	this->showSkills();
			}
			else
			{
				cout << endl << "Невозможно перемещение. Поле снизу занято!";
			}
		}
		if ((GetAsyncKeyState(VK_LEFT) && (rules(field, (XY.x - 1), XY.y))))
		{
			if (!field->isNeutral((XY.x-1), XY.y))
			{
				(*field).remove_from_map(this->XY.x, this->XY.y);
				this->XY.x = this->XY.x - 1;
				system("cls");
				(*field).add_on_map(this->XY.x, this->XY.y, this);
				(*field).print_map();
				printStats();
			//	this->showSkills();
			}
			else
			{
				cout << endl << "Невозможно перемещение. Поле слева занято!";
			}

		}
		if ((GetAsyncKeyState(VK_RIGHT) && (rules(field, (XY.x + 1), XY.y))))
		{
			if (!field->isNeutral((XY.x + 1), XY.y))
			{
				(*field).remove_from_map(this->XY.x, this->XY.y);
				this->XY.x = this->XY.x + 1;
				system("cls");
				(*field).add_on_map(this->XY.x, this->XY.y, this);
				(*field).print_map();
				printStats();
			//	this->showSkills();
			}
			else
			{
				cout << endl << "Невозможно перемещение. Поле справа занято!";
			}
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			cin.clear();
			return;
		}
	}
}


void Units::operator+ (Units* unit) {
	// Смотрит и ничего не делает
}



void Units::selected(Map *field)
{
	if (move(field))
		return;
}



Units::~Units()
{
}


