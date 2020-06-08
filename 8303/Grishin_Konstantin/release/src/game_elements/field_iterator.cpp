#include "field_iterator.h"

#include "game_elements/field.h"
#include "game_elements/cell_grid.h"

FieldIterator::FieldIterator(Field *field, Cell* cell):
    field(field), p(cell)
{
    iSize = field->getSize().x * field->getSize().y;
}


bool FieldIterator::operator!=(const FieldIterator &other) const{
    return this->p != other.p;
}


bool FieldIterator::operator==(const FieldIterator &other) const{
    return this->p == other.p;
}


typename FieldIterator::reference FieldIterator::operator*() const{
    CellInterface cell_interface(p, field, *(field->landscapeLibrary));
    return cell_interface;
}


FieldIterator& FieldIterator::operator++(){
    p = field->grid->getNext(p);
    return *this;
}
