//
// Created by kot on 25.02.2020.
//
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
    for (unsigned i = 0; i < width; i++){
        for (unsigned j = 0; j < height; j++) {
            if (field.items[i][j] != nullptr){
                items[i][j] = field.items[i][j]->itemCopy();
                // page 6
            }
        }
    }

}

Field::Field(Field &&field)
    :width(field.width), height(field.height), itemLimit(field.itemLimit),
itemCounter(field.itemCounter){
    field.items = nullptr;
    field.width = 0;
    field.height = 0;
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
    // page 6
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

FieldItem *Field::getItem(unsigned x, unsigned y){
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
                //page 6
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

std::string Field::getShortInfo() {
    std::string output = "";
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
        {
            if (items[i][j] != nullptr)
                output += items[i][j]->shortName() + "\t";
            else
                output += "*****\t";
        }
        output += "\n";
    }
    return output;
}

bool Field::moveItem(FieldItem *item, int x, int y) {
    int iwidth = static_cast<int>(width);
    int iheight = static_cast<int>(height);
    for (int i=0; i<iwidth; i++)
        for (int j=0; j<iheight; j++)
        {
            if (items[i][j] == item)
            {
                if (x+i >= iwidth || y+j >= iheight || x+i < 0 || y+j < 0)
                    return false;
                if (items[x+i][y+j] != nullptr || item->isMovable() == 0)
                    return false;
                items[x+i][y+j] = items[i][j];
                items[i][j] = nullptr;
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
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": no item at this position\n";
    return "At X=" + std::to_string(x) + ",Y=" + std::to_string(y) + " is set:\n" + items[x][y]->about();
}

void Field::setItemLimit(const unsigned &value) {
    itemLimit = value;
}

FieldIterator::FieldIterator(Field *field)
    : active(true), field(field), curWidth(0), curHeight(0){
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
