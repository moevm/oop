#include "unit_factory.h"


std::shared_ptr<Unit> create_unit(size_t unit_ID) {
	switch (unit_ID) {
	case knight:
		return std::make_shared<Knight>();
	case rogue:
		return std::make_shared<Rogue>();
	case archer:
		return std::make_shared<Archer>();
	case mage:
		return std::make_shared<Mage>();
	case siege_tower:
		return std::make_shared<Siege_tower>();
	case catapult:
		return std::make_shared<Catapult>();
	default:
		break;
	}
	
	return nullptr;
}