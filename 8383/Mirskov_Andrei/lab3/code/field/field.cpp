//
// Created by andrei on 19.02.2020.
//

#include "field.h"

Field::Field(int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    for (int y = 0; y < sizeY; y++) {
        this->cells.push(Vector<Cell*>());
        for (int x = 0; x < sizeX; x++) {
            this->cells[y].push(new Cell());
        }
    }
}

Field::Field(Field &field) {
    this->sizeX = field.sizeX;
    this->sizeY = field.sizeY;

    for (int y = 0; y < this->sizeY; y++) {
        this->cells.push(Vector<Cell*>());
        for (int x = 0; x < this->sizeX; x++) {
            this->cells[y][x] = field.cells[y][x];
        }
    }
}

Field& Field::operator=(Field & field) {
    if (&field == this) {
        return *this;
    }

    this->sizeX = field.sizeX;
    this->sizeY = field.sizeY;

    for (int y = 0; y < this->sizeY; y++) {
        this->cells.push(Vector<Cell*>());
        for (int x = 0; x < this->sizeX; x++) {
            this->cells[y][x] = field.cells[y][x];
        }
    }

    this->cells = field.cells;
    return *this;
}

Field::Field(Field &&field) noexcept{
    std::swap(field.sizeX, this->sizeX);
    std::swap(field.sizeY, this->sizeY);
    std::swap(field.cells, this->cells);
}

Field& Field::operator=(Field&& field) noexcept {
    if (&field == this) {
        return *this;
    }

    std::swap(field.sizeX, this->sizeX);
    std::swap(field.sizeY, this->sizeY);
    std::swap(field.cells, this->cells);

    return *this;
}

Cell *Field::getCell(int x, int y) {
    return this->cells[y][x];
}

void Field::printField() {
    for (int y = 0; y < this->sizeY; y++) {
        for (int x = 0; x < this->sizeX; x++) {
            if (this->cells[y][x]->isUnit())
                cout << this->cells[y][x]->getUnit()->getType();
            else if (this->cells[y][x]->isNeutral())
                cout << this->cells[y][x]->getNeutral()->getType();
            else if (this->cells[y][x]->isBase()) {
                cout << "B";
            }
            else {
                cout << "O";
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

Base *Field::getBase(int ind) {
    return this->bases[ind-1];
}

void Field::addBase(int x, int y) {
    Base* newBase;
    if (this->bases.getSize() == 0)
        newBase = new Base(1);
    else
        newBase = new Base(this->bases[this->bases.getSize()-1]->getNum()+1);

    this->bases.push(newBase);
    this->getCell(x,y)->setBase(newBase);
}

int Field::baseCount() {
    return this->bases.getSize();
}



