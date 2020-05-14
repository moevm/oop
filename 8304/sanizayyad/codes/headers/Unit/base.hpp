#ifndef base_hpp
#define base_hpp

#include "unit.hpp"
#include "unitcreator.hpp"
#include "observerInterface.hpp"

#include <time.h>
#include <stdio.h>

constexpr int MAX_NUMBER_UNITS = 10;

class Base : public Unit, public ObserverInterface, public std::enable_shared_from_this<Base>
{
public:
    explicit Base(const Position2D& position,std::shared_ptr<Mediator> mediator, PLAYER player);

    virtual bool moveLeft() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;
    virtual bool moveRight() override;

    std::shared_ptr<Unit> createShortRangeUnit(int dx, int dy);
    std::shared_ptr<Unit> createLongRangeUnit(int dx, int dy);
    std::shared_ptr<Unit> createDynamicRangeUnit(int dx, int dy);

    void baseInfo();
    
    virtual void update() override;
    virtual std::shared_ptr<Unit> clone() override;
    
private:
    int generateRandomNum(int end) const;
    std::shared_ptr<Unit> createUnit(std::shared_ptr<Unit> unit);

private:
    UnitCreator creator;
    size_t numberOfUnits;
};

#endif /* base_hpp */
