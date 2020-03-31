#include "pch.h"
#include "Units.h"
#include <iostream>
#include <windows.h>
#include "Map.h"


Units::Units(char N, const int &h, const int &ar, const int &at, const int &r) : name(N), health(h), armor(ar), attack(at), radius(r)  //Список инициализации
{
	object = name;
}


bool Units::rules(Map *field, int x, int y)
{
	if ((*field).isUnit(x, y)) return false;
	int type = (*field).isLandscape(x, y);
	if (((type != 2)  && (type != 0)) || (type == 4)) return false;
	if ((*field).isBase(x, y)) return false;
	return true;
}


bool Units::movie(Map *field)
{
	bool space = false;
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
			}
			else
			{

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
			}
			else
			{

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
			}
			else
			{

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
			}
			else
			{
				
			}
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			return  space;
		}
		if (GetAsyncKeyState(VK_SHIFT))
		{
		
		}
	}
}


void Units::selected(Map *field)
{
	if (move(field))
		return;
}



Units::~Units()
{
}


