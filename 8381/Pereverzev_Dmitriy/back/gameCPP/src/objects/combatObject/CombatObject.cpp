#include "CombatObject.hpp"

CombatObject::~CombatObject()
{
    type = nullptr;
}

void CombatObject::setHealth(double health)
{
    this->health = health;
    if (this->health <= 0)
        death();
    else
    {
        fireEvent("object updated");
    }
}
double CombatObject::getHealth() const { return health; }
double CombatObject::getMaxHealth() const { return type->getMaxHealth(); }
double CombatObject::getDamage() const { return type->getDamage(); }
double CombatObject::getArmor() const { return type->getArmor(); }

void CombatObject::underAttack(double damage, double armor)
{
    damage = damage * (1 + (armor - this->type->getArmor()) / 10);
    this->setHealth(this->getHealth() - damage);
}

double CombatObject::getDamageAttack() { return this->getDamage(); }

v8::Local<v8::Object> CombatObject::getFullInfo()
{
    v8::Local<v8::Object> info = Object::getFullInfo();

    SetObjProperty(info, "combatOrNeutral", "combat");

    v8::Local<v8::Object> stats = Nan::New<v8::Object>();

    SetObjProperty(stats, "health", health);
    SetObjProperty(stats, "maxHealth", getMaxHealth());
    SetObjProperty(stats, "damage", getDamage());
    SetObjProperty(stats, "armor", getArmor());

    SetObjProperty(info, "stats", stats);

    return info;
}