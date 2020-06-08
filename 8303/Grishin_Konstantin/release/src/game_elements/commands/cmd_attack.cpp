#include "cmd_attack.h"

#include "game_elements/field.h"
#include "game_elements/team.h"
#include "game_elements/interface/cell_interface.h"

#include "logger.h"

CmdAttack::CmdAttack(Field* field, const EntityInterface& attacking, int to_x, int to_y):
    field(field), from_x(attacking.getPos().x),
    from_y(attacking.getPos().y),
    to_x(to_x), to_y(to_y)
{
    team = attacking.getTeam();
    for(auto &pos: attacking.getTargets()){
        if(pos == sf::Vector2i(to_x, to_y))
            return;
    }

    if(attacking.empty())
        throw empty_interface("non-existent attacking unit", 11);

    if(field->getCell(to_x, to_y).empty())
        throw CellInterface::empty_cell("try to attack non-existen cell", 11);

    ableToAttack = 0;
}


bool CmdAttack::execute(Logger *logger){
    if(!ableToAttack) {
        if(logger)
            (*logger) << "cell out of attack range\n";
        return 0;
    }

    auto attacking = field->getEntity(from_x, from_y);

    if(logger)
        (*logger) << attacking.getID() + " attacking ("
                  << std::to_string(to_x) << "; "
                  << std::to_string(to_y) << ") from ("
                  << std::to_string(from_x) << "; "
                  << std::to_string(from_y) << ")\n";

    if(attacking.getID() == "unit_troll"
    || attacking.getID() == "unit_knight")
    {
        bool good = field->attack(from_x, from_y, to_x, to_y);

        if(logger && good)
            (*logger) << "enemy match\n";

        bool f = field->attack(to_x, to_y, from_x, from_y, 0.5f);

        if(logger && f)
            (*logger) << "got a return attack\n";

        return good;
    }

    if(attacking.getID() == "unit_wizard"
    || attacking.getID() == "unit_berserk")
    {
        bool good = field->attack(from_x, from_y, to_x, to_y);

        if(logger && good)
            (*logger) << "enemy match\n";

        // attack in one cell range
        bool u = field->attack(from_x, from_y, to_x, to_y-1, 0.8f);  // up
        bool r = field->attack(from_x, from_y, to_x+1, to_y, 0.8f);  // right
        bool d = field->attack(from_x, from_y, to_x, to_y+1, 0.8f);  // down
        bool l = field->attack(from_x, from_y, to_x-1, to_y, 0.8f);  // left

        if(logger){
            (*logger) << "attack near positions:\n";
            if(u) (*logger) << "upper position attacked\n";
            if(r) (*logger) << "right position attacked\n";
            if(d) (*logger) << "lower position attacked\n";
            if(l) (*logger) << "left position attacked\n";
        }

        auto delta = abs(from_x - to_x) + abs(from_y - to_y);
        if(delta == 1){
            bool f = field->attack(to_x, to_y, from_x, from_y, 0.4f);
            if(logger && f)
                (*logger) << "got a return attack\n";
        }

        return good;
    }

    return field->attack(from_x, from_y, to_x, to_y);;
}


const std::string& CmdAttack::name() const
{
    return name_;
}


bool CmdAttack::valid_p() const
{
    return ableToAttack;
}


Team CmdAttack::getTeam() const{
    return team;
}
