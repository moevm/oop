#ifndef EASY_H
#define EASY_H

#include "game_elements/team.h"

template<class T> class TGame;
class Field;

class Easy
{
    Field *field;
    TGame<Easy> *game;
    Team first_player;

    Team winner;

public:
    Easy(Team first);
    bool init(Field *field, TGame<Easy> *game);

    bool checkWinner();
    Team getWinner() const;
};

#endif // EASY_H
