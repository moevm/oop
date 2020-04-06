#ifndef ATTACKER_UNITS_H
#define ATTACKER_UNITS_H
class Unit;
class Attacker_Units
    {
        public:
        virtual void attack_unit(Unit** defender) = 0;

        virtual~Attacker_Units() = default;


    };

#endif // ATTACKER_UNITS_H
