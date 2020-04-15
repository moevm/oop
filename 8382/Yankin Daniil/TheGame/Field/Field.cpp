#include "Field.h"
#include "Game/Game.h"
#include "Landscape/LandscapeHeader.h"
#include "Unit/UnitHeader.h"


Field::Field(uint16_t width, uint16_t height, uint8_t landscapeType) : unitCount(0), maxUnitCoint(200) {
    if (width >= 40 && height >= 40) {
        this->width = width;
        this->height = height;
    }
    else {
        this->width = 30;
        this->height = 30;
    }

    if (landscapeType < LAND_WATER && landscapeType > LAND_FOREST_HILL) {
        landscapeType = LAND_PLAIN;
    }

    LandscapeFactory landscapeFactory;

    cellArray = new Cell*[this->height];
    for (uint16_t i = 0; i < this->height; i++) {
        cellArray[i] = new Cell[this->width];
        for (uint16_t j = 0; j < this->height; j++) {
            cellArray[i][j] = Cell(Point(j, i), landscapeFactory.produce(landscapeType, Point(j, i)));
        }
    }
}

Field::Field(std::ifstream& stream) : maxUnitCoint(200) {
    cellArray = nullptr;
    stream >> width >> height;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool correctInput = true;
    if (width < 40 || height < 40) {
        correctInput = false;
    }

    LandscapeFactory landscapeFactory;


    if (correctInput) {
        cellArray = new Cell*[height];
        for (uint16_t i = 0; i < height; i++) {
            cellArray[i] = new Cell[width];
        }

        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                uint16_t landType;
                stream >> landType;

                if (!stream) {
                    goto incorrectInput;
                }
                if (landType < LAND_WATER || landType > LAND_FOREST_HILL) {
                    landType = LAND_PLAIN;
                }

                cellArray[i][j] = Cell(Point(j, i), landscapeFactory.produce(landType, Point(j, i)));
            }
        }
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    else {
        incorrectInput:

        if (cellArray != nullptr) {
            for (uint i = 0; i < height; i++) {
                delete[] cellArray[i];
            }
            delete[] cellArray;
            cellArray = nullptr;
        }

        width = 30;
        height = 30;
        cellArray = new Cell*[height];
        for (uint16_t i = 0; i < height; i++) {
            cellArray[i] = new Cell[width];
        }

        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                cellArray[i][j] = Cell(Point(j, i), landscapeFactory.produce(LAND_PLAIN, Point(j, i)));
            }
        }
    }
}

Field::~Field() {
    for (uint16_t i = 0; i < height; i++) {
        delete [] cellArray[i];
    }
    delete [] cellArray;
}


Field::Field(const Field &field) {
    width = field.width;
    height = field.height;
    cellArray = new Cell*[height];
    for (uint16_t i = 0; i < height; i++) {
        cellArray[i] = new Cell[width];
    }

    LandscapeFactory factory;
    Point point(0, 0);

    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            point = Point(j, i);
            uint8_t landType = field.cellArray[i][j].getLandscape()->getObjectType();

            cellArray[i][j] = Cell(Point(j, i), factory.produce(landType, point));

            cellArray[i][j].setUnit(field.cellArray[i][j].getUnit());

            uint8_t buildingType = field.cellArray[i][j].getBuildingGroupType();
            if (buildingType == BASE)
                cellArray[i][j].setBase(field.cellArray[i][j].getBase());
            else if (buildingType == NEUT_OBJECT)
                cellArray[i][j].setContext(field.cellArray[i][j].getContext());
        }
    }
}

Field& Field::operator=(Field &field) {
    if (&field == this) return *this;

    for (uint16_t i = 0; i < height; i++) {
        delete [] cellArray[i];
    }
    delete [] cellArray;

    width = field.width;
    height = field.height;
    cellArray = new Cell*[height];
    for (uint16_t i = 0; i < height; i++) {
        cellArray[i] = new Cell[width];
    }

    LandscapeFactory factory;
    Point point(0, 0);

    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            point = Point(j, i);
            uint8_t landType = field.cellArray[i][j].getLandscape()->getObjectType();

            cellArray[i][j] = Cell(Point(j, i), factory.produce(landType, point));

            cellArray[i][j].setUnit(field.cellArray[i][j].getUnit());

            uint8_t buildingType = field.cellArray[i][j].getBuildingGroupType();
            if (buildingType == BASE)
                cellArray[i][j].setBase(field.cellArray[i][j].getBase());
            else if (buildingType == NEUT_OBJECT)
                cellArray[i][j].setContext(field.cellArray[i][j].getContext());
        }
    }

    return *this;
}

Field::Field(Field &&field) {
    width = field.width;
    height = field.height;
    cellArray = field.cellArray;

    field.cellArray = nullptr;
}

Field& Field::operator=(Field &&field) {
    if (&field == this) return *this;

    for (uint16_t i = 0; i < height; i++) {
        delete [] cellArray[i];
    }
    delete [] cellArray;

    width = field.width;
    height = field.height;
    cellArray = field.cellArray;

    return *this;
}




uint16_t Field::getWidth() {
    return width;
}

uint16_t Field::getHeight() {
    return height;
}

Cell* Field::getCell(Point point) {
    if (point.getX() >= width || point.getY() >= height)
        return nullptr;
    return &(cellArray[point.getY()][point.getX()]);
}



ILandscape* Field::getLandscape(Point point) {
    return cellArray[point.getY()][point.getX()].getLandscape();
}


void Field::setUnit(Point point, IUnit* unit){
    if (!getCell(point)->isUnitFree())
        return;

    getCell(point)->setUnit(unit);
    unitCount++;
}

IUnit* Field::getUnit(Point point) {
    return getCell(point)->getUnit();
}

void Field::removeUnit(Point point) {
    if (getCell(point)->isUnitFree())
        return;

    getCell(point)->removeUnit();
    unitCount--;
}


void Field::setBase(Point point, Base* base) {
    if (!getCell(point)->isBuildingFree())
        return;

    getCell(point)->setBase(base);
}

Base* Field::getBase(Point point) {
    return getCell(point)->getBase();
}

void Field::removeBase(Point point) {
    if (getCell(point)->getBuildingGroupType() != BASE)
        return;

    getCell(point)->removeBase();
}


void Field::setContext(Point point, NeutralContext* context) {
    if (!getCell(point)->isBuildingFree())
        return;

    getCell(point)->setContext(context);
}

NeutralContext* Field::getContext(Point point) {
    return getCell(point)->getContext();
}


bool Field::isUnitFree(Point point) {
    return getCell(point)->isUnitFree();
}

bool Field::isBuildingFree(Point point) {
    return getCell(point)->isBuildingFree();
}


uint8_t Field::getBuildingGroupType(Point point) {
    return getCell(point)->getBuildingGroupType();
}



bool Field::isBelowMaxUnitCount() {
    if (unitCount < maxUnitCoint)
        return true;
    return false;
}



Field::Iterator Field::begin() {
    return Iterator(this, cellArray[0]);
}

Field::Iterator Field::end() {
    return Iterator(this, cellArray[height - 1] + width);
}
