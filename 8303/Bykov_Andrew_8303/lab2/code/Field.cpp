#include "Field.h"

Field::Field(int w, int h) : width(w), height(h), max_units(w*h/2)
{
	count = 0;
	cells = new Cell*[height];
	for (int i = 0; i < height; i++) cells[i] = new Cell[width];
		
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			cells[i][j].unit = new EmptyUnit();
			cells[i][j].land = new SwampProxy();
			cells[i][j].netral = new Rune();
		}
	base.water = new WaterBase(Point(0, 0), Point(1, 1), this);
	base.fire = new FireBase(Point(width - 1, height - 1), Point(width - 2, height - 2), this);
}
Field& Field::operator=(const Field &field) 
{
	count = field.count;
	cells = new Cell*[height];
	for (int i = 0; i < height; i++) cells[i] = new Cell[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			cells[i][j] = field.cells[i][j];
		}
	return *this;
}
Field::Field(Field &&field) : width(field.width), height(field.height), max_units(width * height / 2)
{
	count = field.count;
	cells = new Cell*[height];
	for (int i = 0; i < height; i++) cells[i] = new Cell[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cells[i][j] = field.cells[i][j];
			
		}
		delete(field.cells[i]);
	}
	delete(field.cells);
}

void Field:: print() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 11; j++)
			cout << "-";
		cout << endl;
		cout << "|";

		for (int j = 0; j < width; j++)
		{
			if (!cells[i][j].unit->getTeam())
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 2));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 4));
			cout.width(2);
			if (cells[i][j].unit->getClass() != "  ")
				cout << "(" << cells[i][j].unit->getSerialNumber() << ")" << cells[i][j].unit->getClass()[0] << cells[i][j].unit->getSubclass()[0] << cells[i][j].unit->getSnum();
			else
				cout << "        ";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 7));
			cout << " | ";
		}
		cout << endl;
	}
	for (int j = 0; j < width * 11; j++)
		cout << "-";
	cout << endl;
}
bool Field::check_point(int x, int y) const
{
	return(x >= 0 && x < width && y >= 0 && y < height);
}
Unit * Field::getUnit(int x, int y) const
{
	if (!check_point(y, x))
	{
		cout << "ERROR\n";
		return nullptr;
	}
	return (cells[y][x].unit);
}

bool Field::addUnit(Point p, Unit * unit)
{
	if (!check_point(p.y, p.x))
	{
		cout << "ERROR\n";
		return false;
	}

	if (unit->getSubclass() == cells[p.y][p.x].unit->getSubclass())
	{
		if (cells[p.y][p.x].unit->getNumber() + unit->getNumber() <= 0)
			cells[p.y][p.x].unit = new EmptyUnit();
		else
			cells[p.y][p.x].unit->setNumber(cells[p.y][p.x].unit->getNumber() + unit->getNumber());
		return false;
	}
	if (count + 1 > max_units)
	{
		cout << "Over limit\n";
		return false;
	}
	else
		count += 1;
	if (!(cells[p.y][p.x].unit->isEmpty()))
	{
		cout << "Mesh is occupied\n";
		return false;
	}

	cells[p.y][p.x].unit = unit;
	return true;
}
bool Field::move_unit(int x1, int y1, int x2, int y2)
{
	if (!check_point(y1, x1) || !check_point(y2, x2))
	{
		cout << "ERROR\n";
		return false;
	}
	if (!cells[y2][x2].land->isInteract(cells[y1][x1].unit))
	{
		cout << "ERROR this units can't go there\n";
		return false;
	}
	if (!(cells[y2][x2].unit->isEmpty()))
	{
		cout << "Mesh is occupied\n";
		return false;
	}
	if (cells[y1][x1].unit->isEmpty())
	{
		cout << "No army\n";
		return false;
	}
	cells[y2][x2].unit = cells[y1][x1].unit;
	cells[y1][x1].unit = new EmptyUnit();
	cells[y2][x2].land->interact(cells[y2][x2].unit);
	*cells[y2][x2].netral >> (cells[y2][x2].unit);
	return true;
}
void Field::del(int x, int y)
{
	if (!check_point(y, x))
	{
		cout << "ERROR\n";
		return;
	}
	if (!(cells[y][x].unit->isEmpty())) count--;
	cells[y][x].unit = new EmptyUnit();

}

WaterBase * Field::getWater()
{
	return base.water;
}
FireBase * Field::getFire()
{
	return base.fire;
}


