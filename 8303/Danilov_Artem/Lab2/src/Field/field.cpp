//
// Created by kot on 25.02.2020.
//

//if bug first check  Field::Field(Field &&field)

#include "field.h"

MoveMediator::MoveMediator(Field * field, Unit * unit):
	field(field), fieldItem(unit)
	{
		this->field->setMoveMediator(this);
		this->fieldItem->setMoveMediator(this);
	}

void MoveMediator::movObj(Unit * item, int x, int y)
{
	field->moveUnit(item, x, y);
}

Field::Field(unsigned width, unsigned height, unsigned maxIt)
    :width(width), height(height), maxItems(maxIt),
    itemCounter(0), base(nullptr)
    {

    items = new FieldItem **[width];
    for (unsigned i = 0; i < width; i++) {
        items[i] = new FieldItem *[height];
        for (unsigned j = 0; j < height; j++) {
            items[i][j] = new FieldItem();
            auto k = (i+j)%2;
	        if (i%3 == 0 && j%3 == 0)
	            items[i][j]->setLandscape(new Forest());
	        else if (k  == 0)
		        items[i][j]->setLandscape(new River());
	        else
		        items[i][j]->setLandscape(new Desert());
        }
    }
}

Field::Field(const Field &field)
    :width(field.width), height(field.height), maxItems(field.maxItems),
	itemCounter(field.itemCounter), base(field.base) {

	items = new FieldItem **[width];
	for (unsigned i = 0; i < width; i++) {
		items[i] = new FieldItem *[height];
		for (unsigned j = 0; j < height; j++) {
			if (!field.items[i][j])
				items[i][j] = field.items[i][j];
			else
				items[i][j] = nullptr;
		}
	}
}

Field::Field(Field &&field)
		:width(field.width), height(field.height), maxItems(field.maxItems),
		 itemCounter(field.itemCounter), base(field.base) {
	items = new FieldItem **[width];
	for (unsigned i = 0; i < width; i++) {
		items[i] = new FieldItem *[height];
		for (unsigned j = 0; j < height; j++) {
			items[i][j] = field.items[i][j];
		}
	}
	field.~Field();

}

Field::~Field() {
	for (unsigned i = 0; i < width; i++){
		for (unsigned j = 0; j < height; j++)
			delete items[i][j];
		delete[] items[i];
	}
	if (items)
		delete[] items;
}

Field &Field::operator=(const Field &field) {
	if (&field == this)
		return *this;
	for (unsigned i = 0; i < width ; i++) {
		for (unsigned j = 0; j < height; j++)
			items[i][j];
		delete [] items[i];
	}
	delete [] items;
	items = new FieldItem**[width];

	for (unsigned i = 0; i < width; i++) {
		items[i] = new FieldItem*[height];
		for (unsigned j = 0; j< height; j++) {
			if (field.items[i][j] != nullptr) {
				items[i][j] = field.items[i][j];
				if (!items[i][j]->isUnitFree())
					new MoveMediator(this, items[i][j]->getUnit());
			} else {
				items[i][j] = nullptr;
			}
		}
	}

	delete base;
	base = field.base;
	return *this;
}

Field &Field::operator=(Field &&field) {
	if (&field == this)
		return *this;

	for (unsigned i = 0; i < width; i++){
		for (unsigned j = 0; j < height; j++)
			delete items[i][j];
		delete [] items[i];
	}
	delete [] items;

	items = field.items;
	itemCounter = field.itemCounter;
	for(unsigned i=0; i < width; i++)
		delete []  field.items[i];
	delete [] field.items;
	base = field.base;
	return *this;
}


unsigned Field::getWidth() const
{
    return  width;
}

unsigned Field::getHeight() const
{
    return  height;
}

unsigned Field::getItemCounter() const
{
    return itemCounter;
}

void Field::setMoveMediator(MoveMediator *value)
{
	moveMediator = value;
}

unsigned Field::getMaxItems () const {
	return maxItems;
}

bool Field::isCellFreeForUnit (size_t x, size_t y) {
	return items[x][y]->isUnitFree();
}


