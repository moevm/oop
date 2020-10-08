#include "../Headers/Unit.h"
#include <random>
#include <algorithm>

void Unit::takeDmg(int Damage) {
	hp.takeDmg(Damage, armor.get());
	armor.dec();
}

void Unit::operator*(std::shared_ptr<NtrlObj> hi) {
    if(hi == nullptr) return;
    auto names = hi->who();
    if(std::find(names.begin(),names.end(), name) != names.end()){
        auto effect = (*hi).get();
        switch (effect.type){
            case ObjEffectType::hp:
                hp.hp = hp.hp < (-1*effect.size) ? 1 : hp.hp + effect.size;
                hp.hp = hp.hp > hp.max_hp? hp.max_hp: hp.hp;
                break;
            case ObjEffectType::power:
                damage.damage += effect.size;
                break;
            case ObjEffectType::range:
                range += effect.size;
                break;
        }
    }

}

void Unit::Say() {
    int cur_d = damage.damage;
    int cur_h = hp.hp;
    int cur_r = range;
    switch (effect.type){
        case LandEffectType::range:
            cur_r += effect.size;
            break;
        case LandEffectType::hp:
            cur_h += effect.size;
            break;
        case LandEffectType::power:
            cur_d += effect.size;
            break;
    }
    std::cout << "Меня зовут: " << name << ", моя сила: " << cur_d << ", мое здоровье: " << cur_h << ", моя дальность: " << cur_r << std::endl;
}

Hp::Hp(int a): hp(a), max_hp(a){}

void Hp::takeDmg(int damage, int armor) {
	int clear_damage = armor > damage ? 0 : damage - armor;
	hp = clear_damage > hp? 0 : hp - clear_damage;
}

Dmg::Dmg(int a): damage(a), accuracy(a/4){}

int Dmg::get() {
	int scatter = (rand() % (2 * accuracy)) - accuracy + 1;
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
	hp = Hp(200);
	damage = Dmg(50);
	armor = Def(20);
	range = 1;
	name = 'K';
}

Shieldman::Shieldman() {
    hp = Hp(200);
    damage = Dmg(50);
    armor = Def(20);
    range = 1;
    name = 'S';
}

Archer::Archer() {
    hp = Hp(200);
    damage = Dmg(50);
    armor = Def(20);
    range = 1;
    name = 'A';
}

Ranger::Ranger() {
    hp = Hp(200);
    damage = Dmg(50);
    armor = Def(20);
    range = 1;
    name = 'R';
}

Caster::Caster() {
    hp = Hp(200);
    damage = Dmg(50);
    armor = Def(20);
    range = 1;
    name = 'C';
}

Healer::Healer() {
    hp = Hp(50);
    damage = Dmg(10);
    armor = Def(20);
    range = 1;
    name = 'H';
}
