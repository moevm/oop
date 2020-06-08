//
// Created by therealyou on 11.02.2020.
//
/**
 * Игровое поле является контейнером для объектов представляющим прямоугольную сетку.
 * Основные требования к классу игрового поля:
 * Создание поля произвольного размера
 * Контроль максимального количества объектов на поле
 * Возможность добавления и удаления объектов на поле
 * Возможность копирования поля (включая объекты на нем)
 * Для хранения запрещается использовать контейнеры из stl
 * */

#include "GameField.h"


GameField::GameField(Adapter *adapter) :
        GameField(0, 0, adapter, 1) {}

GameField::GameField(int x, int y, Adapter *adapter, int mode) :
        width(x), height(y), maxCountUnits(x * y), gameField(this), adapter(adapter), gameMode(mode) {
    setMatrix();

}

GameField::GameField(const GameField &gameField) :
        width(gameField.width), height(gameField.height),
        maxCountUnits(maxCountUnits),
        countUnits(gameField.countUnits),
        gameField(this) {
    setMatrix(gameField.matrix);
}

GameField::GameField(GameField &&gameField) : width(gameField.width),
                                              height(gameField.height), matrix(nullptr),
                                              maxCountUnits(width * height), countUnits(0), adapter(gameField.adapter),
                                              base1(nullptr), base2(nullptr), base3(nullptr), unit1(nullptr),
                                              unit2(nullptr) {
    std::swap(matrix, gameField.matrix);
    std::swap(countUnits, gameField.countUnits);
    std::swap(base1, gameField.base1);
    std::swap(base2, gameField.base2);
    std::swap(base3, gameField.base3);
    std::swap(unit1, gameField.unit1);
    std::swap(unit2, gameField.unit2);

}

GameField &GameField::operator=(const GameField &gameField) {
    this->height = gameField.height;
    this->width = gameField.width;
    this->countUnits = gameField.countUnits;
    this->adapter = gameField.adapter;
    this->maxCountUnits = gameField.maxCountUnits;
    this->base1 = gameField.base1;
    this->base2 = gameField.base2;
    this->base3 = gameField.base3;
    this->unit1 = gameField.unit1;
    this->unit2 = gameField.unit2;
    this->unit3 = gameField.unit3;
    this->matrix = new Cell *[gameField.height];
    for (int i = 0; i < height; i++) {
        matrix[i] = new Cell[width];
        for (int j = 0; j < width; j++)
            matrix[i][j] = gameField.matrix[i][j];
    }
    return *this;
}

void GameField::setMatrix() {
    matrix = new Cell *[height];
    for (int i = 0; i < height; i++) {
        matrix[i] = new Cell[width];
    }
//    for (int i = 0; i < height; i++){
//        for (int j = 0; j < width; j++){
//            matrix[i][j].valueAsChar = DEFAULT_VALUE;
//        }
//    }
}

void GameField::setMatrix(Cell **matrix) {
    this->matrix = new Cell *[height];
    for (int i = 0; i < height; i++) {
        this->matrix[i] = new Cell[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->matrix[i][j].valueAsChar = matrix[i][j].valueAsChar;
            this->matrix[i][j].charLandscape = matrix[i][j].charLandscape;
            this->matrix[i][j].unit = matrix[i][j].unit;
            this->matrix[i][j].base = matrix[i][j].base;
            this->matrix[i][j].landscape = matrix[i][j].landscape;
            this->matrix[i][j].neutralObject = matrix[i][j].neutralObject;
        }
    }
}

int GameField::addUnit(Unit *unit, int x, int y) {
    if (!isCorrect(x, y)) {
        std::cerr << "\t\tWrong coords to add" << std::endl;
        return 1;
    }
    if (countUnits == maxCountUnits) {
        std::cerr << "\t\tHas reached total count of units" << std::endl;
        return 2;
    }
    if (!unit->isCanAdded()) {
        std::cerr << "\t\tThis unit has been added early" << std::endl;
        return 3;
    }
    if (matrix[y][x].valueAsChar != DEFAULT_VALUE) {
        std::cerr << "\t\tThis place is not free" << std::endl;
        return 4;
    }
    unit->addUnit();
    unit->setX(x);
    unit->setY(y);
    matrix[y][x].valueAsChar = unit->getCharType();
    unit->setId(++countUnits);
    matrix[y][x].unit = unit;
    adapter->setUnit(unit);
    return 0;
}

