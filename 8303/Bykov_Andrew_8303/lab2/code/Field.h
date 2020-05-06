#pragma once
#include "Land.h"
#include "Unit_types.h"

class FieldIterator : public std::iterator<std::input_iterator_tag, Cell> {

	friend class Field;
private:
	Point p;
	Cell ** cells;
	const int height;
	const int width;
	FieldIterator(Point P, Cell ** cells, const int Width, const int Height) :
		p(P),
		cells(cells),
		width(Width),
		height(Height) {};
public:

	Cell& operator++ (int n)
	{
		Point next = p;
		next.x++;

		if (next.x < width) {
			p = next;
			return cells[p.x][p.y];
		}
		else {

			next.x = 0;
			next.y++;

			p = next;
			return cells[p.x][p.y];
		}
	}

	typename FieldIterator::reference operator*() { return  cells[p.x][p.y]; };
	bool operator!=(const FieldIterator &it) { return p != it.p; };
	bool operator==(const FieldIterator &it) { return p == it.p; };
};
class Field
{
	friend class FieldIterator;
private:
	const int max_units;
	const int width; 
	const int height;
	int count;
	Cell ** cells;
	
	struct BasePlace
	{
		WaterBase * water = nullptr;
		FireBase  * fire  = nullptr;
		void replaceWater(Point p)
		{
			waterCords = p;
		};
		void replaceFire(Point p)
		{
			fireCords = p;
		};
	private:
		Point waterCords;
		Point fireCords;
	}base;


public:
		
	Field(int w, int h);
	Field(Field &&field);
	Field &operator=(const Field &field);

	void print() const;
	bool check_point(int x, int y) const;
	Unit * getUnit(int x, int y) const;

	bool move_unit(int x1, int y1, int x2, int y2);
	bool addUnit(Point p, Unit * unit);
	void del(int x, int y);

	FieldIterator begin() 
	{ 
		return FieldIterator(Point(0, 0), cells, height, width);
	}
	FieldIterator end() 
	{ 
		return FieldIterator(Point(0, height), cells, height, width);
	}

	WaterBase * getWater();
	FireBase
 * getFire();
	
};	

