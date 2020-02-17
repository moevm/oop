#include "Field.h"
#include "Unit_types.h"


void Field :: add_unit(string code, int x, int y, int number)
{
	if (!check_point(y, x))
	{
		cout << "ERROR\n";
		return;
	}
	if (count + 1 > max_units)
	{
		cout << "Over limit\n";
		return;
	}
	else 
		count += 1;

	if (code == units[y][x][0].code)
	{
		if (units[y][x][0].number + number <= 0)
			units[y][x] = new Unit();
		else units[y][x][0].change_num(units[y][x][0].number + number);
		return;
	}

	if (!(units[y][x][0].army == "  "))
	{
		cout << "Mesh is occupied\n";
		return;
	}

	if (number < 0)
	{
		cout << "Negative number\n";
		return;
	}
	if (code[0] == 'I')
	{
		//units[y][x] = new Infantry(number);
		if (code[1] == 'B')
			units[y][x] = new Berserks(number);
			//units[y][x][0].sub_class("Berserks");
		if (code[1] == 'S')
			units[y][x] = new Spearmen(number);
			//units[y][x][0].sub_class("Swordsmen");
	}
	if (code[0] == 'C')
	{
		//units[y][x] = new Cavalry(number);
		if (code[1] == 'C')
			units[y][x] = new Cuirassiers(number);
			//units[y][x][0].sub_class("Cuirassiers");
		if (code[1] == 'U')
			units[y][x] = new Ulans(number);
			//units[y][x][0].sub_class("Ulans");
	}
	if (code[0] == 'A')
	{
		//units[y][x] = new Archers(number);
		if (code[1] == 'F')
			units[y][x] = new Fire_Archers(number);
			//units[y][x][0].sub_class("Fire_Archers");
		if (code[1] == 'H')
			units[y][x] = new Hunters(number);
			//units[y][x][0].sub_class("Hunters");
	}
	
	list_units[count - 1] = units[y][x];



}

void Field :: move_unit(int x1, int y1, int x2, int y2)
{
	if (!check_point(y1, x1) || !check_point(y2, x2))
	{
		cout << "ERROR\n";
		return;
	}
	if(!(units[y2][x2][0].army == "  "))
	{
		cout << "Mesh is occupied\n";
		return;
	}
	if ((units[y1][x1][0].army == "  "))
	{
		cout << "No army\n";
		return;
	}
	units[y2][x2] = units[y1][x1];
	units[y1][x1] = new Unit();
}

void Field::del(int x, int y)
{
	if (!check_point(y, x))
	{
		cout << "ERROR\n";
		return;
	}
	units[y][x] = new Unit();
}



