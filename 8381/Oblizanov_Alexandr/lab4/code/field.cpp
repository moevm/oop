#include "field.h"

MoveMediator::MoveMediator(Field *field, FieldItem *item)
    : field(field), item(item)
{
    this->field->setMoveMediator(this);
    this->item->setMoveMediator(this);
}

void MoveMediator::Notify(IUnit *sender, int x, int y)
{
    field->moveItem(sender, x, y);
}

Field::Field(unsigned width, unsigned height, unsigned itemLimit, LandType basicLand)
    :width(width), height(height), itemLimit(itemLimit), itemCounter(0)
{
    landscapes = new FieldLandscape**[width];
    items = new FieldItem**[width];
    for (unsigned i=0; i<width; i++)
    {
        landscapes[i] = new FieldLandscape*[height];
        items[i] = new FieldItem*[height];
        for (unsigned j=0; j<height; j++)
        {
            items[i][j] = nullptr;
            landscapes[i][j] = new ProxyLandscape(basicLand);
        }
    }
}

Field::Field(const Field &field)
    :width(field.width), height(field.height), itemLimit(field.itemLimit), itemCounter(field.itemCounter)
{
    items = new FieldItem**[width];
    landscapes = new FieldLandscape**[width];
    for (unsigned i=0; i<width; i++)
    {
        items[i] = new FieldItem*[height];
        landscapes[i] = new FieldLandscape*[height];
        for (unsigned j=0; j<height; j++)
        {
            items[i][j] = nullptr;
            landscapes[i][j] = nullptr;
        }
    }
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
        {
            if (field.items[i][j] != nullptr)
            {
                items[i][j] = field.items[i][j]->itemCopy();
                new MoveMediator(this, items[i][j]);
            }
            landscapes[i][j] = field.landscapes[i][j]->landCopy();
        }
    }
}

Field::Field(Field &&field)
    :width(field.width), height(field.height),  items(field.items), landscapes(field.landscapes), itemLimit(field.itemLimit), itemCounter(field.itemCounter)
{
    field.landscapes = nullptr;
    field.items = nullptr;
    field.width = 0;
    field.height = 0;
}

Field::~Field()
{
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
            deleteItem(i, j);
        delete [] items[i];
    }
    if (items)
        delete [] items;
}

bool Field::addItem(unsigned x, unsigned y, FieldItem *item)
{
    if (itemCounter == itemLimit)
        throw std::length_error("field items limit reached");
    if (x >= width || y >= height)
        throw std::out_of_range("coords are not on field");
    if (items[x][y] != nullptr)
        throw std::invalid_argument("field cell is busy");
    items[x][y] = item;
    new MoveMediator(this, item);
    itemCounter++;
    return true;
}

bool Field::addLandscape(unsigned x, unsigned y, FieldLandscape *landscape)
{
    if (x >= width || y >= height)
        throw std::out_of_range("coords are not on field");
    if (landscapes[x][y] != nullptr)
        delete landscapes[x][y];
    landscapes[x][y] = landscape;
    return true;
}

bool Field::addBaseUnit(unsigned x, unsigned y, FieldItem *base, FieldItem *unit)
{
    int iwidth = static_cast<int>(width);
    int iheight = static_cast<int>(height);
    for (int i=0; i<iwidth; i++)
    {
        for(int j=0; j<iheight; j++)
        {
            if (items[i][j] == base)
            {
                if (std::abs(static_cast<int>(x)-i) <= 1 && std::abs(static_cast<int>(y)-j) <= 1)
                {
                    addItem(x, y, unit);
                    return true;
                }
                else
                    throw std::invalid_argument("wrong unit coords, should be near base");
            }
        }
    }
    throw std::invalid_argument("no base on field");
}

bool Field::deleteItem(unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        throw std::out_of_range("coords are not on field");
    if (items[x][y] == nullptr)
        throw std::invalid_argument("no item at this position");
    delete items[x][y];
    items[x][y] = nullptr;
    itemCounter--;
    return true;
}

bool Field::deleteItem(FieldItem *item)
{
    for (unsigned i=0; i<width; i++)
        for (unsigned j=0; j<height; j++)
        {
            if (items[i][j] == item)
            {
                delete items[i][j];
                items[i][j] = nullptr;
                itemCounter--;
                return true;
            }
        }
    throw std::invalid_argument("no such item on field");
}

FieldItem *Field::getItem(unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        throw std::out_of_range("coords are not on field");
    return items[x][y];
}

