#ifndef OOP_GAMEFIELDPROXY_H
#define OOP_GAMEFIELDPROXY_H

#include <set>
#include <random>

#include "IGameField.h"
#include "GameField.h"
#include "Coords.h"

#include "Landscape/Champaign.h"
#include "Landscape/Forest.h"
#include "Landscape/Mountains.h"

#include "NeutralObjects/NeutralObject.h"
#include "NeutralObjects/NeutralObjectContext.h"
#include "NeutralObjects/EnchantedRobe.h"
#include "NeutralObjects/EnergyPotion.h"
#include "NeutralObjects/LegendaryWeapon.h"
#include "NeutralObjects/Poison.h"

typedef cds::ObjectFactory<Landscape, std::string> LandscapeFabric;
typedef cds::ObjectFactory<NeutralObject, std::string> NeutralObjectFabric;

class GameFieldProxy : public  IGameField, public std::enable_shared_from_this<IGameField>
{
public:
    GameFieldProxy(size_t width_, size_t height_);
    ~GameFieldProxy() = default;

    [[nodiscard]] size_t getWidth() const override;
    [[nodiscard]] size_t getHeight() const override;

    void addUnit(const std::shared_ptr<Unit> &unit, size_t x, size_t y) override;
    void addBase(const std::shared_ptr<GameBase> &base, size_t x, size_t y) override;
    void delUnit(size_t x, size_t y) override;
    bool isCellFreeForUnit(size_t x, size_t y) override;
    bool isCellFreeForBase(size_t x, size_t y) override;
    void informationAboutCell(size_t x, size_t y) override;

    void moveUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y) override;
    void meleeAttackUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y) override;

    void getTotalInformation() override;
private:
    // The field for which this class is a protecting and caching proxy
    std::shared_ptr<GameField> field;

    // Landscape stuff
    LandscapeFabric landscapeFabric;
    std::map<Coords, std::shared_ptr<Landscape>> terrain;
    std::map<std::string, std::shared_ptr<Landscape>> landscapeTypes;

    // Neutral objects stuff
    NeutralObjectFabric neutralObjectFabric;
    std::map<Coords, std::shared_ptr<NeutralObject>> artifactMap;
    std::map<std::string, std::shared_ptr<NeutralObject>> neutralObjectTypes;
    std::unique_ptr<NeutralObjectContext> context;

    // moveMediator for correct unit moving
    std::shared_ptr<UnitMoveMediator> moveMediator{};

    // meleeAttackMediator for correct unit melee attack
    std::shared_ptr<UnitMeleeAttackMediator> meleeAttackMediator{};

    void initLandscapeFabric();
    void initTerrain();
    void initNeutralObjectFabric();
    void initArtifactMap();
};

#endif //OOP_GAMEFIELDPROXY_H
