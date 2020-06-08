#ifndef WORKERUNITFACTORY_H
#define WORKERUNITFACTORY_H

#include "game_elements/team.h"

class Worker;

class WorkerUnitFactory
{
    Team team;

public:
    WorkerUnitFactory(Team team);
    Worker* createWorker(int x_pos, int y_pos);
};

#endif // WORKERUNITFACTORY_H
