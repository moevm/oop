#pragma once
#include <iostream>
#include <string>
class UnitAttributes
{
private:
	int healPoints;
	int armorPoints;
	int damage;
	int range;
public:
	void setAll(int hp, int ap, int dmg, int r);
	int getHealPoints() const;
	int getArmorPoints() const;
	int getDamage() const;
	int getRange() const;

	void setHealPoints(int hp);
	void setArmorPoints(int ap);
	void setDamage(int dmg);
	void setRange(int r);

	friend std::ostream& operator<<(std::ostream& os, const UnitAttributes& ua) {
		return os << "healPoints:[" << ua.healPoints << "], armorPoints:[" << ua.armorPoints << "], damage:[" << ua.damage << "], range:[" << ua.range << "]";
	}
	std::string getInfoAttributes() const{
		std::string  out = "healPoints:[" + std::to_string(healPoints) + "], armorPoints:[" + std::to_string(armorPoints) + "], damage:[" + std::to_string(damage) + "], range:[" + std::to_string(range) + "]";
		return out;
	}
};
