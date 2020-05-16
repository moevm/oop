#pragma once

#include <GAME/engine/behaviour/UnitAttackBehaviour.hpp>

class BaseUnitAttackBehaviour : public UnitAttackBehaviour {
public:
	virtual bool attack(sf::Vector2i &cell) override;
	virtual bool attack(Unit& other) override;
};