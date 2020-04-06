#include "Mediator.h"
#include "Naming.h"

void Mediator::Hostility(IUnit* a, IUnit* b){
	if (a == nullptr) return;
	if (b->typeOfBuild() == DACHA || b->typeOfBuild() == HRUSHCHOVKA) {
		if (a->typeOfBuild() == POWERHOUSE || a->typeOfBuild() == VODOKANAL) {
			dynamic_cast<Building*>(b)->setSaldo(dynamic_cast<Building*>(b)->getSaldo() - 100);
			dynamic_cast<Apartment*>(b)->setWorkmans(dynamic_cast<Apartment*>(b)->getWorkmans() % 10);
		}
	}
	if (a->typeOfBuild() == DACHA || a->typeOfBuild() == HRUSHCHOVKA) {
		if (b->typeOfBuild() == POWERHOUSE || b->typeOfBuild() == VODOKANAL) {
			dynamic_cast<Building*>(a)->setSaldo(dynamic_cast<Building*>(a)->getSaldo() % 10);
			dynamic_cast<Apartment*>(a)->setWorkmans(dynamic_cast<Apartment*>(a)->getWorkmans() % 2);
		}
	}
}