bool Field::moveUnit (Unit * item, int x, int y)  {
	for(auto i = 0; i < width; i++ )
		for(auto j = 0; j < height; j++ )
			if (items[i][j]->getUnit() == item)
			{
				if (x + i >= width ||
				    y + j >= height ||
				    x + i < 0 || y - j < 0)
					throw out_of_range("check position coordinates of unit");
				Proxy* p = new Proxy(items[x+i][y+j]->getLandscape());
				if (!p->canMove(item))
					throw invalid_argument("item can't move to this land");
				if(!item->isMovable())
					throw invalid_argument("item  must be movable");
				if(!items[x+i][y+j]->isUnitFree())
					throw invalid_argument("there is other unit on this cell ");
				if(items[x+i][y+j]->getNeutral())
				{
					*(items[x+i][y+j]->getNeutral()) += *(items[i][j]->getUnit());
					items[x+i][y+j]->delNeutral();
				}
				swap(items[x+i][y+j], items[i][j]);
				return true;
			}
	return false;
}

bool Field::addUnit (Unit *item, unsigned x, unsigned y, int baseNum) {
    if (itemCounter == maxItems)
        throw length_error("limit of field items is reached");
    if (x >= width || y >= height)
        throw out_of_range("coords are out of field");
    if (!item)
    	throw invalid_argument("item can't be empty");
    if (!items[x][y]->isUnitFree())
        throw std::invalid_argument("field cell is have unit");

    auto* p = new Proxy(items[x][y]->getLandscape());
	if (!p->canMove(item))
		throw invalid_argument("item  can't add to this landscape");
	//Base* base = (baseNum == 1) ? base;
	Base* bASE = base;
	if (!bASE)
		throw invalid_argument("create base!!!!");
	base->addUnit(item);
	items[x][y]->addUnit(item);
	items[x][y]->getUnit()->attach(this);
    itemCounter++;
    new MoveMediator(this, item);
    return true;

}

bool Field::deleteUnit(unsigned x, unsigned y) {
    if (x >= width || y >= height)
        throw out_of_range("coords are out of field");
    if (items[x][y]->isUnitFree())
        return false;
    if (base)
    	base->delUnit(items[x][y]->getUnit());

	items[x][y]->getUnit()->detach(this);
	items[x][y]->delUnit();
    itemCounter--;
    return true;
}

Base *Field::getBase () const {
	return base;
}

bool Field::addNeutral (NeutralObj * item, unsigned x, unsigned y) {
	if(x >= width || y >= height){
		throw out_of_range("check position coordinates of unit");
	}
	if(!item){
		throw invalid_argument("item can't be empty");
	}
	if(items[x][y]->getNeutral()){
		throw invalid_argument("this cell of field have unit");
	}
	items[x][y]->addNeutral(item);
	return true;
}

bool Field::deleteNeutral (unsigned x, unsigned y) {
	if(x >= width || y >= height){
		throw out_of_range("check coordinates for delete item");
	}
	if(!items[x][y]->getNeutral()){
		return false;
	}
	items[x][y]->delNeutral();
	return true;
}

FieldItem *Field::getCell (unsigned int x, unsigned int y) {
	if (x >= width || y >= height)
		throw out_of_range("coords are not on field");
	return items[x][y];
}

FieldItem *Field::findUnit (Unit *unit) {
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			if (items[i][j]->getUnit() == unit){
				return items[i][j];
			}
		}
	}
	return nullptr;
}

void Field::update (Subject * subject)
{
//	deleteUnit(subject);
}

//void Field::deleteUnit (Subject * unit)
//{
//	for (int i = 0; i < width; i++) {
//		for (int j = 0; j < height; j++) {
//			if (unit == items[i][j]->getUnit()) {
//				items[i][j]->delUnit();
//				itemCounter--;
//				if (base)
//					base->delUnit(unit);
////				if (base2)
////					base2->deleteUnit(unit);
//				unit->detach(this);
//				return;
//			}
//		}
//	}
//}

void Field::setBase (Base * base) {
	if(base->getMaxCount() <= 0)
		throw invalid_argument("maxCount must be >0");
	if(base->getHealth() <= 0)
		throw invalid_argument("health must be >0");
	if(base->getX() > width)
		throw invalid_argument("width must be < curr width");
	if(base->getY() > height)
		throw invalid_argument("height must be < curr height");
	if (base->getBaseNumb() == 1)
		this->base = new Base(base->getMaxCount(), base->getHealth(),
		         base->getX(), base->getY(), base->getBaseNumb());
	else throw invalid_argument("there is a base");

}

