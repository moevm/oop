#include "pch.h"
#include "Archer.h"
#include "Classes.h"
#include "Map.h"


Archer::Archer(int &x, int &y) : Classe_archer('L', 60, 6, 2, 10)
{
	XY.x = x;
	XY.y = y;
	_luck = 30;
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}

void Archer::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 1: hail_of_arrows(field, link, adapter);
	break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			poison_arrow(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Стрелок зря потратил стрелы!";
			arrows -= 1;
		}
	}
	break;
	case 3:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_headshot(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Стрелок зря потратил стрелы!";
			arrows -= 1;
		}
	}
	break;
	case 4: {
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			double_shot(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Стрелок зря потратил стрелы!";
			arrows -= 1;
		}
	}
		break;
	}
	if (arrows <= 0)
	{
		cout << endl << "Стрелы иссякли!";
		arrows = 0;
	}
}


void Archer::showSkills(Adapter *adapter) {
	cout << endl << "Количество стрел: " << arrows <<"\t\t"   << "Удача: " << _luck << endl
				 << "1: <Обстрел>"			 <<"\t\t\t"<<"Затраты стрел: " << arrowscost[0] << endl
				 << "2: <Отравленная стрела>"<<"\t\t"  <<"Затраты стрел: " << arrowscost[1] << endl
				 << "3: <Выстрел в голову>"  <<"\t\t"    <<"Затраты стрел: " << arrowscost[2] << endl
				 << "4: <Двойной выстрел>"   <<"\t\t"  <<"Требуется надежды: " << arrowscost[3] << endl;
}

void Archer::double_shot(Units* unit, Map* field, Adapter *adapter)
{
	if (_luck >= arrowscost[3])
	{
		cout << endl << "Двойное попадание, ваш противник получает в два раза больше урона.";
		unit->health.change(-4);
		unit->reaction(field, adapter);
		arrows -= 1;
		_luck -= arrowscost[3];
	}
	else
		cout << endl << "Недостаточно удачи!";
}
void Archer::hail_of_arrows(Map* field, Units **link, Adapter *adapter)
{
	if (arrows >= arrowscost[0])
	{
		cout << endl << "Лучник натянул тетеву, юниты в радиусе 1 клетки получают урон!";
		string message = "Лучник натянул тетеву, юниты в радиусе 1 клетки получают урон!";
		adapter->request(message);
		// Правая клетка 6
		if ((*field).isUnit(this->XY.x + 1, XY.y))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		// Правая верхняя клетка 3
		if ((*field).isUnit(this->XY.x + 1, XY.y - 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		// Левая клетка 4 
		if ((*field).isUnit(this->XY.x - 1, XY.y))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		// Правая нижняя клетка 9
		if ((*field).isUnit(this->XY.x + 1, XY.y + 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		// Нижняя клетка 8
		if ((*field).isUnit(this->XY.x, XY.y + 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		// Верхняя левая клетка 1
		if ((*field).isUnit(this->XY.x - 1, XY.y - 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		// Нижняя левая клекта 7
		if ((*field).isUnit(this->XY.x - 1, XY.y + 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		//Верхняя клетка 2
		if ((*field).isUnit(this->XY.x, XY.y - 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(-(3 + this->attack.returnAttack()));
			un->reaction(field, adapter);
		}
		arrows -= arrowscost[0];
		_luck += 1;
	}
}
void Archer::poison_arrow(Units* unit, Map* field, Adapter *adapter)
{
	if (arrows >= arrowscost[1])
	{

		cout << endl << "Отравленная стрела.";
		string message = "Лучник использует способность <Отравленная стрела>";
		adapter->request(message);
		unit->health.change(-3);
		unit->reaction(field, adapter);
		arrows -= arrowscost[1];
		_luck += 1;
	}
	else
	{
		cout << endl << "Недостаточно стрел!";
		string message = "Лучник не может использовать заклинание";
		adapter->request(message);
	}

}
Archer::~Archer()
{
	cout << endl << "Лучник был уничтожен!";
}

Arbalester::Arbalester(int &x, int &y) : Classe_archer('A', 70, 7, 3, 6)
{
	XY.x = x;
	XY.y = y;
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}

void Arbalester::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 4: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			crossbow_shot(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Арбалетчик зря потратил стрелы!";
			arrows -= 1;
		}
	}
		break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			fire_shot(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Арбалетчик зря потратил стрелы!";
			arrows -= 1;
		}
	}
	break;
	case 3:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_headshot(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Арбалетчик зря потратил стрелы!";
			arrows -= 1;
		}
	}
	break;
	case 1: { reliable_shot(adapter); } break;
	}
	if (arrows <= 0)
	{
		cout << endl << "Стрелы иссякли!";
		arrows = 0;
	}
}

void Arbalester::showSkills(Adapter *adapter) {
	cout << endl << "Количество стрел: " << "\t\t"<< arrows << "Интуиция: " << _intuition
		<< "1: <Орлинный глаз>\t\tТребуется интуиции: " << arrowscost[0] << endl
		<< "2: <Огненная стрела>\t\tЗатраты стрел: " << arrowscost[1] << endl
		<< "3: <Выстрел в голову>\t\tЗатраты стрел: " << arrowscost[2] << endl
		<< "4: <Выстрел>\t\tЗатраты стрел: " << arrowscost[3] << endl;
	adapter->request("Арбалетчик докладывает о доступных способностях");
}

void Arbalester::crossbow_shot(Units* unit, Map* field, Adapter *adapter)
{
	if (arrows >= arrowscost[0])
	{

		cout <<"Арбатлетчик делает выстрел из арбалета"<< endl << " ";
		unit->health.change(-(2 + this->attack.returnAttack()));
		adapter->request("Арбалетчик делает выстрел из арбалета");
		unit->reaction(field, adapter);
		arrows -= arrowscost[0] * 4;
		_intuition -= arrowscost[0];
		
	}
	else
	{
		cout << endl << "Недостаточно стрел!";
		adapter->request("Арбалетчик отменяет действие, недостаточно стрел");
	}
}

void Arbalester::fire_shot(Units* unit, Map* field, Adapter *adapter)
{
	if (arrows >= arrowscost[1])
	{
		cout << endl << "Огненная стрела.";
		adapter->request("Арбалетчик выпускает огненную стрелу");
		unit->health.change(-(3 + this->attack.returnAttack()));
		unit->reaction(field, adapter);
		arrows -= arrowscost[1];
		_intuition += 1;
		
	}
	else
	{
		cout << endl << "Недостаточно стрел!";
		adapter->request("Арбалетчик отменяет действие, недостаточно стрел");
	}
	
}

void Arbalester::reliable_shot(Adapter *adapter)
{
	if (_intuition >= arrowscost[3])
	{
		cout << endl << "Арбалетчик усилил свои навыки и лучше попадает в цель. Количтесво стрел увеличено.";
		adapter->request("Арбалетчик усилил свои навыки и лучше попадает в цель");
		this->attack.change(2);
		arrows += 5;
		_intuition -= arrowscost[3];
		
	}
	else
	{
		cout << endl << "Недостаточно стрел!";
		adapter->request("Арбалетчик отменяет действие, недостаточно интуиции");
	}
}

Arbalester::~Arbalester()
{
	cout << endl << "Абалетчик был уничтожен!";
}

