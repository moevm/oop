#pragma once


#include "Unit.h"
class Field
{
public:
	class Iterator;
	int max_units;
	int count;
	Unit *** units;
	Unit ** list_units;
	int width; int height;
	Field(int w, int h);
	Field(const Field &field);
	Field(Field &&field);
	void print();
	void add_unit(string code, int x, int y, int number);
	void move_unit(int x1, int y1, int x2, int y2);
	bool check_point(int x, int y);
	void save(Field &field);
	void load(Field &field);
	void del(int X, int Y);
	
	class Iterator {

		Unit** current;

	public:
		Iterator(Unit** first)
		{
			current = first;
		}

		Unit*& operator+ (int n)
		{
			return *(current + n);
		}
		Unit*& operator++ (int n)
		{
			return *current++;
		}
		Unit*& operator++ ()
		{
			return *++current;
		}
		Unit*& operator- (int n)
		{
			return *(current - n);
		}

		Unit*& operator-- (int n)
		{
			return *current--;
		}

		Unit*& operator-- ()
		{
			return *--current;
		}
		bool operator!= (const Iterator& iter)
		{
			return current != iter.current;
		}
		bool operator== (const Iterator& iter)
		{
			return current == iter.current;
		}
		Unit*& operator* ()
		{
			return *current;
		}
	};
	Iterator begin()
	{
		return 	list_units;
	}
	Iterator end()
	{
		return 	list_units + count;
	}

};


