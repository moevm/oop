#include "Mediator.h"

void Mediator::make_action() const {
    std::cout << "Neutral object is interaction with unit." << std::endl;
    unit->defense.change(neutral_object->get_health());
    unit->attack.change(neutral_object->get_attack());
    unit->intelligence += neutral_object->get_intelligence();
}
