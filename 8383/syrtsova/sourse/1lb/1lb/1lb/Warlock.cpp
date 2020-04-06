#include "pch.h"
#include "Warlock.h"
#include "Classes.h"
#include "Bases.h"
#include "Units.h"
#include "Map.h"
#include <windows.h>

Magician::Magician(int &x, int &y) : Classe_warlock('M', 50, 6, 4, 100)
{
	XY.x = x;
	XY.y = y;
	ether = 20;
}


void Magician::selectSkill(int ch, Map* field)
{
	switch (ch)
	{
	case 1: 
	{
		selectLine();
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			/*Units *un;
			for (int i = 1; i <= base->count_units; ++i)
			{
				un = field->iterator->mas[i]->getUnit;
				if (un->XY.x == this->_xy.x && un->XY.y == this->_xy.y)
				{*/
					meteorite(this->getLink(field));
					return;
				//}
			//}
		}
		else
		{
		cout << endl << "На выбранной клетке нет юнитов!" << endl << "Маг отменяет заклинание, но часть маны истрачена!";
		mana -= 1;
		}
	}
		break;
	case 2: 
	{
		selectLine();
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			storm(this->getLink(field));
			return;
		}
		else 
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Маг отменяет заклинание, но часть маны истрачена!";
			mana -= 1;
		}
	}
		break;
	case 3: 
	{
		selectLine();
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_fireball(this->getLink(field));
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Маг отменяет заклинание, но часть маны истрачена!";
			mana -= 1;
		}
	}
		break;
	case 4: ARMAGEDON(field);
		break;
	}
	if (mana <= 0)
	{
		cout << endl << "Мана иссякла!";
		mana = 0;
	}
}

void Magician::showSkills()
{
	cout << endl << "Количество маны: " << mana     << "\t\t"              << "Количество эфира: " << this->ether;
	cout << endl << "1: <Метеорит> "    << "\t\t\t" << "Затрата маны: "    << manacost[2] 
		 << endl << "2: <Шторм>"        << "\t\t\t" << "Затрата маны: "    << manacost[1]
		 << endl << "3: <Огненный шар>" << "\t\t"   << "Затарта маны: "    << manacost[0]
		 << endl << "4: <АРМАГЕДОН>"    << "\t\t\t" << "Нужно эфира: "	   << manacost[3];
}

void Magician::ARMAGEDON(Map* field)
{
	if (ether <= manacost[3]) {
		cout << endl << "Мага переполняет тёмная энергия! Он не в состоянии её контролировать."
			<< endl << "Из под земли вырывается лава, а с небес падают метеориты."
			<< endl << "Силы и здровье всех инитов, кто попал в радиус действия стремятся к нулю."
			<< endl << "Настал АРМАГЕДОН.";
		Object* o = new Object('@');
		o->color = colorLand::red;

		// Правая клетка 6
		(*field).add_on_map(this->XY.x + 1, this->XY.y, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x + 1, XY.y))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);
	
		// Правая верхняя клетка 3
		(*field).add_on_map(this->XY.x + 1, this->XY.y - 1, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x + 1, XY.y - 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);

		// Левая клетка 4 
		(*field).add_on_map(this->XY.x - 1, this->XY.y, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x - 1, XY.y))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);

		// Правая нижняя клетка 9
		(*field).add_on_map(this->XY.x + 1, this->XY.y + 1, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x + 1, XY.y + 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);

		// Нижняя клетка 8
		(*field).add_on_map(this->XY.x    , this->XY.y + 1, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x, XY.y + 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);

		// Верхняя левая клетка 1
		(*field).add_on_map(this->XY.x - 1, this->XY.y - 1, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x - 1, XY.y - 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);

		// Нижняя левая клекта 7
		(*field).add_on_map(this->XY.x - 1, this->XY.y + 1, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x - 1, XY.y + 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);
		
		//Верхняя клетка 2
		(*field).add_on_map(this->XY.x, this->XY.y - 1, o);
		system("cls");
		(*field).print_map();
		if ((*field).isUnit(this->XY.x, XY.y - 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(field);
			delete un;
		}
		Sleep(10);
		// Центральная клетка 5
		(*field).add_on_map(this->XY.x, this->XY.y, o);
		system("cls");
		(*field).print_map();
		delete this;
		Sleep(10);
	}
	else
		cout << endl << "Недостаточно темной энергии!";
}

