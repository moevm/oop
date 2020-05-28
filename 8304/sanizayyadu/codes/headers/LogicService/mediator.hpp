#ifndef mediator_hpp
#define mediator_hpp


class Unit;
class BattleField;
class Proxy;

#include <memory>


class Mediator
{
public:
    explicit Mediator(std::shared_ptr<BattleField> battleField,std::shared_ptr<Proxy> proxyLog);
    ~Mediator() = default;

    bool notify(std::shared_ptr<Unit> unit, const std::string& action);
 
private:
    std::shared_ptr<BattleField> battleField;
    std::shared_ptr<Proxy> proxyLog;
};

#endif /* mediator_hpp */
