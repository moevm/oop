#include <iostream>
#include <map>
#include <string>

#include "storable.hpp"
#include "restorers.hpp"
#include "common_storables.hpp"

#include "melee_units.hpp"
#include "ranged_units.hpp"
#include "catapult_units.hpp"
#include "landscape_types.hpp"
#include "neutral_object_types.hpp"

#include "factory_table.hpp"
#include "iostream_player.hpp"

#include "game_rules.hpp"


RestorerTable *
RestorerTable::defaultTable()
{
    return new RestorerTable {{

{"end", new SimpleRestorer<StorableEnd> {}},
{"coords", new SimpleRestorer<StorableCoordinates> {}},
{"index", new SimpleRestorer<StorableWithIndex> {}},
{"at", new SimpleRestorer<StorableWithCoords> {}},

{"game", new restorers::GameRestorer {}},
{"map", new restorers::MapRestorer {}},

{"base", new SimpleRestorer<Base> {}},
{"base_w_countdown", new SimpleRestorer<BaseWithSpawnCountdown> {}},

{"iostream_player", new SimpleRestorer<IostreamPlayer> {}},

{"l_normal", new SimpleRestorer<landscapes::Normal> {}},
{"l_swamp", new SimpleRestorer<landscapes::Swamp> {}},
{"l_forest", new SimpleRestorer<landscapes::Forest> {}},

{"u_swordsman", new SimpleRestorer<units::Swordsman> {}},
{"u_spearsman", new SimpleRestorer<units::Spearsman> {}},
{"u_cavalry", new SimpleRestorer<units::Cavalry> {}},

{"u_archer", new SimpleRestorer<units::Archer> {}},
{"u_slinger", new SimpleRestorer<units::Slinger> {}},

{"u_onager", new SimpleRestorer<units::Onager> {}},
{"u_boltthrower", new SimpleRestorer<units::BoltThrower> {}},

{"n_healingwell", new SimpleRestorer<objects::HealingWell> {}},
{"n_tower", new SimpleRestorer<objects::Tower> {}},
{"n_tunnelentrance", new SimpleRestorer<objects::TunnelsEntrance> {}},
{"n_weaponsmiths", new SimpleRestorer<objects::WeaponSmiths> {}},

{"uf_melee",
 new SimpleRestorer<objects::WeaponSmiths::MeleeUnitFilter> {}},
{"uf_ranged",
 new SimpleRestorer<objects::WeaponSmiths::RangedUnitFilter> {}},
{"uf_catapult",
 new SimpleRestorer<objects::WeaponSmiths::CatapultUnitFilter> {}},

{"mp_basic", new SimpleRestorer<BasicMovement> {}},
{"mp_modifyiing", new SimpleRestorer<ModifyingMovePolicy> {}},

{"dp_basic", new SimpleRestorer<BasicDefense> {}},
{"dp_level_deco", new SimpleRestorer<DefenseLevelDeco> {}},
{"dp_multiplier", new SimpleRestorer<MultiplierDefensePolicy> {}},

{"ap_forbidden", new SimpleRestorer<AttackForbidden> {}},
{"ap_multiplier", new SimpleRestorer<MultiplierAttackPolicy> {}},
{"ap_extended", new SimpleRestorer<ExtendedShootingRange> {}},

{"ap_melee", new SimpleRestorer<MeleeAttack> {}},
{"ap_ranged", new SimpleRestorer<RangedAttack> {}},
{"ap_catapult", new SimpleRestorer<CatapultAttack> {}},

    }};
}
