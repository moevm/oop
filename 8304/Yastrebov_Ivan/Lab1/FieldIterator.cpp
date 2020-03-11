#include "pch.h"


#include "FieldIterator.h"
#include "Unit.h"
#include "Field.h"


Iterator::Iterator(Field& gameField) : gameField(gameField)
{
	this->i = 0;
	this->j = 0;
	this->width = gameField.getSize().width;
	this->height = gameField.getSize().height;
}


bool Iterator::hasNext() const
{
	return (int)i < (int)gameField.getSize().height && (int)j < (int)gameField.getSize().width;

}


void Iterator::first()
{
	j = 0;
	i = 0;
}


const Iterator& operator++(Iterator& it)
{
	if (it.j + 1 < it.width) {
		++it.j;
	}
	else {
		++it.i;
		it.j = 0;
	}

	return it;
}

const Iterator& operator--(Iterator& it)
{
	if (it.j - 1 >= 0) {
		--it.j;
	}
	else {
		--it.i;
		it.j = it.width - 1;
	}

	return it;
}


Unit* Iterator::operator*() const
{
	return ((gameField.GetHead())[i * this->width + j]);
}


const bool operator==(Iterator& left, Iterator& right) {
	return (right.i == left.i) && (left.j == right.j);
}


const bool operator!=(Iterator& left, Iterator& right) {
	return !(left == right);
}


Iterator& Iterator::operator=(const Iterator& it) {	
	if (this == &it)
		return *this;

	this->gameField = it.gameField;
	this->height = it.height;
	this->width = it.width;
	this->i = it.i;
	this->j = it.j;

	return *this;
}

const bool operator<(Iterator& left, Iterator& right) {
	if (left.i > left.j)
		return false;
	else if (left.i < left.j)
		return true;
	else
		return left.j < right.j;


}

const bool operator<=(Iterator& left, Iterator& right) {
	return (left < right) || (left == right);
}

const bool operator>(Iterator& left, Iterator& right) {
	return (right < left);

}

const bool operator>=(Iterator& left, Iterator& right) {
	return (right < left) || (right == left);

}