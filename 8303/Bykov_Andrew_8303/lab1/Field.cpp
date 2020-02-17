#include "Field.h"
#include "Unit_types.h"

Field::Field(int w, int h)
{
	count = 0;
	width = w;
	height = h;
	max_units = width * height / 2;
	units = new Unit**[height];
	list_units = new Unit*[max_units];
	for (int i = 0; i < height; i++) units[i] = new Unit*[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			units[i][j] = new Unit();
		}
	/*
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
		{
			units[i][j] = new Berserks(10);
		}

	for (int i = 0; i < 8; i++)
		for (int j = 6; j < 10; j++)
		{
			units[i][j] = new Cuirassiers(10);
			units[i][j][0].team = 1;
		}
	*/
}

void Field:: print()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 7 + 1; j++)
			cout << "-";
		cout << endl;
		cout << "| ";

		for (int j = 0; j < width; j++)
		{
			if (!units[i][j][0].team)
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 2));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 4));
			cout << units[i][j][0].army[0] << units[i][j][0].s_class[0] << units[i][j][0].num;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 7));
			cout << " | ";
		}
		cout << endl;
	}
	for (int j = 0; j < width * 7 + 1; j++)
		cout << "-";
	cout << endl;
}

bool Field::check_point(int x, int y)
{
	return(x >= 0 && x < width && y >= 0 && y < height);
}

void Field::save(Field &field)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			field.units[i][j] = units[i][j];
		}
	
}

void Field::load(Field &field)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			units[i][j] = field.units[i][j];
		}
}

Field::Field(const Field &field)
{
	count = 0;
	width = field.width;
	height = field.height;
	max_units = width * height / 2;
	units = new Unit**[height];
	for (int i = 0; i < height; i++) units[i] = new Unit*[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			units[i][j] = field.units[i][j];
		}
}

Field::Field(Field &&field)
{
	count = 0;
	width = field.width;
	height = field.height;
	max_units = width * height / 2;
	units = new Unit**[height];
	for (int i = 0; i < height; i++) units[i] = new Unit*[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			units[i][j] = field.units[i][j];
			delete(field.units[i][j]);
		}
		delete(field.units[i]);
	}
	delete(field.units);
}

