#ifndef mediator_hpp
#define mediator_hpp


class Unit;
class BattleField;
class Log;

#include <memory>


class Mediator
{
public:
    explicit Mediator(std::shared_ptr<BattleField> battleField,std::shared_ptr<Log> log);
    ~Mediator() = default;

    bool notify(std::shared_ptr<Unit> unit, const std::string& action);
 
private:
    std::shared_ptr<BattleField> battleField;
    std::shared_ptr<Log> log;
};

#endif /* mediator_hpp */
