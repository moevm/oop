#include <random>

#include "storable.hpp"
#include "common_storables.hpp"
#include "unit.hpp"


std::default_random_engine global_random {};

void
Unit::store(std::ostream &os) const
{
    os << health() << "\n";

    movePolicy()->store(os);
    defensePolicy()->store(os);
    attackPolicy()->store(os);

    os << "end\n";
}

bool
Unit::restore(std::istream &is, RestorerTable *tab)
{
    if (!ObjectWithHealth::restore(is, tab)) {
        return false;
    }

    for (;;) {
        Storable *s = tab->restore(is);

        if (auto *mp = dynamic_cast<MovePolicy *>(s)) {
            setMovePolicy(mp);
        } else if (auto *dp = dynamic_cast<DefensePolicy *>(s)) {
            setDefensePolicy(dp);
        } else if (auto *ap = dynamic_cast<AttackPolicy *>(s)) {
            setAttackPolicy(ap);
        } else if (dynamic_cast<StorableEnd *>(s)) {
            delete s;
            break;
        } else {
            delete s;
            return false;
        }
    }

    return true;
}
