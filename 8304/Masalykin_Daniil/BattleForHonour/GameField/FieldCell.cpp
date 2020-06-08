#include "FieldCell.h"

FieldCell::FieldCell(Terrain *terrain): FieldCell() {
    this->terrain = terrain;
}

bool FieldCell::setObject(GameObject *object) {
    if (isEmpty()){
        this->object = object;
        return true;
    } else
        return false;
}

bool FieldCell::setTerrain(Terrain *terrain) {
    if (!this->terrain){
        this->terrain = terrain;
        return true;
    } else
        return false;
}

void FieldCell::eraseObject() {
    this->object = nullptr;
}

std::ostream &operator<<(std::ostream &stream, const FieldCell &cell) {

    stream << " ";

    if (cell.terrain){

        if (cell.object)
            cell.terrain->print(stream, *cell.object);
        else
            stream << *(cell.terrain);

    } else{

        if (cell.object)
            stream << *(cell.object);
        else
            stream << "#";

    }
    return stream;
}

FieldCell::FieldCell(FieldCell &&other):
        object(other.object),
        terrain(other.terrain)
        {
    other.object = nullptr;
}

FieldCell &FieldCell::operator=(FieldCell &&other) {
    if (&other == this)
        return *this;

    object = other.object;
    other.object = nullptr;

    return *this;

}

FieldCell::FieldCell(const FieldCell &cell):
        object(cell.object),
        terrain(cell.terrain){}

FieldCell &FieldCell::operator=(const FieldCell &cell) {
    object = cell.object;
    terrain = cell.terrain;

    return *this;

}