#include "GameFieldProxy.h"

GameFieldProxy::GameFieldProxy(size_t width_, size_t height_, bool fill)
{
    field = std::make_shared<GameField>(width_, height_);

    initLandscapeFabric();
    initTerrain();

    initNeutralObjectFabric();
    initArtifactMap();

    if(fill)
    {
        fillTerrainByRandom();
        fillArtifactMapByRandom();
    }

    context = std::make_unique<NeutralObjectContext>();
}

size_t GameFieldProxy::getWidth() const
{
    return field->getWidth();
}

size_t GameFieldProxy::getHeight() const
{
    return field->getHeight();
}

void GameFieldProxy::addUnit(const std::shared_ptr<Unit> &unit, size_t x, size_t y)
{
    moveMediator = std::make_shared<UnitMoveMediator>(shared_from_this(), unit);
    moveMediator->connectWithUnit();

    meleeAttackMediator = std::make_shared<UnitMeleeAttackMediator>(shared_from_this(), unit);
    meleeAttackMediator->connectWithUnit();

    field->addUnit(unit, x, y);
}

void GameFieldProxy::addBase(const std::shared_ptr<GameBase> &base, size_t x, size_t y)
{
    field->addBase(base, x, y);
}

void GameFieldProxy::delUnit(size_t x, size_t y)
{
    field->delUnit(x, y);
}

bool GameFieldProxy::isCellFreeForUnit(size_t x, size_t y)
{
    return field->isCellFreeForUnit(x, y);
}

bool GameFieldProxy::isCellFreeForBase(size_t x, size_t y)
{
    return field->isCellFreeForBase(x, y);
}

void GameFieldProxy::informationAboutCell(size_t x, size_t y)
{
    field->informationAboutCell(x, y);
}

void GameFieldProxy::moveUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y)
{
    Coords check(x, y);
    std::shared_ptr<Unit> tempForNeutralObject;
    if(terrain[check]->isAccessibleForMove(sender))
    {
        tempForNeutralObject = sender;
        field->moveUnit(sender, x, y);
    }
    else
    {
        throw std::invalid_argument("Current unit can't move on this type of landscape");
    }

    if(artifactMap[check] != nullptr)
    {
        context->setObject(artifactMap[check]);
        *context+=tempForNeutralObject;
    }
}

void GameFieldProxy::getTotalInformation()
{
    field->getTotalInformation();
}

void GameFieldProxy::initLandscapeFabric()
{
    landscapeFabric.add<Champaign>("Champaign");
    landscapeFabric.add<Forest>("Forest");
    landscapeFabric.add<Mountains>("Mountains");
}

void GameFieldProxy::initTerrain()
{
    landscapeTypes.insert(std::make_pair<std::string, std::shared_ptr<Landscape>>
            ("Champaign", landscapeFabric.create("Champaign")));
    landscapeTypes.insert(std::make_pair<std::string, std::shared_ptr<Landscape>>
            ("Forest", landscapeFabric.create("Forest")));
    landscapeTypes.insert(std::make_pair<std::string, std::shared_ptr<Landscape>>
            ("Mountains", landscapeFabric.create("Mountains")));
}

void GameFieldProxy::fillTerrainByRandom()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, LANDSCAPE_GENERATION_RAND);
    for(size_t i = 0; i < field->getHeight(); i++)
    {
        for(size_t j = 0; j < field->getWidth(); j++)
        {
            if(j % 3 == 0 && dist(mt) == 1 && j != 0)
            {
                terrain.insert(std::make_pair(Coords(i, j), landscapeTypes["Forest"]));
            }
            else if (j % 5 == 0 && dist(mt) == 1 && j != 0)
            {
                terrain.insert(std::make_pair(Coords(i, j), landscapeTypes["Mountains"]));
            }
            else
            {
                terrain.insert(std::make_pair(Coords(i, j), landscapeTypes["Champaign"]));
            }
        }
    }
}

void GameFieldProxy::fillArtifactMapByRandom()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, NEUTRAL_OBJECT_GENERATION_RAND);
    for(size_t i = 0; i < field->getHeight(); i++)
    {
        for (size_t j = 0; j < field->getWidth(); j++)
        {
            if(j % 7 == 0 && j != 0)
            {
                switch (dist(mt))
                {
                    case 1:
                        artifactMap.insert(std::make_pair(Coords(i, j), neutralObjectTypes["Enchanted Robe"]));
                        break;
                    case 2:
                        artifactMap.insert(std::make_pair(Coords(i, j), neutralObjectTypes["Energy Potion"]));
                        break;
                    case 3:
                        artifactMap.insert(std::make_pair(Coords(i, j), neutralObjectTypes["Legendary Weapon"]));
                        break;
                    case 4:
                        artifactMap.insert(std::make_pair(Coords(i, j), neutralObjectTypes["Poison"]));
                        break;
                }
            }
            else
            {
                artifactMap.insert(std::make_pair(Coords(i, j), nullptr));
            }
        }
    }
}

