#ifndef FIELDITERATOR_H
#define FIELDITERATOR_H

#include <iterator>

class Cell;
class CellInterface;
class Field;

class FieldIterator
{
    friend class Field;
private:
    Field *field;
    int iSize;
    Cell *p;

    FieldIterator(Field *field, Cell *p);

public:
    using iterator_category = std::input_iterator_tag;
    using value_type = CellInterface;
    using difference_type = int;
    using pointer = Cell*;
    using reference = CellInterface;

    FieldIterator(const FieldIterator& it);

    bool operator != (FieldIterator const &other) const;
    bool operator == (FieldIterator const &other) const;
    typename FieldIterator::reference operator*() const;
    FieldIterator& operator ++ ();

};

#endif // FIELDITERATOR_H