void GameField::deleteUnit(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        std::cerr << "\t\tWrong coords to delete" << std::endl;
        return;
    }
    if (matrix[y][x].valueAsChar != DEFAULT_VALUE) {
        matrix[y][x].valueAsChar = DEFAULT_VALUE;
        countUnits--;
        adapter->deleteUnit(matrix[y][x].unit);
        matrix[y][x].unit = nullptr;
    } else {
//        std::cerr << "\t\tThis place is free" << std::endl;
        return;
    }
}

void GameField::printField() const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << matrix[i][j].valueAsChar << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GameField::moveUnit(Unit *unit, int dx, int dy) {

    if (isCorrect(unit->getY() + dy, unit->getX() + dx) &&
        !matrix[unit->getY() + dy][unit->getX() + dx].unit) {
        unit->setX(unit->getX() + dx);
        unit->setY(unit->getY() + dy);
        matrix[unit->getY()][unit->getX()].unit =
                matrix[unit->getY() - dy][unit->getX() - dx].unit;
        matrix[unit->getY()][unit->getX()].valueAsChar =
                matrix[unit->getY() - dx][unit->getX() - dx].unit->getCharType();

        matrix[unit->getY() - dy][unit->getX() - dx].unit = nullptr;
        matrix[unit->getY() - dy][unit->getX() - dx].valueAsChar = DEFAULT_VALUE;
        adapter->move(unit);
    } else {
        throw LogicException("can't move at this position",
                             std::to_string(unit->getX() + dx) + " " +
                             std::to_string(unit->getY() + dy));
    }
}

int GameField::getWidth() const {
    return width;
}

int GameField::getHeight() const {
    return height;
}

GameField::GameFieldIterator GameField::begin() {
    return GameFieldIterator(0, 0, matrix,
                             height, width);
}

GameField::GameFieldIterator GameField::end() {
    return GameFieldIterator(height, 0, matrix,
                             height, width);
}


int GameField::createLandscape(Landscapes landscape, int x, int y) {
    if (!isCorrect(x, y)) {
        std::cerr << "\t\tWrong coords to set landscape" << std::endl;
        return 1;
    }
    switch (landscape) {
        case Landscapes::DESERT:
            matrix[y][x].landscape = new LandscapeProxy(new Desert());
            matrix[y][x].charLandscape = 'D';
            break;
        case Landscapes::WOOD:
            matrix[y][x].landscape = new LandscapeProxy(new Wood());
            matrix[y][x].charLandscape = 'W';
            break;
        case Landscapes::MOUNTAIN:
            matrix[y][x].landscape = new LandscapeProxy(new Mountain());
            matrix[y][x].charLandscape = 'M';
            break;
    }
    if (Unit *unit = matrix[y][x].unit) {
        unit->landscape = matrix[y][x].landscape;
    }
    return 0;
}

void GameField::printFieldLandscape() const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << matrix[i][j].charLandscape << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Base *GameField::createBase(int x, int y, int baseNumber, int maxCountUnits, int health) {
    if (!isCorrect(x, y)) {
        std::cerr << "\t\tWrong coords to set base" << std::endl;
        return nullptr;
    }
    matrix[y][x].base = new Base(gameField, x, y, baseNumber, maxCountUnits, health);
    matrix[y][x].valueAsChar = 'B';
    if (baseNumber == 1) {
        base1 = matrix[y][x].base;
    } else if (baseNumber == 2) {
        base2 = matrix[y][x].base;
    } else if (baseNumber == 3) {
        base3 = matrix[y][x].base;
    }
    adapter->setBase(matrix[y][x].base);
    return matrix[y][x].base;
}

bool GameField::isCorrect(int x, int y) {
    return x >= 0 && x < width &&
           y >= 0 && y < height;
}

bool GameField::canAdd(int x, int y) {
    if (!isCorrect(x, y)) {
        std::cerr << "\t\tWrong coords to add" << std::endl;
        return false;
    }
    if (countUnits == maxCountUnits) {
        std::cerr << "\t\tHas reached total count of units" << std::endl;
        return false;
    }
    if (matrix[y][x].valueAsChar != DEFAULT_VALUE) {
        std::cerr << "\t\tThis place is not free" << std::endl;
        return false;
    }
    return true;
}

