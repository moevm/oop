#include "DestroyBaseCommand.h"

DestroyBaseCommand::DestroyBaseCommand(Coordinates d, unsigned hp, std::vector<Object**> c)
    : destroyed(d), hpToRestore(hp), clones(c)
{}

void DestroyBaseCommand::exec()
{
    saveBase = (*field)[size_t(destroyed.y)][size_t(destroyed.x)].obj;

    field->delObject(destroyed);
}

void DestroyBaseCommand::unExec()
{
    saveBase->heal(hpToRestore);
    for (auto clone : clones)
        *clone = saveBase;
}
