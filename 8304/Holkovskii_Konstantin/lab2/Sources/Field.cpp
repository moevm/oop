#include "../Headers/Field.h"

#include <memory>


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
		for (int j = 0; j < width; ++j) {
            field[i][j].unit = element(a.field[i][j]).unit;
            field[i][j].base = element(a.field[i][j]).base;
            if(field[i][j].base != nullptr)
                ListBases.push_back(field[i][j].base);
		}
	}
}

Field::Field(Field&& a) noexcept{
    height = a.height;
	width = a.width;
	field = a.field;
	MaxCount = a.MaxCount;
	Count = a.Count;
	ListBases = a.ListBases;
	a.ListBases.clear();
	a.field = nullptr;
	a.height = 0;
	a.width = 0;
	a.Count = 0;
	a.MaxCount = 0;
}

Field::~Field() {
	for (int i = 0; i < height; ++i)
		delete[] field[i];
	delete[] field;
}

void Field::addUnit(Point const & a, char Name) {
    auto tof = new Tier1Factory();
    auto tsf = new Tier2Factory();
    auto ttf = new Tier3Factory();

    Unit* hiiiiiiiiiii;

    switch (Name) {
        case 'K':
            hiiiiiiiiiii = (tof->createType1());
            break;
        case 'S':
            hiiiiiiiiiii = (tof->createType2());
            break;
        case 'A':
            hiiiiiiiiiii = (tsf->createType1());
            break;
        case 'R':
            hiiiiiiiiiii = (tsf->createType2());
            break;
        case 'C':
            hiiiiiiiiiii = (ttf->createType1());
            break;
        case 'H':
            hiiiiiiiiiii = (ttf->createType2());
            break;
        default:{}
    }
    hiiiiiiiiiii->Say();
    ProxyLandscape proxy(field[a.y][a.x].type);
    field[a.y][a.x].unit.reset(hiiiiiiiiiii);
    proxy.execute(field[a.y][a.x].unit);
    (*field[a.y][a.x].unit)*field[a.y][a.x].object;
    std::cout << "После того как меня добавили в клетку с ландшафтом ";
    switch (field[a.y][a.x].type){
        case LandscapeTypes::Grass:
            std::cout << "\"Трава\"";
            break;
        case LandscapeTypes::Mount:
            std::cout << "\"Гора\"";
            break;
        case LandscapeTypes::Dust:
            std::cout << "\"Пыль\"";
    }
    std::cout << ", с нйтр. объектом " << field[a.y][a.x].ObjName << " мои характеристики: \n";
    field[a.y][a.x].unit->Say();

    delete tof;
    delete tsf;
    delete ttf;
    ++Count;
}

void Field::remUnit(Point const & a) {
    if(field[a.y][a.x].unit != nullptr) --Count;
    field[a.y][a.x].unit = nullptr;
    for(auto & i : ListBases){
        if(i->Units.components.find(a) != i->Units.components.end()){
            i->removeUnit(a);
            return;
        }
    }
}

bool Field::move(Point const & o, Point const & n) {
    if(field[n.y][n.x].unit != nullptr) return false;
    field[n.y][n.x].unit = element(field[o.y][o.x]).unit;
    field[o.y][o.x].unit = nullptr;
    (*field[n.y][n.x].unit)*field[n.y][n.x].object;
    for(auto & i : ListBases){
        if(i->Units.components.find(o) != i->Units.components.end()){
            i->removeUnit(o);
            i->addUnit(n);
            return true;
        }
    }
    return true;
}

void Field::show() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(field[i][j].base != nullptr) std::cout << "B ";
            else
                if(field[i][j].unit != nullptr)
                    std::cout << field[i][j].unit->name << ' ';
                else
                    std::cout << "* ";
        }
        std::cout << std::endl;
    }
}

Field::element::element(): unit(nullptr), base(nullptr){
    size_t chance = rand() % 10;
    switch (chance){
        case 0:
            object = std::make_shared<Oasis>();
            ObjName = "\"Оазис\"";
            break;
        case 1:
            object = std::make_shared<Crocodile>();
            ObjName = "\"Крокодил\"";
            break;
        case 2:
            object = std::make_shared<PowerStatue>();
            ObjName = "\"Статуя силы\"";
            break;
        case 3:
            object = std::make_shared<RangeStatue>();
            ObjName = "\"Статуя зоркости\"";
            break;
        default:
            ObjName = "\"Нет объекта\"";
            object = nullptr;
    }
    chance = rand()%3;
    switch(chance){
        case 0:
            type = LandscapeTypes::Grass;
            break;
        case 1:
            type = LandscapeTypes::Mount;
            break;
        case 2:
            type = LandscapeTypes::Dust;
            break;
    }
}

Field::element::element(element const& a) {
	if (a.unit == nullptr) {
		unit = nullptr;
        if (a.base != nullptr)
            base = std::make_shared<Base>(*a.base);
        else
            base = nullptr;

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
    if (a.base != nullptr)
        base = std::make_shared<Base>(*a.base);
    else
        base = nullptr;
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

bool Point::operator<(Point const &a) const {
    return y<a.y || (y == a.y && x < a.x);
}