void GameField::update(SubjectObserve *subjectObserve) {
    Unit *unit = (Unit *) subjectObserve;
    deleteUnit(unit->getX(), unit->getY());
}

SnapShot *GameField::makeSnapShot(const std::string &mode) {
    SnapShot *tmp;
    if (mode == "save") {
        tmp = new SnapShot(this, base1, base2, base3, unit1, unit2, unit3, adapter, gameMode);
    }
    if (mode == "load") {
        tmp = new SnapShot(this);
    }
    return tmp;
}

Object *GameField::createNeutralObject(ObjectsType type, int x, int y, int buffValue) {
    if (!isCorrect(x, y)) {
        std::cerr << "\t\tWrong coords to set neutral type" << std::endl;
        return nullptr;
    }
    if (matrix[y][x].neutralObject) {
        delete matrix[y][x].neutralObject;
    }
    switch (type) {
        case ObjectsType::ARMOR :
            matrix[y][x].neutralObject = new Armor(x, y, buffValue);
            matrix[y][x].charNeutralObject = 'A';
            break;
        case ObjectsType::MEDICINE :
            matrix[y][x].neutralObject = new Medicine(x, y, buffValue);
            matrix[y][x].charNeutralObject = 'M';
            break;
        case ObjectsType::POISON :
            matrix[y][x].neutralObject = new Poison(x, y, buffValue);
            matrix[y][x].charNeutralObject = 'P';
            break;
        case ObjectsType::WEAPON :
            matrix[y][x].neutralObject = new Weapon(x, y, buffValue);
            matrix[y][x].charNeutralObject = 'W';
            break;
    }
    return matrix[y][x].neutralObject;
}

void GameField::printFieldNeutralObject() const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << matrix[i][j].charNeutralObject << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Base *GameField::findBase(int baseId) {
    for (auto x : *gameField) {
        if (x.base) {
            if (x.base->baseNumber == baseId) {
                return x.base;
            }
        }
    }
    return nullptr;
}

Unit *GameField::findUnit(int unitId) {
    for (auto x : *gameField) {
        if (x.unit) {
            if (x.unit->profileUnit.id == unitId) {
                return x.unit;
            }
        }
    }
    return nullptr;
}

void GameField::attack(int x, int y, int attack) {
    if (matrix[y][x].unit) {
        adapter->attack(matrix[y][x].unit, attack);
        matrix[y][x].unit->getDamage(attack);
    }
    if (matrix[y][x].base) {
        matrix[y][x].base->getDamage(attack);
    }
}

void GameField::deleteBase(Base *base) {
    for (auto &cell : *this) {
        if (cell.base == base) {
            cell.valueAsChar = DEFAULT_VALUE;
            for (auto &unit : base->getUnits()) {
                this->deleteUnit(unit->getX(), unit->getY());
            }
            cell.base = nullptr;
        }
    }
}


GameField::GameFieldIterator::GameFieldIterator(const GameFieldIterator &it) :
        p(it.p),
        field(it.field),
        fieldWidth(it.fieldWidth),
        fieldHeight(it.fieldHeight) {

};

bool GameField::GameFieldIterator::operator!=(GameField::GameFieldIterator const &other) const {
    return x != other.x || y != other.y;
}

bool GameField::GameFieldIterator::operator==(const GameField::GameFieldIterator &other) const {
    return x == other.x && y == other.y;
}

typename GameField::GameFieldIterator::reference GameField::GameFieldIterator::operator*() const {
    return field[y][x];
}

GameField::GameFieldIterator &GameField::GameFieldIterator::operator++() {
    x++;
    if (x < fieldWidth) {
        p = field[y][x];
        return *this;
    }
    x = 0;
    y++;
    return *this;

}


GameField::GameFieldIterator::GameFieldIterator(int height, int width, Cell **field, const int fieldHeight,
                                                const int fieldWidth) :
        y(height),
        x(width),
        field(field),
        fieldHeight(fieldHeight),
        fieldWidth(fieldWidth) {

}
