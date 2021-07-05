//
// Created by kot on 25.02.2020.
//

//if bug first check  Field::Field(Field &&field)

#include "field.h"

Field::Field(unsigned width, unsigned height, unsigned itemLimit)
    :width(width), height(height), itemLimit(itemLimit), itemCounter(0) {

    items = new FieldItem **[width];
    for (unsigned i = 0; i < width; i++) {
        items[i] = new FieldItem *[height];
        for (unsigned j = 0; j < height; j++) {
            items[i][j] = nullptr;
        }
    }
    land = new Proxy **[width];
    for (unsigned i = 0; i < width; i++) {
        land[i] = new Proxy *[height];
        for (unsigned j = 0; j < height; j++) {
            land[i][j] = nullptr;
        }
    }
}

Field::Field(const Field &field)
    :width(field.width), height(field.height), itemLimit(field.itemLimit),
itemCounter(field.itemCounter){

    items = new FieldItem **[width];
    for (unsigned i = 0; i < width; i++) {
        items[i] = new FieldItem *[height];
        for (unsigned j = 0; j < height; j++) {
            items[i][j] = nullptr;
        }
    }
//    land = new Proxy **[width];
//    for (unsigned i = 0; i < width; i++) {
//        land[i] = new Proxy *[height];
//        for (unsigned j = 0; j < height; j++) {
//            land[i][j] = nullptr;
//        }
//    }


    for (unsigned i = 0; i < width; i++){
        for (unsigned j = 0; j < height; j++) {
            if (field.items[i][j] != nullptr){
                items[i][j] = field.items[i][j]->itemCopy();
//                land[i][j] = field.land[i][j];
                new MoveMediator(this, items[i][j]);
            }
        }
    }

}

Field::Field(Field &&field)
    :width(field.width), height(field.height), itemLimit(field.itemLimit),
itemCounter(field.itemCounter){
    field.~Field();
//    field.items = nullptr;
//    field.width = 0;
//    field.height = 0;
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

Field::~Field() {
    for (unsigned i = 0; i < width; i++){
        for (unsigned j = 0; j < height; j++)
            deleteItem(i,j);
        delete[] items[i];
    }
    if (items)
        delete[] items;
}

bool Field::addItem(unsigned x, unsigned y, FieldItem *item) {
    if (itemCounter == itemLimit)
        throw std::length_error("limit of field items is reached");
    if (x >= width || y >= height)
        throw std::out_of_range("coords are out of field");
    if (items[x][y] != nullptr)
        throw std::invalid_argument("field cell is busy");
    items[x][y] = item;
    new MoveMediator(this, items[x][y]);
    itemCounter++;
    return true;

}

bool Field::deleteItem(unsigned x, unsigned y) {
    if (x >= width || y >= height)
        throw std::out_of_range("coords are out of field");
    if (items[x][y] == nullptr)
        return false;
    delete items[x][y];
    items[x][y] = nullptr;
    itemCounter--;
    return true;
}

bool Field::deleteItem(FieldItem *item) {
    for (unsigned i = 0; i < width; i++){
        for (unsigned j = 0; j < height ; j++) {
            if (items[i][j] == item){
                delete items[i][j];
                items[i][j] = nullptr;
                itemCounter--;
                return true;
            }
        }
    }
    throw  std::invalid_argument("there is no items like that");
}

FieldItem *Field::getItem(unsigned x, unsigned y) const
{
    if (x >= width || y >= height)
        throw std::out_of_range("coords are out of field");
    return items[x][y];
}

Field &Field::operator=(const Field &field) {
    if (&field == this)
        return *this;
    for (unsigned i = 0; i < width ; i++) {
        for (unsigned j = 0; j < height; j++)
            deleteItem(i, j);
        delete [] items[i];
    }
    delete [] items;
    items = new FieldItem**[width];
    for (unsigned i = 0; i < width; i++) {
        items[i] = new FieldItem*[height];
        for (unsigned j = 0; j< height; j++)
            items[i][j] = nullptr;
    }
    for (unsigned i=0; i<width; i++){
        for (unsigned j=0; j<height; j++){
            if (field.items[i][j] != nullptr){
                items[i][j] = field.items[i][j]->itemCopy();
                 new MoveMediator(this, items[i][j]);
            }
        }
    }
    return *this;
}

Field &Field::operator=(Field &&field) {
    if (&field == this)
        return *this;
    for (unsigned i = 0; i < width; i++){
        for (unsigned j = 0; j < height; j++)
            deleteItem(i, j);
        delete [] items[i];
    }
    items = new FieldItem**[width];
    for (unsigned i = 0; i < width; i++){
        items[i] = new FieldItem*[height];
        for (unsigned j = 0; j < height; j++)
        {
            items[i][j] = field.items[i][j];
            field.items[i][j] = nullptr;
        }
    }
    return *this;
}

void Field::addLand(unsigned x, unsigned y, Proxy *landscape)
{
    land[x][y] = landscape;
}

std::string Field::getShortInfo() {
    std::string output = "";
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
        {
            if (items[i][j] != nullptr)
                output += items[i][j]->shortName() + "\t";
            else
                output += land[i][j]->getType() + "\t";
        }
        output += "\n";
    }
    return output;
}

bool Field::moveItem(FieldItem *item, int x, int y) {
    //fix
    int iwidth = static_cast<int>(width);
    int iheight = static_cast<int>(height);
    for (int i=0; i<iwidth; i++)
        for (int j=0; j<iheight; j++)
        {
            if (items[i][j] == item)
            {
                if (x+i >= iwidth || y+j >= iheight || x+i < 0 || y+j < 0)
                    return false;
                if (items[x+i][y+j] != nullptr || item->isMovable() == 0){
                    std::cout << "this field is buzy\n";
                    return false;
                }
                if(land[x+i][y+j]->checkMoveAccess(items[i][j]->shortName()))
                {
                    items[x+i][y+j] = items[i][j];
                    items[i][j] = nullptr;
                    return true;
                }
                else return false;
            }
        }
    throw std::invalid_argument("no such item on field");
}

std::string Field::getAbout(unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": is out of field\n";
    if (items[x][y] == nullptr)
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": no item at this position\n";
    return "At X=" + std::to_string(x) + ",Y=" + std::to_string(y) + " is set:\n" + items[x][y]->about();
}

//void Field::setItemLimit(const unsigned &value) {
//    itemLimit = value;
//}

void Field::setMoveMediator(MoveMediator *value)
{
    moveMediator = value;
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

MoveMediator::MoveMediator(Field *field, FieldItem *item)
    :field(field), item(item){
    this->field->setMoveMediator(this);
    this->item->setMoveMediator(this);
}

void MoveMediator::notify(FieldItem *sender, int x, int y)
{
    field->moveItem(sender, x, y);
}