bool Field::moveItem(IUnit *item, int x, int y)
{
    int iwidth = static_cast<int>(width);
    int iheight = static_cast<int>(height);
    for (int i=0; i<iwidth; i++)
        for (int j=0; j<iheight; j++)
        {
            if (items[i][j] == item)
            {
                if (x+i >= iwidth || y+j >= iheight || x+i < 0 || y+j < 0)
                    throw std::out_of_range("coords are not on field");
                if (item->isMovable() == 0)
                    throw std::invalid_argument("Item is not movable");
                if (items[x+i][y+j] != nullptr && items[x+i][y+j]->getType()<CHEST)
                    throw std::invalid_argument("field cell is busy");
                landscapes[x+i][y+j]->unitInfluence(item);
                if (items[x+i][y+j] != nullptr)
                {
                    if (items[x+i][y+j]->getType()>=CHEST)
                    {
                        *item += items[x+i][y+j];
                        delete items[x+i][y+j];
                        items[x+i][y+j] = nullptr;
                    }
                }
                std::swap(items[x+i][y+j], items[i][j]);
                return true;
            }
        }
    throw std::invalid_argument("no such item on field");
}

std::string Field::getAbout(unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": is out of field\n";
    if (items[x][y] == nullptr)
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + " with landscape " + landscapes[x][y]->shortName() + std::to_string(y) + ": no item at this position\n";
    return "At X=" + std::to_string(x) + ",Y=" + std::to_string(y) + " with landscape " + landscapes[x][y]->shortName() + " is set:\n" + items[x][y]->about();
}

LandType Field::getLandType(unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        throw std::out_of_range("coords are not on field");
    return landscapes[x][y]->getType();
}

std::string Field::getShortInfo()
{
    std::string output = "";
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
        {
            if (items[i][j] != nullptr)
                output += items[i][j]->shortName() + "\t";
            else
                output += "empty\t";
        }
        output += "\n";
    }
    return output;
}

Field &Field::operator=(const Field &field)
{
    if (&field == this)
        return *this;
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
            deleteItem(i, j);
        delete [] items[i];
    }
    delete [] items;
    items = new FieldItem**[width];
    landscapes = new FieldLandscape**[width];
    for (unsigned i=0; i<width; i++)
    {
        items[i] = new FieldItem*[height];
        landscapes[i] = new FieldLandscape*[height];
        for (unsigned j=0; j<height; j++)
        {
            items[i][j] = nullptr;
            landscapes[i][j] = nullptr;
        }
    }
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
        {
            if (field.items[i][j] != nullptr)
            {
                items[i][j] = field.items[i][j]->itemCopy();
                new MoveMediator(this, items[i][j]);
            }
            landscapes[i][j] = field.landscapes[i][j]->landCopy();
        }
    }
    return *this;
}

Field &Field::operator=(Field &&field)
{
    if (&field == this)
        return *this;
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
            deleteItem(i, j);
        delete [] items[i];
    }
    std::swap(items, field.items);
    std::swap(landscapes, field.landscapes);
    return *this;
}

//GETTERS/SETTERS

void Field::setCreateMediator(ICreateMediator *value)
{
    createMediator = value;
}

void Field::setMoveMediator(MoveMediator *value)
{
    moveMediator = value;
}

unsigned Field::getWidth() const
{
    return width;
}

unsigned Field::getHeight() const
{
    return height;
}


unsigned Field::getItemLimit() const
{
    return itemLimit;
}

void Field::setItemLimit(const unsigned &value)
{
    itemLimit = value;
}

unsigned Field::getItemCounter() const
{
    return itemCounter;
}

FieldIterator::FieldIterator(Field *field)
    : active(true), field(field), curWidth(0), curHeight(0) {
    if (field->getItem(curWidth, curHeight) == nullptr)
        this->operator++();
}

bool FieldIterator::isActive()
{
    return active;
}

FieldItem *FieldIterator::operator->()
{
    return field->getItem(curWidth, curHeight);
}

FieldItem *FieldIterator::operator++()
{
    do {
        if (curWidth+1 == field->getWidth())
        {
            if (curHeight+1 == field->getHeight())
            {
                active = false;
                return nullptr;
            }
            curWidth = 0;
            curHeight++;
        }
        else
            curWidth++;
    } while (field->getItem(curWidth, curHeight) == nullptr);
    return field->getItem(curWidth, curHeight);
}

unsigned FieldIterator::getCurWidth() const
{
    return curWidth;
}

unsigned FieldIterator::getCurHeight() const
{
    return curHeight;
}
