#ifndef OOP_GAMEBASE_H
#define OOP_GAMEBASE_H

#include <cstddef>

#include "Units/ObjectFactory.h"
#include "InformationHeaders/constPar.h"
#include "InformationHeaders/unitPar.h"
#include "InformationHeaders/commandPar.h"
#include "Units/CompositeUnit.h"
#include "UnitStorekeeper.h"
#include "AuxiliaryFunctionality/EnumToString.h"
#include "AuxiliaryFunctionality/UnitObserver.h"

typedef cds::ObjectFactory<Unit, eUnitsType> UnitFabric;

class GameBase : public UnitObserver, public std::enable_shared_from_this<GameBase>
{
protected:
    size_t health{BASE_HEALTH};
    UnitFabric unitFabric;
    std::unique_ptr<UnitStorekeeper> unitCount{};
    std::vector<std::shared_ptr<CompositeUnit>> army{};

public:
    virtual ~GameBase() = default;
    virtual eBaseType getBaseType();
    void initUnitCount();
    template<class T>
    void registerNewUnitType(eUnitsType typeID)
    {
        unitFabric.add<T>(typeID);
    }
    virtual void describeYourself();
    virtual std::string getInformationAbout();
    std::shared_ptr<Unit> getUnit(eUnitsType typeID);
    std::shared_ptr<CompositeUnit> createLegion();
    std::shared_ptr<CompositeUnit> createSquad(eUnitsType, size_t quantity);
    void updateAfterDeath(std::shared_ptr<Unit> corpse, size_t x, size_t y) override;

    size_t getHealth();
    std::string getUnitCountInf();

    std::shared_ptr<BaseParametersCaretaker> createMemento();
    void restoreMemento(std::shared_ptr<BaseParametersCaretaker> memento);

    static std::string convertEnumBaseNameToStr(eBaseType type);
};

#endif //OOP_GAMEBASE_H
