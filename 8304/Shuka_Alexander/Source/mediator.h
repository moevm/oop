#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <memory>

namespace unit {
    class Unit;
}

class GameField;


class Mediator
{
public:
    explicit Mediator(std::shared_ptr<GameField> gameField);

    bool notify(std::shared_ptr<unit::Unit> unit, const std::string& act);

private:
    std::shared_ptr<GameField> gameField;
};


#endif // MEDIATOR_H
