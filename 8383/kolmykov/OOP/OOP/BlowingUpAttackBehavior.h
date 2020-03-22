#pragma once
#include "AttackBehavior.h"


class BlowingUpAttackBehavior :
	public AttackBehavior
{
public:
	BlowingUpAttackBehavior();
	~BlowingUpAttackBehavior();
	void attack(std::shared_ptr<Unit> unit);
};

