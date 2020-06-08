#ifndef NORMAL_H
#define NORMAL_H

#include "game_elements/team.h"

template<class T> class TGame;
class Field;

class Normal
{
    Field *field;
    TGame<Normal> *game;
    Team first_player;

    Team winner;

public:
    Normal(Team first);
    bool init(Field *field, TGame<Normal> *game);

    bool checkWinner();
    Team getWinner() const;
};

#endif // NORMAL_H