void Magician::meteorite(Units* unit)
{
	if (mana >= manacost[1])
	{
		cout << endl << "С неба летит огромный метеорит!";
		unit->health.change(-5);
		mana -= manacost[1];
		ether += 5;
	}
	else
		cout << endl << "Недостаточно маны!";
}

void Magician::storm(Units* unit)
{
	if (mana >= manacost[2])
	{
		cout << endl << "Тучи сгущаюстя. Молнии и ураган наносят огромный урон, не щадя никого";
		unit->health.change(-10);
		this->health.change(-4);
		mana -= manacost[2];
		ether += 10;
	}
	else
		cout << endl << "Недостаточно маны!";
}

Magician::~Magician()
{
	cout << endl << "Маг был уничтожен!";
}


void Healer::selectSkill(int ch, Map* field)
{
	switch (ch)
	{
	case 1:
	{
		cover();
	} break;
	case 2:
	{
		selectLine();
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			heal(this->getLink(field));
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Целитель просто начинает молиться.";
			cover();
		}
	} break;
	case 3:
	{
		selectLine();
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_fireball(this->getLink(field));
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Целитель отменяет заклинание, но часть маны истрачена!";
			mana -= 1;
		}
	} break;
	case 4: mass_heal(field);
		break;
	}
	if (mana <= 0)
	{
		cout << endl << "Мана иссякла!";
		mana = 0;
	}
}

Healer::Healer(int &x, int &y) : Classe_warlock('H', 40, 8, 2, 80)
{
	XY.x = x;
	XY.y = y;
	prayer = 10;
}

void Healer::showSkills()
{
	cout << endl << "Количество маны: " << mana << "\t\t"   << "Сила молитвы: "		    << prayer;
	cout << endl << "1: <Молитва> "             << "\t\t\t" << "Затрата маны: "         << manacost[2]
		 << endl << "2: <Исцеление>"            << "\t\t\t" << "Затрата маны: "         << manacost[1]
		 << endl << "3: <Огненный шар>"         << "\t\t"   << "Затрата маны: "         << manacost[0]
		 << endl << "4: <Массовое исцеление>"   << "\t\t"   << "Нужно священных слов: " << manacost[3];
}


void Healer::heal(Units* unit)
{
	if (mana >= manacost[1])
	{
		cout << endl << "Целитель достаёт манускрипт и колбы с зельями и приступает к исцелению";
		unit->health.change(2);
		mana -= manacost[1];
	}
	else
		cout << endl << "Недостаточно маны!";
}
void Healer::mass_heal( Map* field)
{
	if (prayer >= manacost[3])
	{
		cout << endl << "Целитель взывает к небесам, юниты в радиусе 1 клетки исцелены";
		// Правая клетка 6
		if ((*field).isUnit(this->XY.x + 1, XY.y))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		// Правая верхняя клетка 3
		if ((*field).isUnit(this->XY.x + 1, XY.y - 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		// Левая клетка 4 
		if ((*field).isUnit(this->XY.x - 1, XY.y))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		// Правая нижняя клетка 9
		if ((*field).isUnit(this->XY.x + 1, XY.y + 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		// Нижняя клетка 8
		if ((*field).isUnit(this->XY.x, XY.y + 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		// Верхняя левая клетка 1
		if ((*field).isUnit(this->XY.x - 1, XY.y - 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		// Нижняя левая клекта 7
		if ((*field).isUnit(this->XY.x - 1, XY.y + 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		//Верхняя клетка 2
		if ((*field).isUnit(this->XY.x, XY.y - 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(field);
			un->health.change(3);
		}
		// Центральная клетка 5
		this->health.change(3);
	}	
	else
		cout << endl << "Священной энергии не хватает!";
}


void Healer::cover()
{
	if (mana >= manacost[2])
	{
		cout << endl << "Целитель читает молитву, количество священных слов увеличивается";
		prayer += 1;
	}
	else
		cout << endl << "Недостаточно маны!";
}


Healer::~Healer()
{
	cout << endl << "Цилитель был уничтожен!";
}


