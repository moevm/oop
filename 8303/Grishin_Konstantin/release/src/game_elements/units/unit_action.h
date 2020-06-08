#ifndef UNITACTION_H
#define UNITACTION_H


class UnitAction
{
public:
    enum Type{
        Attack,
        Heal,
        Work
    };

    struct AttackAction{
        float damage;
        int radius;
        int blind;
    };

    struct HealAction{
        float health;
        int radius;
    };

    struct WorkAction{
        bool work;
        int x;
        int y;
    };

    Type type;

    union{
        AttackAction    attackAction;
        HealAction      healAction;
        WorkAction      workAction;
    };

private:
    friend class Unit;
    UnitAction();
};

#endif // UNITACTION_H
