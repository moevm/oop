#include <iostream>
#include "Field.h"

class UnitControl {
private:
	Field* field;
public:
	UnitControl(Field* f) {
		field = f;
	}
	void UnitFunctional(Unit* a, Base* start_base) {
		int choice = 2e7, x, y;
		while (choice != 0) {
			std::cout << "Unit: Moving(1), attack(2, coords), switch to base(0)\n Your choice:";
			std::cin >> choice;
			switch (choice) {
			case 1:
				std::cin >> x >> y;
				field->Moving(a, a->getx(), a->gety(), x, y);
				break;
			case 2:
				std::cin >> x >> y;
				if (abs(x - a->getx()) < a->getCharactresistics()->getSpeed() && abs(y - a->gety()) < a->getCharactresistics()->getSpeed()) {

					a->attack(field->getCoords(x, y)->getUnit());
					if (field->getCoords(x, y)->getUnit()->getCharactresistics()->getArmor()->getArmorValue() < 0) {
						Unit* b = field->getCoords(x, y)->getUnit();
						field->RemObj(b, x, y);
						start_base->deleteUnit(b);
						field->Moving(a, a->getx(), a->gety(), x - a->getx(), y - a->gety());
					}
				}
				else if (x - a->getx() == 0)
					field->Moving(a, a->getx(), a->gety(), 0, a->getCharactresistics()->getSpeed() * (y - a->gety()) / abs(y - a->gety()));
				else if (y - a->gety() == 0)
					field->Moving(a, a->getx(), a->gety(), a->getCharactresistics()->getSpeed() * (x - a->getx()) / abs(x - a->getx()), 0);
				else field->Moving(a, a->getx(), a->gety(), a->getCharactresistics()->getSpeed() * (x - a->getx() )/ abs(x - a->getx()), a->getCharactresistics()->getSpeed() * (y - a->gety()) / abs(y - a->gety()));
				break;
			}field->PrintField();
		}
	}
};
class BaseControl {
private:
	Base* start_base;
	Field* field;
	UnitControl* unit_ctrl;
public:
	BaseControl(Field* f) {
		field = f;
		start_base = field->SetBase(0, 0);
		unit_ctrl = new UnitControl(field);
	}
		;
	void BaseFunctional() {
		int choice = 2e7, x, y;
		Unit* unit = nullptr;
		while (choice != 0) {
			std::cout << "\nBase: create swordman(1), spearman(2), slinger(3), bowman(4),light cavalry(5), heavy cavalry(6)\nSwitch to unit(7, write coords)\nCheck base condition(8)\nQuit(0)\nYour choice:";
			std::cin >> choice;

			switch (choice) {
			case 1:
			{
				unit = start_base->createSwordman();
				field->AddObj(unit, unit->getx(), unit->gety());
				break;
			}
			case 2:
			{
				unit = start_base->createSpearman();
				field->AddObj(unit, unit->getx(), unit->gety());
				break;
			}
			case 3:
			{
				unit = start_base->createSlinger();
				field->AddObj(unit, unit->getx(), unit->gety());
				break;
			}
			case 4:
			{
				unit = start_base->createBowman();
				field->AddObj(unit, unit->getx(), unit->gety());
				break;
			}
			case 5:
			{
				unit = start_base->createLC();
				field->AddObj(unit, unit->getx(), unit->gety());
				break;
			}
			case 6:
			{
				unit = start_base->createHC();
				field->AddObj(unit, unit->getx(), unit->gety());
				break;
			}
			case 7: {
				std::cin >> x >> y;
				if (field->getCoords(x, y)->getUnit()->getid() != '0')
					unit_ctrl->UnitFunctional(unit, start_base);
				else std::cout << "Incorrect coordinates";
				break;
			}case 8: {
				start_base->printBaseCondition();
				break;
			}
				
			}field->PrintField();
		}

	
	}

};

int main() {

	Field *f = new Field(10, 30, 30);
	f->formLandscape();

	BaseControl* base = new BaseControl(f);
	base->BaseFunctional();

	return 0;
}
