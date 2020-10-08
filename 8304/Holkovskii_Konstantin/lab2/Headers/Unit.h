#pragma once

#include <memory>
#include "NtrlObj.h"
#include "LandscapeResurces.h"
#include <iostream>

struct Hp {
	explicit Hp(int a = 10);
	void takeDmg(int damage, int armor);
	int hp; // hp < max_hp
	int max_hp;
};

struct Dmg {
	explicit Dmg(int a = 10);
	int get();
	int damage; // +-scatter
	int accuracy;
};

struct Def {
	explicit Def(int a = 10);
	int get();
	void dec();
	int armor; // integrity != 0 : armor ? 0
	int integrity;
};

struct IUnit{
    virtual void takeDmg(int) = 0;
};

struct Unit : public IUnit {
	void takeDmg(int Damage) override;
	~Unit() = default;
	void operator*(std::shared_ptr<NtrlObj> hi);
    void Say();
	LandEffect effect = {LandEffectType::noeffect, 0};
	Hp hp;
	Dmg damage;
	Def armor;
	int range;
	char name;
};

//knight, shieldman, archer, ranger, caster, healer

struct SwordsMan : Unit {

};

struct Knight : SwordsMan {
	Knight();
};

struct Shieldman : SwordsMan {
	Shieldman();
};

struct Shooter : Unit {
};

struct Archer : Shooter {
	Archer();
};

struct Ranger : Shooter {
	Ranger();
};

struct Mage : Unit {
};

struct Caster : Mage {
	Caster();
};

struct Healer : Mage {
	Healer();
};