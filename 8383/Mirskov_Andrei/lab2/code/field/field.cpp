//
// Created by andrei on 19.02.2020.
//

#include "field.h"

Field::Field(int sizeX, int sizeY, int base1x, int base1y, int base2x, int base2y) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;

    this->base1 = new Base(base1x, base1y);
    this->base2 = new Base(base2x, base2y);

    for (int y = 0; y < sizeY; y++) {
        this->picture.push(Vector<char>());
        for (int x = 0; x < sizeX; x++) {
            this->picture[y].push('O');
        }
    }

    for (int y = 0; y < sizeY; y++) {
        this->cells.push(Vector<Landscape*>());
        for (int x = 0; x < sizeX; x++) {
            switch ((x+y) % 3) {
                case 0:
                    this->cells[y].push(new Ground);
                    break;
                case 1:
                    this->cells[y].push(new Liquid);
                    break;
                case 2:
                    this->cells[y].push(new Wall);
                    break;
            }
        }
    }

    this->picture[base1y][base1x] = '1';
    this->picture[base2y][base2x] = '2';
}

Field::Field(Field &field) {
    this->sizeX = field.sizeX;
    this->sizeY = field.sizeY;

    for (int y = 0; y < this->sizeY; y++) {
        this->picture.push(Vector<char>());
        for (int x = 0; x < this->sizeX; x++) {
            this->picture[y][x] = field.picture[y][x];
        }
    }

    this->base1 = field.base1;
    this->base2 = field.base2;
}

Field& Field::operator=(Field & field) {
    if (&field == this) {
        return *this;
    }

    this->sizeX = field.sizeX;
    this->sizeY = field.sizeY;

    for (int y = 0; y < this->sizeY; y++) {
        this->picture.push(Vector<char>());
        for (int x = 0; x < this->sizeX; x++) {
            this->picture[y][x] = field.picture[y][x];
        }
    }

    this->base1 = field.base1;
    this->base2 = field.base2;
    return *this;
}

Field::Field(Field &&field) noexcept{
    std::swap(field.sizeX, this->sizeX);
    std::swap(field.sizeY, this->sizeY);
    std::swap(field.base1, this->base1);
    std::swap(field.base2, this->base2);
    std::swap(field.picture, this->picture);
}

Field& Field::operator=(Field&& field) noexcept {
    if (&field == this) {
        return *this;
    }

    std::swap(field.sizeX, this->sizeX);
    std::swap(field.sizeY, this->sizeY);
    std::swap(field.base1, this->base1);
    std::swap(field.base2, this->base2);
    std::swap(field.picture, this->picture);

    return *this;
}

void Field::addUnit(int x, int y, char type, int playerNum) {
    if (playerNum == 1) {
        base1->addUnit(x, y, type);
        if (this->cells[y][x]->getType() == 'l')
            this->base1->getUnit(x, y)->setDamage(this->base1->getUnit(x, y)->getDamage() - 1);
    }
    else {
        base2->addUnit(x, y, type);
        if (this->cells[y][x]->getType() == 'l')
            this->base2->getUnit(x, y)->setDamage(this->base2->getUnit(x, y)->getDamage() - 1);
    }
    this->picture[y][x] = type;
}

void Field::removeUnit(int x, int y) {
    base1->removeUnit(x, y);
    base2->removeUnit(x, y);
    this->picture[y][x] = 'O';
}

void Field::moveUnit(int x1, int y1, int x2, int y2, int playerNum) {
    if (this->cells[y2][x2]->getType() == 'w')
        return;
    if (this->cells[y2][x2]->getType() == 'l') {
        if (this->cells[y1][x1]->getType() != 'l') {
            Unit *unit;
            if (playerNum == 1)
                unit = this->base1->getUnit(x1, y1);
            else
                unit = this->base2->getUnit(x1, y1);
            unit->setDamage(unit->getDamage() - 1);
        }
    }
    else {
        if (this->cells[y1][x1]->getType() == 'l') {
            Unit *unit;
            if (playerNum == 1)
                unit = this->base1->getUnit(x1, y1);
            else
                unit = this->base2->getUnit(x1, y1);
            unit->setDamage(unit->getDamage() + 1);
        }
    }

    if (isNeutral(x2, y2)) {
        this->takeItem(x1, y1, x2, y2, playerNum);
    }

    if (isUnit(x2, y2)) {
        this->attack(x1, y1, x2, y2, playerNum);
        return;
    }

    if (playerNum == 1)
        base1->moveUnit(x1, y1, x2, y2);
    else
        base2->moveUnit(x1, y1, x2, y2);

    char type = this->picture[y1][x1];
    this->picture[y1][x1] = 'O';
    this->picture[y2][x2] = type;
}

void Field::printField() {
    for (int y = 0; y < this->sizeY; y++) {
        for (int x = 0; x < this->sizeX; x++) {
            cout << "\033[0;3" << this->cells[y][x]->getType()%3 << "m" << this->picture[y][x];
        }
        cout << '\n';
    }
    cout << '\n';
}

void Field::addNeutral(int x, int y, char type) {
    this->neutrals.push(Factory::createNeutral(x, y, type));
    this->picture[y][x] = type;
}

void Field::removeNeutral(int x, int y) {
    for (int i = 0; i < this->neutrals.getSize(); i++) {
        if (this->neutrals[i]->getX() == x && this->neutrals[i]->getY() == y) {
            this->neutrals.remove(i);
        }
    }
    this->picture[y][x] = 'O';
}

bool Field::isNeutral(int x, int y) {
    for (int i = 0; i < this->neutrals.getSize(); i++) {
        if (this->neutrals[i]->getX() == x && this->neutrals[i]->getY() == y) return true;
    }
    return false;
}

void Field::takeItem(int x1, int y1, int x2, int y2, int playerNum) {
    Neutral* neutral;
    for (int i = 0; i < this->neutrals.getSize(); i++) {
        if (this->neutrals[i]->getX() == x2 && this->neutrals[i]->getY() == y2) {
            neutral = this->neutrals[i];
            break;
        }
    }

    if (playerNum == 1) {
        base1->takeItem(x1,y1,neutral);
    }
    else {
        base2->takeItem(x1,y1,neutral);
    }
    this->removeNeutral(x2, y2);
}

bool Field::isUnit(int x, int y) {
    return this->base1->isUnit(x, y) || this->base2->isUnit(x, y);
}

void Field::attack(int x1, int y1, int x2, int y2, int playerNum) {
    Unit* unit1;
    Unit* unit2;
    if (playerNum == 1) {
        unit1 = this->base1->getUnit(x1, y1);
        unit2 = this->base2->getUnit(x2, y2);
    }
    else {
        unit1 = this->base2->getUnit(x1, y1);
        unit2 = this->base1->getUnit(x2, y2);
    }

    bool isDie1 = unit1->takeDamage(unit2->getDamage());
    bool isDie2 = unit2->takeDamage(unit1->getDamage());

    if (isDie1) {
        this->removeUnit(x1, y1);
    }

    if (isDie2) {
        this->removeUnit(x2, y2);
        if (!isDie1) {
            this->moveUnit(x1, y1, x2, y2, playerNum);
        }
    }
}

