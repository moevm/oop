//
// Created by therealyou on 11.02.2020.
//

#include "Unit.h"

int Unit::getX() const {
    return x;
}

void Unit::setX(int x) {
    this->x = x;
}

int Unit::getY() const {
    return y;
}

void Unit::setY(int y) {
    this->y = y;
}

double Unit::minAttribute(double attribute) {
    return attribute - deltaAttribute(attribute);
}

double Unit::deltaAttribute(double attribute) {
    return attribute * SCATTER;
}

double Unit::getSpeed() const {
    return profileUnit.speed;
}

double Unit::getHealth() const {
    return profileUnit.health;
}

double Unit::getArmor() const {
    return profileUnit.armor;
}

double Unit::getDamage() const {
    return profileUnit.damage;
}

void Unit::addUnit() {
    this->canAdded = false;
}

void Unit::deleteUnit() {
    this->canAdded = true;
}

bool Unit::isCanAdded() const {
    return canAdded;
}

void Unit::print() const {

}


void Unit::setRange(int rangeAttack) {
    this->profileUnit.attackRange = rangeAttack;
}

void Unit::setDamage(int damage) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(damage);
    this->profileUnit.damage = min + static_cast<double >(std::rand()) / RAND_MAX * 2 * deltaAttribute(min);
}

void Unit::setArmor(int armor) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(armor);
    this->profileUnit.armor = min + static_cast<double >(std::rand()) / RAND_MAX * 2 * deltaAttribute(min);
}

void Unit::setHealth(int health) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(health);
    this->profileUnit.health = min + static_cast<double >(std::rand()) / RAND_MAX * 2 * deltaAttribute(min);
}

void Unit::setSpeed(int speed) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(speed);
    this->profileUnit.speed = min + static_cast<double >(std::rand()) / RAND_MAX * 2 * deltaAttribute(min);
}

Unit::Unit(int speed, int armor, int damage, int health, int rangeAttack) {
    setArmor(armor);
    setDamage(damage);
    setHealth(health);
    setSpeed(speed);
    setRange(rangeAttack);
}

int Unit::getId() const {
    return this->profileUnit.id;
}

int Unit::getRange() const {
    return this->profileUnit.attackRange;
}

void Unit::setId(int id) {
    profileUnit.id = id;
}

void Unit::death() {
    std::cout << "notify\n";
    this->notify();
}

void Unit::attack(Unit &other) {
    if (other.getHealth() > 0) {
        other.setHealth(other.getHealth() -
                        this->getDamage() /
                        (other.landscape->getAbsorptionFactor(other.type)));
        if (other.getHealth() <= 0) {
            other.setHealth(0);
            other.death();
        }
    }
}

void Unit::attack(Unit *other) {
    if (other->getHealth() > 0) {
        other->setHealth(other->getHealth() -
                         this->getDamage() * 10.0 /
                         (other->landscape->getAbsorptionFactor(other->type)));
        if (other->getHealth() <= 0) {
            other->setHealth(0);
            other->death();
        }
    }
}

void Unit::getDamage(int damage) {
    profileUnit.health -= damage;
    if (getHealth() <= 0) {
        death();
    }
}

std::ostream &operator<<(std::ostream &out, const Unit &unit) {
    char id = unit.getCharType();
    char *name = (char *) malloc(10 * sizeof(char));
    switch (id) {
        case 'P':
            strcpy(name, "Peon");
            break;
        case 'S':
            strcpy(name, "Shooter");
            break;
        case 'E':
            strcpy(name, "Elf");
            break;
        case 'W':
            strcpy(name, "Witch");
            break;
        case 'T':
            strcpy(name, "Troll");
            break;
        case 'G':
            strcpy(name, "Goblin");
            break;
        default:
            break;
    }
    out << "[" << name << "]" << std::endl <<
        "Armor: " << unit.getArmor() << std::endl <<
        "Speed: " << unit.getSpeed() << std::endl <<
        "Damage: " << unit.getDamage() << std::endl <<
        "Health: " << unit.getHealth() << std::endl <<
        "Attack range: " << unit.getRange() << std::endl <<

        "Current position: " << std::endl <<
        "X: " << unit.getX() << std::endl <<
        "Y: " << unit.getY() << std::endl <<
        "Id: " << unit.getId() <<
        std::endl << std::endl;
    return out;
}

std::string Unit::getInfo() {

    std::string unitInfo = std::to_string(this->getCharType())
                           + " " + std::to_string(profileUnit.id)
                           + " " + std::to_string(x) + " " + std::to_string(y)
                           + " " + std::to_string(profileUnit.health)
                           + " " + std::to_string(profileUnit.armor)
                           + " " + std::to_string(profileUnit.damage)
                           + " " + std::to_string(profileUnit.attackRange)
                           + " " + std::to_string(profileUnit.speed);
    return unitInfo;
}