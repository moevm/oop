#pragma once
#include "Unit_types.h"


class Land
{
	friend class RiverProxy;
	friend class ForestProxy;
	friend class SwampProxy;
	friend class MeadowProxy;
	Land(){}
	
	void slow(Unit * unit, float debuff);
	void weak(Unit * unit, float debuff);
	void disableAttack(Unit * unit);
	void enableAttack(Unit * unit);
	
public:

	virtual void interact(Unit * unit) = 0;
	virtual bool isInteract(Unit * unit) = 0;
};

class RiverProxy : public Land
{
	Land * land;
public:
	RiverProxy() {}
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};
class ForestProxy : public Land
{
	Land * land;
public:
	ForestProxy() {}
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};
class SwampProxy : public Land
{
	Land * land;
public:
	SwampProxy() {}
	void interact(Unit * unit);
	bool isInteract(Unit * unit);
};
class MeadowProxy : public Land
{
	Land * land;
public:
	MeadowProxy() {}
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
	virtual void operator>>(Unit * unit) = 0;
};

class Pit : public Netral
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
	
};
class EmptyObject : public Netral
{
public:
	void operator>>(Unit * unit)
	{
		return;
	}
};


class Cell
{
public:
	Unit * unit;
	Land * land;
	Netral * netral;
};