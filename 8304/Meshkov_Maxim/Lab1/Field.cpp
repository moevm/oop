#include "Field.hpp"

Field::Field(int width, int height)
    : m_units(width, height)
{}

Field::Field(const Field &other)
    : m_units(other.m_units)
{
    copyUnits();
}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        m_units = other.m_units;
        copyUnits();
    }
    return *this;
}

void Field::addUnit(const std::shared_ptr<Unit> &unit, FieldPosition position) {
    m_units.at(position.row, position.col) = unit;
}

void Field::removeUnit(FieldPosition position) {
    m_units.at(position.row, position.col).reset();
}

std::shared_ptr<Unit> Field::getUnit(FieldPosition position) {
    return m_units.at(position.row, position.col);
}

int Field::getWidth() const {
    return m_units.getWidth();
}

int Field::getHeight() const {
    return m_units.getHeight();
}

void Field::copyUnits() {
    for (int row = 0; row < m_units.getHeight(); row++) {
        for (int col = 0; col < m_units.getWidth(); col++) {
            m_units.at(row, col) = m_units.at(row, col)->createCopy();
        }
    }
}
