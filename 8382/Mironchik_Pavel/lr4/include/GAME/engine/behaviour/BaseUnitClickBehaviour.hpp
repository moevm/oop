#pragma once

#include <memory>

#include <GAME/engine/Provider.hpp>
#include <GAME/engine/behaviour/CellClickBehaviour.hpp>
#include <GAME/engine/behaviour/UnitAttackBehaviour.hpp>
#include <GAME/engine/behaviour/UnitMoveBehaviour.hpp>

using std::shared_ptr;

class Unit;

class BaseUnitClickBehaviour : public CellClickBehaviour<Unit> {
public:
	virtual bool onCellClick(sf::Vector2i &cell) override;
};