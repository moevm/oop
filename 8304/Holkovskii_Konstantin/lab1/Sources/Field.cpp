#include "../Headers/Field.h"

Field::SomeStruct Field::operator[](int a)
{
	return SomeStruct(field[a]);
}

Field::Field(int s, int l): width(l), height(s), MaxCount(l*s/4), Count(0) {
	field = new element* [height];
	for (int i = 0; i < height; ++i)
		field[i] = new element[width]();
}

Field::Field(Field const& a) {
    height = a.height;
	width = a.width;
	MaxCount = a.MaxCount;
	Count = a.Count;
	field = new element * [height];
	for (int i = 0; i < height; ++i) {
        field[i] = new element[width]();
		for (int j = 0; j < width; ++j)
		    field[i][j].unit = element(a.field[i][j]).unit;
	}
}

Field::Field(Field&& a) noexcept{
    height = a.height;
	width = a.width;
	field = a.field;
	a.field = nullptr;
	a.height = 0;
	a.width = 0;
}

Field::~Field() {
	for (int i = 0; i < height; ++i)
		delete[] field[i];
	delete[] field;
}

void Field::addUnit(Point const & a, char Name) {
    if(field[a.y][a.x].unit != nullptr && Count == MaxCount) return;

    auto tof = new Tier1Factory();
    auto tsf = new Tier2Factory();
    auto ttf = new Tier3Factory();

    switch (Name) {
        case 'K':
            field[a.y][a.x].unit.reset(tof->createType1());
            break;
        case 'S':
            field[a.y][a.x].unit.reset(tof->createType2());
            break;
        case 'A':
            field[a.y][a.x].unit.reset(tsf->createType1());
            break;
        case 'R':
            field[a.y][a.x].unit.reset(tsf->createType2());
            break;
        case 'C':
            field[a.y][a.x].unit.reset(ttf->createType1());
            break;
        case 'H':
            field[a.y][a.x].unit.reset(ttf->createType2());
            break;
        default:{}
    }
    delete tof;
    delete tsf;
    delete ttf;
    ++Count;
}

void Field::remUnit(Point const & a) {
    if(field[a.y][a.x].unit != nullptr) --Count;
    field[a.y][a.x].unit = nullptr;
}

bool Field::move(Point const & o, Point const & n) {
    if(field[n.y][n.x].unit != nullptr) return false;
    field[n.y][n.x].unit = element(field[o.y][o.x]).unit;
    field[o.y][o.x].unit = nullptr;
    return true;
}

void Field::show() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(field[i][j].unit == nullptr) std::cout << "* ";
            else
                std::cout << field[i][j].unit->name << ' ';
        }
        std::cout << std::endl;
    }
}

Field::element::element(): unit(nullptr){}

Field::element::element(element const& a) {
	if (a.unit == nullptr) {
		unit = nullptr;
		return;
	}
	switch (a.unit->name) {
	    case 'K':
		unit = std::unique_ptr<Unit>(new Knight(*dynamic_cast<Knight*>(&(*(a.unit)))));
		break;
	case 'S':
		unit = std::unique_ptr<Unit>(new Shieldman(*dynamic_cast<Shieldman*>(&(*(a.unit)))));
		break;
	case 'A':
		unit = std::unique_ptr<Unit>(new Archer(*dynamic_cast<Archer*>(&(*(a.unit)))));
		break;
	case 'R':
		unit = std::unique_ptr<Unit>(new Ranger(*dynamic_cast<Ranger*>(&(*(a.unit)))));
		break;
	case 'C':
		unit = std::unique_ptr<Unit>(new Caster(*dynamic_cast<Caster*>(&(*(a.unit)))));
		break;
	case 'H':
		unit = std::unique_ptr<Unit>(new Healer(*dynamic_cast<Healer*>(&(*(a.unit)))));
	}

}

Field::iterator::iterator(element** field_, int height_, int width_, int y_, int x_): field(field_), height(height_), width(width_), y(y_), x(x_){}

Field::iterator& Field::iterator::operator++()
{
	if (x >= width - 1) {
		if (y == height - 1) {
			x = width;
			return *this;
		}
		x = 0;
		++y;
		return *this;
	}
	++x;
	return *this;
}

Field::iterator Field::iterator::operator++(int)
{
	auto tmp = iterator(*this);
	if (x >= width - 1) {
		if (y == height - 1) {
			x = width;
			return tmp;
		}
		x = 0;
		++y;
		return tmp;
	}
	++x;
	return tmp;
}

Field::iterator& Field::iterator::operator--()
{
	if (x == 0) {
		if (y == 0) return *this;
		x = width - 1;
		--y;
		return *this;
	}
	--x;
	return *this;
}

Field::iterator Field::iterator::operator--(int)
{
	auto tmp = *this;
	if (x == 0) {
		if (y == 0) return tmp;
		x = width - 1;
		--y;
		return tmp;
	}
	--x;
	return tmp;
}

bool Field::iterator::operator==(const iterator& b) const{ return ((y == b.y)&&(x == b.x));}

bool Field::iterator::operator!=(const iterator& b) const { return !operator==(b);}

const Field::element& Field::iterator::operator*() const{ return field[y][x];}

Field::element const* Field::iterator::operator->() const { return &(field[y][x]);}

Field::SomeStruct::SomeStruct(element* a): arr(a){}

Field::element& Field::SomeStruct::operator[](int a) {
	return arr[a];
}

Point::Point(int x_, int y_):x(x_),y(y_) {}

Point &Point::operator=(Point const &a) {
    x = a.x;
    y = a.y;
    return *this;
}

Point::Point(Point const &a):x(a.x),y(a.y) {}
