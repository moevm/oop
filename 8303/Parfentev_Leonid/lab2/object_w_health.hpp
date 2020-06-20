#ifndef _H_OBJECT_W_HEALTH_HPP
#define _H_OBJECT_W_HEALTH_HPP


class ObjectWithHealth {
    int _health, _base_health;

public:
    ObjectWithHealth(int base_health)
        :_health{base_health},
         _base_health{base_health} {}

    int
    health() const { return _health; }
    int
    baseHealth() const { return _base_health; }
    double
    relativeHealth() const { return _health / (double)_base_health; }
    bool
    alive() const { return health() > 0; }

    virtual void
    heal(int hp) { _health += hp; }

    virtual void
    takeDamage(int dmg) { _health -= dmg; }
};


#endif
