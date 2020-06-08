#include "easy.h"

#include "t_game.h"
#include "game_elements/field.h"


Easy::Easy(Team first)
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


bool Easy::init(Field* field, TGame<Easy> *game)
{
    this->field = field;
    this->game = game;

    if(!game || !field)
        return 0;

    game->setPointsMod(0.5f);

    game->addPoints(Team::Blu, 9);
    game->addPoints(Team::Red, 9);

    game->setFirstPlayer(first_player);
}


bool Easy::checkWinner(){
    if(!game || !field)
        return 0;

    auto bluBase = field->getBluBase();
    auto redBase = field->getRedBase();

    if(bluBase.empty() && redBase.empty()){
        winner = Team::Neutral;
        return 1;
    }

    if(bluBase.empty()){
        winner = Team::Red;
        return 1;
    }

    if(redBase.empty()){
        winner = Team::Blu;
        return 1;
    }

    return 0;
}


Team Easy::getWinner() const{
    return winner;
}
