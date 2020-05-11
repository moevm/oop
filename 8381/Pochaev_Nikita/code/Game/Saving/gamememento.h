#ifndef GAMEMEMENTO_H
#define GAMEMEMENTO_H

#include "IMemento.h"
#include "SaveStuctures.h"

class GameMemento : public IMemento
{
public:
    GameMemento();

private:
    GameParametersCaretaker gamePar;
};

#endif // GAMEMEMENTO_H
