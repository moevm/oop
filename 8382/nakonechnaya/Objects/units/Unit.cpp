#include "Unit.h"

void Unit::setCoordinates(int x, int y) {
    coordinates = new Coordinates;
    coordinates->x = x;
    coordinates->y = y;
}

void Unit::changeAttributes(int attack, int defense, int health) {
    this->attack->changeValue(attack);
    this->health->changeValue(health);
    this->defense->changeValue(defense);
    std::string update = "Update units attributes.";
    notifyObservers(&update);
}

void Unit::setAttributes(int attack, int defense, int health) {
    this->attack = new Attack(attack);
    this->defense = new Defense(defense);
    this->health = new Health(health);
}

void Unit::printAttributeValues() {
    if (health->getValue() < 0)
        std::cout << "Health: " << 0 << std::endl;
    else
        std::cout << "Health: " << health->getValue() << std::endl;
    if (defense->getValue() < 0)
        std::cout << "Defense: " << 0 << std::endl;
    else
        std::cout << "Defense: " << defense->getValue() << std::endl;
    if (attack->getValue() < 0)
        std::cout << "Attack: " << 0 << std::endl;
    else
        std::cout << "Attack: " << attack->getValue() << std::endl;
}

void Unit::addObservers(Observer *observer) {
    observers.push_back(observer);
}

void Unit::notifyObservers(std::string *newAction) {
    for (auto & observer : observers){
        observer->update(*newAction);
    }
}