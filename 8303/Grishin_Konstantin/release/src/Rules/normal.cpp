#include "normal.h"

#include "t_game.h"
#include "game_elements/field.h"

Normal::Normal(Team first)
{
    if(first == Team::Neutral)
    {
        RandInt randomizer;
        if(randomizer(0, 1) == 1){
            first = Team::Red;
        } else {
            first = Team::Blu;
        }
    }

    first_player = first;
}


bool Normal::init(Field *field, TGame<Normal> *game)
{
    this->field = field;
    this->game = game;

    if(!game || !field)
        return 0;

    game->setPointsMod(1);
    game->setFirstPlayer(first_player);
}


bool Normal::checkWinner()
{
    if(!game || !field)
        return 0;

    int blu_units = 0;
    int red_units = 0;

    for(auto c: (*field))
    {
        auto e = c.getEntity();
        if(e.empty()) continue;
        if(e.getEntityType() != Entity::Unit) continue;

        if(e.getTeam() == Team::Red)
            red_units++;
        if(e.getTeam() == Team::Blu)
            blu_units++;
    }

    auto points = game->getPoints();

    if(points.first == 0 && points.second == 0)
    {
        if(blu_units == 0 && red_units == 0){
            winner = Team::Neutral;
            return 1;
        }
        if(blu_units == 0){
            winner = Team::Red;
            return 1;
        }
        if(red_units == 0){
            winner = Team::Blu;
            return 1;
        }
        return 0;
    }

    if(points.first == 0 && red_units == 0){
        winner = Team::Blu;
        return 1;
    }
    if(points.second && blu_units == 0){
        winner = Team::Red;
        return 1;
    }
    return 0;
}


Team Normal::getWinner() const{
    return winner;
}