void GameFieldProxy::initNeutralObjectFabric()
{
    neutralObjectFabric.add<EnchantedRobe>("Enchanted Robe");
    neutralObjectFabric.add<EnergyPotion>("Energy Potion");
    neutralObjectFabric.add<LegendaryWeapon>("Legendary Weapon");
    neutralObjectFabric.add<Poison>("Poison");
}

void GameFieldProxy::initArtifactMap()
{
    neutralObjectTypes.insert(std::make_pair<std::string, std::shared_ptr<NeutralObject>>
            ("Enchanted Robe", neutralObjectFabric.create("Enchanted Robe")));
    neutralObjectTypes.insert(std::make_pair<std::string, std::shared_ptr<NeutralObject>>
            ("Energy Potion", neutralObjectFabric.create("Energy Potion")));
    neutralObjectTypes.insert(std::make_pair<std::string, std::shared_ptr<NeutralObject>>
                                      ("Legendary Weapon", neutralObjectFabric.create("Legendary Weapon")));
    neutralObjectTypes.insert(std::make_pair<std::string, std::shared_ptr<NeutralObject>>
                                      ("Poison", neutralObjectFabric.create("Poison")));
}

void GameFieldProxy::meleeAttackUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y)
{
    Coords attackCoords(x, y);
    if(terrain[sender->getCoords()]->isAccessibleForAttack(sender->getType()))
    {
        field->meleeAttackUnit(sender, x, y);
    }
    else
    {
        throw std::invalid_argument("For this type of unit it's impossible to attack from this landscape");
    }
}

std::string GameFieldProxy::getInfAboutItem(size_t x, size_t y)
{
    std::string res = "On possition (" + std::to_string(x) + ";" + std::to_string(y) + ") there are ";
    Coords coords(x, y);
    return res + artifactMap[coords]->getNameOfNeutralObject();
}

std::string GameFieldProxy::getInfAboutLand(size_t x, size_t y)
{
    std::string res = "On possition (" + std::to_string(x) + ";" + std::to_string(y) + ") there are ";
    Coords coords(x, y);
    return res + terrain[coords]->getNameOfLandscape();
}

std::shared_ptr<GameBase> GameFieldProxy::getBaseByCoords(size_t x, size_t y)
{
    return field->getBaseByCoords(x, y);
}

std::shared_ptr<Unit> GameFieldProxy::getUnitByCoords(size_t x, size_t y)
{
    return field->getUnitByCoords(x, y);
}

void GameFieldProxy::moveUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDest)
{
    field->moveUnit(xSource, ySource, xDest, yDest);
}

void GameFieldProxy::meleeAttackUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDest)
{
    field->meleeAttackUnit(xSource, ySource, xDest, yDest);
}

std::string GameFieldProxy::getInfAboutBase(size_t xDest, size_t yDest)
{
    return field->getInfAboutBase(xDest, yDest);
}

std::string GameFieldProxy::getInfAboutUnit(size_t xDest, size_t yDest)
{
    return field->getInfAboutUnit(xDest, yDest);
}

std::shared_ptr<FieldProxyParametersMemento> GameFieldProxy::createMemento()
{
    std::shared_ptr<FieldProxyParametersMemento> memento = std::make_shared<FieldProxyParametersMemento>();

    memento->fieldParam = field->createMemento();

    for(const auto& curr : terrain)
    {
        memento->landscape.insert(std::pair(Coords(curr.first.x, curr.first.y), curr.second->getNameOfLandscape()));
    }
    for(const auto& curr : artifactMap)
    {
        if(curr.second == nullptr) continue;
        memento->neutralObjects.insert(std::pair(Coords(curr.first.x, curr.first.y), curr.second->getNameOfNeutralObject()));
    }

    return memento;
}

void GameFieldProxy::restoreMemento(std::shared_ptr<FieldProxyParametersMemento> memento)
{
    field->restoreMemento(memento->fieldParam);

    for(const auto& curr : memento->landscape)
    {
        terrain.insert(std::pair(curr.first, landscapeTypes[curr.second]));
    }
    for(const auto& curr : memento->neutralObjects)
    {
        artifactMap.insert(std::pair(curr.first, neutralObjectTypes[curr.second]));
    }
}
