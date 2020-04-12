#ifndef FACADEMEDIATOR_H
#define FACADEMEDIATOR_H

#include "Game/IFacadeMediator.h"

class Game;
class Command;

class FacadeMediator : public IFacadeMediator
{
public:
    FacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_);
    std::string sendRequest(std::vector<size_t> param, eUnitsType unitType = NONE_UNIT, eBaseType baseType = NONE_BASE) override;
    std::string sendInfoRequest(eRequest request, size_t x, size_t y) override;
protected:
    std::shared_ptr<Game> game;
    std::shared_ptr<Command> command;
    std::shared_ptr<UIFacade> facade;
};

class addUnitFacadeMediator : public FacadeMediator
{
public:
    addUnitFacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_);
    std::string sendRequest(std::vector<size_t> param, eUnitsType unitType = NONE_UNIT, eBaseType baseType = NONE_BASE) override;
};

class unitAttackFacadeMediator : public FacadeMediator
{
public:
    unitAttackFacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_);
    std::string sendRequest(std::vector<size_t> param, eUnitsType unitType = NONE_UNIT, eBaseType baseType = NONE_BASE) override;
};

class unitMoveFacadeMediator : public FacadeMediator
{
public:
    unitMoveFacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_);
    std::string sendRequest(std::vector<size_t> param, eUnitsType unitType = NONE_UNIT, eBaseType baseType = NONE_BASE) override;
};



#endif // FACADEMEDIATOR_H
