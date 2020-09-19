#pragma once

struct Hp {
	Hp(int a=10);
	void takeDmg(int damage, int armor);
	int hp; // hp < max_hp
	int max_hp;
};

struct Dmg {
	Dmg(int a=10);
	int get();
	int damage; // +-scatter
	int accuracy;
};

struct Def {
	Def(int a=10);
	int get();
	void dec();
	int armor; // integrity != 0 : armor ? 0
	int integrity;
};

struct Unit {
	void  takeDmg(int Damage);
	virtual ~Unit() = default;
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
	Knight(Knight const& a);
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