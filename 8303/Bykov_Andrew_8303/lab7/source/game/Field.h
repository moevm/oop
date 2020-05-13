#pragma once
#include <SFML/Graphics.hpp>
#include "Land.h"
#include <fstream>


class WaterBase; 
class FireBase;
class Adapter;
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
	Cell ** cells;
	Adapter * adapter;
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
	float curFrame;
public:
	Point chosenUnit[2] = { Point(-1, -1), Point(-1, -1) };
	const int width;
	const int height;
	Field(int w, int h, Adapter * adapter);
	Field(Field &&field);
	Field &operator=(const Field &field);
	void paint(sf::RenderWindow * window, float frame);
	bool check_point(int x, int y) const;
	Unit * getUnit(int x, int y) const;
	bool moveUnit(int x1, int y1, int x2, int y2);
	bool addUnit(Point p, Unit * unit);
	bool addNetral(Point p, Netral * n);
	bool addLand(Point p, Land * l);
	FieldIterator begin() 
	{ 
		return FieldIterator(Point(0, 0), cells, height, width);
	}
	FieldIterator end() 
	{ 
		return FieldIterator(Point(0, width), cells, height, width);
	}
	WaterBase * getWater();
	FireBase * getFire();
	Adapter * getAdapter();
	Base * getBuilding(int x, int y);
};	

