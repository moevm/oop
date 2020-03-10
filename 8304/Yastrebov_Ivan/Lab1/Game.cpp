#include "pch.h"

#include <iostream>
#include "Unit.h"
#include "Field.h"
#include "FieldIterator.h"

void doNothing(Field fi) {
	//hi

};

int main()
{

	Field f(10, 10);

	Catapult* danilkin = new Catapult;
	HorsemenLeader* vanyusha = new HorsemenLeader;

	f.addObj((Unit*)danilkin, 1, 1);
	f.addObj((Unit*)vanyusha, 2, 2);

	danilkin->attack(&f, vanyusha);

	danilkin->move(&f, -1, -1);

	Iterator it(f);

	it.first();

	++it;
	--it;

	auto tmp = (*it);

	doNothing(f);

	return 0;
}


