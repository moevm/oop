#include "pch.h"
#include "UnitParent.h"
#include <iostream>


UnitParent::UnitParent() {
}

UnitParent::UnitParent(const UnitParent &unit) {
	this->unitProps = unit.unitProps;
}

UnitParent & UnitParent::operator=(const UnitParent &unit) {
	if (this == &unit) return *this;

	this->unitProps = unit.unitProps;

	return *this;
}

UnitParent::~UnitParent() {
}

void UnitParent::updateLocation(Vector2D newBorders) {
	GameUtilities::clamp(unitProps.location.x, newBorders.x, 0);
	GameUtilities::clamp(unitProps.location.y, newBorders.y, 0);
}

void UnitParent::move(Vector2D direction, Vector2D borders) {
	unitProps.location.x += direction.x;
	unitProps.location.y += direction.y;

	GameUtilities::clamp(unitProps.location.x, borders.x, 0);
	GameUtilities::clamp(unitProps.location.y, borders.y, 0);
}

void UnitParent::setNewUnitLocation(Vector2D unitOffset, Vector2D borders) {
	unitProps.location.x += unitOffset.x;
	unitProps.location.y += unitOffset.y;

	GameUtilities::clamp(unitProps.location.x, borders.x, 0);
	GameUtilities::clamp(unitProps.location.y, borders.y, 0);
}

void BeeUnit::attack() {
	std::cout << "It's me, BEE" << std::endl;
}

void FlyUnit::attack() {
	std::cout << "It's me, FLY" << std::endl;
}

void CollectorUnit::attack() {
	std::cout << "It's me, COLLECTOR" << std::endl;
}

void SprinklerUnit::attack() {
	std::cout << "It's me, SPRINKLER" << std::endl;
}

void CoalUnit::attack() {
	std::cout << "It's me, COAL" << std::endl;
}

void FlowerUnit::attack() {
	std::cout << "It's me, FLOWER" << std::endl;
}
