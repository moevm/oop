#include "../Headers/Unit.h"
#include <random>

void Unit::takeDmg(int Damage) {
	hp.takeDmg(Damage, armor.get());
	armor.dec();
}

Hp::Hp(int a): hp(a), max_hp(a){}

void Hp::takeDmg(int damage, int armor) {
	int clear_damage = armor > damage ? 0 : damage - armor;
	hp = clear_damage > hp? 0 : hp - clear_damage;
}

Dmg::Dmg(int a): damage(a), accuracy(a/4){}

int Dmg::get() {
	int scatter = rand() % (2 * accuracy) - accuracy + 1;
	return damage - scatter;
}

Def::Def(int a):armor(a),integrity(3){}

int Def::get() {
	if (integrity != 0) return armor;
	return 0;
}

void Def::dec() {
	if (integrity == 0) return;
	--integrity;
}

Knight::Knight() {
	hp = 200;
	damage = 50;
	armor = 20;
	range = 1;
	name = 'K';
}

Knight::Knight(Knight const &a) {
        hp = a.hp;
        damage = a.damage;
        armor = a.armor;
        range = a.range;
        name = a.name;
}

Shieldman::Shieldman() {
    hp = 200;
    damage = 50;
    armor = 20;
    range = 1;
    name = 'S';
}

Archer::Archer() {
    hp = 200;
    damage = 50;
    armor = 20;
    range = 1;
    name = 'A';
}

Ranger::Ranger() {
    hp = 200;
    damage = 50;
    armor = 20;
    range = 1;
    name = 'R';
}

Caster::Caster() {
    hp = 200;
    damage = 50;
    armor = 20;
    range = 1;
    name = 'C';
}

Healer::Healer() {
    hp = 200;
    damage = 50;
    armor = 20;
    range = 1;
    name = 'H';
}
