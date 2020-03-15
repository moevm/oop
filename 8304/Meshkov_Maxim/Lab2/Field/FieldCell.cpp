#include "FieldCell.hpp"

#include "../Units/Unit.hpp"
#include "../Terrains/GroundTerrain.hpp"

FieldCell::FieldCell()
    : m_terrain(new GroundTerrain)
{}

FieldCell::FieldCell(const FieldCell &other) {
    *this = other;
}

FieldCell &FieldCell::operator=(const FieldCell &other) {
    if (&other != this) {
        m_unit = other.m_unit->createCopy();
        m_terrain = other.m_terrain->createCopy();
    }
    return *this;
}
