#pragma once
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>
#include "UnitBase.h"

struct Field
{
private:
	struct fieldElement
	{
		UnitBase* unit = nullptr;
	};
	using FldType = std::shared_ptr<std::shared_ptr<fieldElement[]>[]>;

public:

	Field(size_t new_length = 10, size_t new_width = 10);
	Field(Field const& other);
	Field(Field&& other);
	Field& operator=(Field const& other);
	Field& operator=(Field&& other);

	addAndRemoveResult addUnit(UnitBase* unitToAdd, Point p);
	addAndRemoveResult removeUnit(Point p);
	moveResult moveUnit(Point from, Point to);
	UnitBase* getUnit(Point p);

	~Field() = default;

	void swap(Field& other);
	friend void operator<<(std::ostream& out, Field& f);

private:
	size_t units_cnt = 0;
	size_t length = 0;
	size_t width = 0;
	FldType fld;
};

