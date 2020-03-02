#include "Field.h"

Field::Field(size_t new_length, size_t new_width) : length(new_length), width(new_width)
{
	FldType new_fld(new std::shared_ptr<fieldElement[]>[width], std::default_delete<std::shared_ptr<fieldElement[]>[]>());
	for (size_t i = 0; i < width; ++i)
	{
		std::shared_ptr<fieldElement[]> new_elem(new fieldElement[length], std::default_delete<fieldElement[]>());
		new_fld[i] = new_elem;
	}

	fld = new_fld;
}

void Field::swap(Field& other)
{
	std::swap(units_cnt, other.units_cnt);
	std::swap(length, other.length);
	std::swap(width, other.width);
	std::swap(fld, other.fld);
}

Field::Field(Field const& other)
{
	units_cnt = other.units_cnt;
	length = other.length;
	width = other.width;
	fld = other.fld;
}

Field& Field::operator=(Field const& other)
{
	if (&other != this)
	{
		Field(other).swap(*this);
	}
	return *this;
}

Field& Field::operator=(Field&& other)
{
	swap(other);
	return *this;
}

addAndRemoveResult Field::addUnit(UnitBase* unitToAdd, Point p)
{
	if (fld[p.x][p.y].unit != nullptr)
		return addAndRemoveResult::addErrorColission;

	++units_cnt;
	fld[p.x][p.y].unit = unitToAdd;
	return addAndRemoveResult::unitAdded;
}

addAndRemoveResult Field::removeUnit(Point p)
{
	if (fld[p.x][p.y].unit == nullptr)
		return addAndRemoveResult::removeErrorNoUnit;

	--units_cnt;
	fld[p.x][p.y].unit = nullptr;
	return addAndRemoveResult::unitRemoved;
}

moveResult Field::moveUnit(Point from, Point to)
{
	UnitBase* unitFrom = fld[from.x][from.y].unit;
	auto removeRes = removeUnit(from);
	if (removeRes == addAndRemoveResult::removeErrorNoUnit)
		return moveResult::moveCoordinateError;

	auto addRes = addUnit(unitFrom, to);
	if (addRes == addAndRemoveResult::addErrorColission)
		return moveResult::moveCoordinateError;

	return moveResult::moveComplete;

}

UnitBase* Field::getUnit(Point p)
{
	return fld[p.x][p.y].unit;
}

Field::Field(Field&& other)
{
	swap(other);
}

void operator<<(std::ostream& out, Field& f)
{
	std::cout << std::string(5, ' ');
	for (size_t j = 0; j < f.length; ++j)
	{
		std::cout << j << "   ";
	}
	std::cout << "\n";

	std::cout << std::string(5, ' ');
	for (size_t j = 0; j < f.length; ++j)
	{
		std::cout << '-' << std::string(std::to_string(j).size() + 2, ' ');
	}
	std::cout << "\n";

	for (int i = 0; i < f.width; ++i)
	{
		std::cout << i << std::string(3 - std::to_string(i).size(), ' ');
		for (int j = 0; j < f.length; ++j)
		{
			std::cout << "| ";
			UnitBase* curUnit = f.getUnit({ i, j });
			std::cout << (curUnit == nullptr ? 'G' : curUnit->name) << std::string(std::to_string(j).size(), ' ');
		}
		std::cout << '|' << "\n";
		std::cout << std::string(5, ' ');
		for (size_t j = 0; j < f.length; ++j)
		{
			std::cout << '-' << std::string(std::to_string(j).size() + 2, ' ');
		}
		std::cout << "\n";
	}
}
