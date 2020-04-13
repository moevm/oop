#pragma once
#include "Unit_types.h"


class Land
{
	friend class RiverProxy;
	friend class ForestProxy;
	friend class SwampProxy;
	friend class MeadowProxy;
	friend class BuildingProxy;
	Land(){}
	
	void slow(Unit * unit, float debuff);
	void weak(Unit * unit, float debuff);
	void disableAttack(Unit * unit);
	void enableAttack(Unit * unit);
	
public:
	string sprite = "";
	virtual void interact(Unit * unit) = 0;
	virtual bool isInteract(Unit * unit) = 0;
};

class RiverProxy : public Land
{
	Land * land;
public:
	RiverProxy() { sprite = "River"; }
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};
class ForestProxy : public Land
{
	Land * land;
public:
	ForestProxy() { sprite = "Forest"; }
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};
class SwampProxy : public Land
{
	Land * land;
public:
	SwampProxy() { sprite = "Swamp"; }
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};
class MeadowProxy : public Land
{
	Land * land;
public:
	MeadowProxy() { sprite = "Meadow"; }
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};
class BuildingProxy : public Land
{
	Land * land;
public:
	BuildingProxy() { sprite = "Meadow"; }
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};

class Netral
{
public:
	class Iteraction
	{
	public:
		virtual void interact(Unit * unit) = 0;
	};

	class Interactor
	{
		Iteraction * it;
	public:
		Interactor(Iteraction * inter) : it(inter) {}
		void interact(Unit * unit)
		{
			it->interact(unit);
		}
	};

	Netral() {}
	Interactor * it;
	string sprite;
	virtual void operator>>(Unit * unit) = 0;
	//void interact(Unit * unit) { *this >> unit; }
};

class Gold : public Netral
{
	class Infantry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Cavalry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Archers_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};

public:
	void operator>>(Unit * unit);
	Gold() : Netral()
	{
		sprite = "Gold";
	}
};
class Curse : public Netral
{
	class Infantry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Cavalry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Archers_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};

public:
	void operator>>(Unit * unit);
	Curse() : Netral()
	{
		sprite = "Curse";
	}
};
class Rune : public Netral
{
	class Infantry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Cavalry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Archers_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};

public:
	void operator>>(Unit * unit);
	Rune() : Netral()
	{
		sprite = "Rune";
	}
};
class Trap : public Netral
{
	
	class Infantry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Cavalry_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	class Archers_Iteraction : public Iteraction
	{
		void interact(Unit * unit);
	};
	
public:
	void operator>>(Unit * unit);
	Trap() : Netral()
	{
		sprite = "Trap";
	}
};
class EmptyObject : public Netral
{
public:
	void operator>>(Unit * unit)
	{
		return;
	}
	EmptyObject() : Netral()
	{
		sprite = "";
	}
};

class Cell
{
public:
	Unit * unit;
	Land * land;
	Netral * netral;
};