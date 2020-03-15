#pragma once

#include <memory>

class Unit;
class Terrain;

struct FieldCell {
    FieldCell();
    FieldCell(const FieldCell &other);
    FieldCell &operator=(const FieldCell &other);

    std::shared_ptr<Unit> getUnit() {
        return m_unit;
    }
    std::shared_ptr<const Unit> getUnit() const {
        return m_unit;
    }
    void setUnit(const std::shared_ptr<Unit> &unit) {
        m_unit = unit;
    }

    std::shared_ptr<Terrain> getTerrain() {
        return m_terrain;
    }
    std::shared_ptr<const Terrain> getTerrain() const {
        return m_terrain;
    }
    void setTerrain(const std::shared_ptr<Terrain> &terrain) {
        if (terrain == nullptr) {
            throw std::invalid_argument("Error: terrain is nullptr.");
        }
        m_terrain = terrain;
    }

private:
    std::shared_ptr<Unit> m_unit;
    std::shared_ptr<Terrain> m_terrain;
};