string Field::printBase (Base *base) {
	return base->printUnits();
}

string Field::getUnitMap () {
	std::string output = "";
	auto baseX = base->getX();
	auto baseY = base->getY();
	for (unsigned i=0; i<width; i++)
	{
		for (unsigned j=0; j<height; j++)
		{
			if( i == baseX && j == baseY)
				output += base->shortName() + "\t";
			else if (!items[i][j]->isUnitFree()) {
				auto tmp = items[i][j]->getUnit()->getName();
				output += items[i][j]->getUnit()->getName() + "\t";
			}else
				output += "empty\t";
		}
		output += "\n";
	}
	return output;
}

string Field::getNeutralMap()
{
	std::string output = "";
	auto baseX = base->getX();
	auto baseY = base->getY();
	for (unsigned i=0; i<width; i++)
	{
		for (unsigned j=0; j<height; j++)
		{
			if( i == baseX && j == baseY)
				output += base->shortName() + "\t";

			else if (items[i][j]->getNeutral())
				output += items[i][j]->getNeutral()-> characteristics() + "\t";
			else
				output += "empty\t";
		}
		output += "\n";
	}
	return output;
}

string Field::getLandMap () {
	std::string output = "";
	auto baseX = base->getX();
	auto baseY = base->getY();
	for (unsigned i=0; i<width; i++)
	{
		for (unsigned j=0; j<height; j++)
		{
			if( i == baseX && j == baseY) {
				output += base->shortName() + '\t';
			}

			else if (items[i][j]->getLandscape()) {
				auto *tmp = new Proxy(items[i][j]->getLandscape());
				output += tmp->getType() + "\t";
//				delete tmp;
			}
			else
				output += "empty\t";
		}
		output += "\n";
	}
	return output;
}

FieldItem *Field::getItem (unsigned int x, unsigned int y) const {
	if (x >= width || y >= height)
        throw std::out_of_range("coords are out of field");
    return items[x][y];
}

//std::string Field::getShortInfo() {
//	std::string output = "";
//	for (unsigned i=0; i<width; i++)
//	{
//		for (unsigned j=0; j<height; j++)
//		{
//			if (items[i][j] != nullptr)
//				output += items[i][j]->shortName() + "\t";
//			else
//				output += land[i][j]->getType() + "\t";
//		}
//		output += "\n";
//	}
//	return output;
//}






































//bool Field::deleteItem(FieldItem *item) {
//    for (unsigned i = 0; i < width; i++){
//        for (unsigned j = 0; j < height ; j++) {
//            if (items[i][j] == item){
//                delete items[i][j];
//                items[i][j] = nullptr;
//                itemCounter--;
//                return true;
//            }
//        }
//    }
//    throw  std::invalid_argument("there is no items like that");
//}

//FieldItem *Field::getItem(unsigned x, unsigned y) const
//{
//    if (x >= width || y >= height)
//        throw std::out_of_range("coords are out of field");
//    return items[x][y];
//}


//void Field::addLand(unsigned x, unsigned y, Proxy *landscape)
//{
//    land[x][y] = landscape;
//}


std::string Field::getAbout(unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": is out of field\n";
    if (items[x][y] == nullptr)
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": no item at this position\n";
    return "At X=" + std::to_string(x) + ",Y=" + std::to_string(y) + " is set:\n" + items[x][y]->getUnit()->about();
}



FieldIterator::FieldIterator(const Field *field)
    : active(true), field(field), curWidth(0), curHeight(0){
    if (field->getItem(curWidth, curHeight) == nullptr)
        this->operator++();
}

bool FieldIterator::isActive () const
{
    return active;
}

FieldItem *FieldIterator::operator->() const
{
    return field->getItem(curWidth, curHeight);
}

FieldItem *FieldIterator::operator++()
{
    do{
        if (curWidth + 1 == field->getWidth()){
            if (curHeight + 1 == field->getHeight()){
                active = false;
                return nullptr; //stop
            }
            curWidth = 0;
            curHeight++;
        }
        else
            curWidth++;
    } while (field->getItem(curWidth, curHeight) == nullptr);
    return  field->getItem(curWidth, curHeight);
}
