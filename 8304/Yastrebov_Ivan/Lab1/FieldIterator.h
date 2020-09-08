#pragma once

#ifndef OOP_FIELDITERATOR_H
#define OOP_FIELDITERATOR_H

#include <cstdio>


class Field;
class Unit;

class Iterator
{
public:
	explicit Iterator(Field& gameField);

	bool hasNext() const;
	void first();
	friend const Iterator& operator--(Iterator& it);
	friend const Iterator& operator++(Iterator& it);
	friend const bool operator==(Iterator& left, Iterator& right);
	friend const bool operator!=(Iterator& left, Iterator& right);

	friend const bool operator<(Iterator& left, Iterator& right);
	friend const bool operator<=(Iterator& left, Iterator& right);
	friend const bool operator>(Iterator& left, Iterator& right);
	friend const bool operator>=(Iterator& left, Iterator& right);

    Iterator& operator=(const Iterator& it);

	Unit* operator*() const;


private:
	size_t i;
	size_t j;
	size_t width;
	size_t height;
	Field& gameField;
};




#endif //OOP_FIELDITERATOR_H
