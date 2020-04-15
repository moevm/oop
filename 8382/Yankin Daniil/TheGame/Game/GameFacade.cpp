#include "GameFacade.h"
#include "Game.h"
#include "Command/Command.h"
#include "Landscape/LandscapeHeader.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Neutrals/NeutralContext.h"
#include "Handler/UnitActionHandler.h"


GameFacade::GameFacade(Game* game) {
    this->game = game;
    scene = nullptr;
}

GameFacade::~GameFacade() {
    cellMovementMap.clear();
    visualLandVector.clear();
    visualUnitMap.clear();
    visualBaseMap.clear();
    visualBuildingMap.clear();
}



void GameFacade::setScene(ModifiedScene* scene) {
    if (game->field != nullptr && scene != nullptr) {
        this->scene = scene;
    }

    addLandToScene();
    addUnitsToScene();
    addBasesToScene();
    addBuldingsToScene();

    this->scene->showTurn();
}

void GameFacade::addLandToScene() {
    if (scene == nullptr)
        return;

    Field* field = game->field;

    visualLandVector.resize(field->getHeight());

    for (uint16_t i = 0; i < field->getHeight(); i++) {
        visualLandVector[i].resize(field->getWidth(), nullptr);

        for (uint16_t j = 0; j < field->getWidth(); j++) {
            visualLandVector[i][j] = new VisualItem(field->getLandscape(Point(j, i)));
            addVisualItemToScene(visualLandVector[i][j]);
            setVisualLandPos(field->getLandscape(Point(j, i)));
        }
    }
}

void GameFacade::addUnitsToScene() {
    if (scene == nullptr)
        return;

    for (auto player = game->playerVector.begin(); player != game->playerVector.end(); player++) {
        auto unitSet = (*player)->getUnitSet();

        for (auto unit = unitSet->begin(); unit != unitSet->end(); unit++) {
            VisualItem* unitItem = new VisualItem(*unit);

            visualUnitMap.insert(std::make_pair(*unit, unitItem));

            addVisualItemToScene(unitItem);
            setVisualUnitPos(*unit);
        }
    }
}

void GameFacade::addBasesToScene() {
    if (scene == nullptr)
        return;

    for (auto player = game->playerVector.begin(); player != game->playerVector.end(); player++) {
        auto baseSet = (*player)->getBaseSet();

        for (auto base = baseSet->begin(); base != baseSet->end(); base++) {
            VisualItem* baseItem = new VisualItem(*base);

            visualBaseMap.insert(std::pair <Base*, VisualItem*> (*base, baseItem));

            addVisualItemToScene(baseItem);
            setVisualBasePos(*base);
        }
    }
}

void GameFacade::addBuldingsToScene() {
    if (scene == nullptr)
        return;

    auto buildingSet = game->neutralPlayer->getNeutralObjectSet();

    for (auto building = buildingSet->begin(); building != buildingSet->end(); building++) {
        VisualItem* buildingItem = new VisualItem(static_cast <Object*> (*building) );

        visualBuildingMap.insert(std::make_pair(*building, buildingItem));

        addVisualItemToScene(buildingItem);
        setVisualBuildingPos(*building);
    }
}



void GameFacade::addVisualItemToScene(VisualItem* item) {
    if (scene == nullptr)
        return;

    scene->addItem(item);
    item->setPos(0, 0);
}

void GameFacade::setVisualLandPos(ILandscape* landscape) {
    if (scene == nullptr)
        return;

    Point point = landscape->getPoint();
    VisualItem* landItem = visualLandVector[point.getY()][point.getX()];

    uint16_t itemWidth = landItem->pixmap().width();
    uint16_t itemHeight = landItem->pixmap().height();

    if (point.getY() % 2 == 0)
        landItem->setPos(point.getX() * itemWidth, point.getY() * itemHeight*3/4);
    else
        landItem->setPos(point.getX() * itemWidth + itemWidth/2, point.getY() * itemHeight*3/4);
}

void GameFacade::setVisualUnitPos(IUnit* unit) {
    if (scene == nullptr)
        return;

    if (visualUnitMap.find(unit) == visualUnitMap.end()) {
        visualUnitMap[unit] = new VisualItem(unit);
        scene->addItem(visualUnitMap[unit]);
    }

    VisualItem* unitItem = visualUnitMap[unit];
    VisualItem* landItem = visualLandVector[unit->getPoint().getY()][unit->getPoint().getX()];

    uint16_t landX = landItem->x();
    uint16_t landY = landItem->y();

    uint16_t landWidth = landItem->pixmap().width();
    uint16_t landHeight = landItem->pixmap().height();

    unitItem->setPos(landX + landWidth/2, landY + landHeight/3);

    if (unit == selectedObject) {
        setCellMovementMap(unit);
        scene->showAttributes(selectedObject);
    }
}

void GameFacade::setVisualBasePos(Base* base) {
    if (scene == nullptr)
        return;

    VisualItem* baseItem = visualBaseMap[base];
    VisualItem* landItem = visualLandVector[base->getPoint().getY()][base->getPoint().getX()];

    uint16_t landX = landItem->x();
    uint16_t landY = landItem->y();

    uint16_t landWidth = landItem->pixmap().width();
    uint16_t landHeight = landItem->pixmap().height();

    baseItem->setPos(landX + landWidth/5, landY + landHeight/3*2);
}

void GameFacade::setVisualBuildingPos(NeutralContext* building) {
    if (scene == nullptr)
        return;

    VisualItem* buildingItem = visualBuildingMap[building];
    VisualItem* landItem = visualLandVector[building->getPoint().getY()][building->getPoint().getX()];

    uint16_t landX = landItem->x();
    uint16_t landY = landItem->y();

    uint16_t landWidth = landItem->pixmap().width();
    uint16_t landHeight = landItem->pixmap().height();

    buildingItem->setPos(landX + landWidth/5 * 2, landY + landHeight/3 *2);
}



void GameFacade::userCommand(uint8_t uiCommand, Object* object, uint8_t parameter) {
    // Выделение оъекта
    if (uiCommand == UI_SELECT_OBJECT) {
        scene->showTurn();
        scene->hideAttributes();
        scene->hideBase();

        if (object->getGroupType() == BASE || object->getGroupType() == UNIT) {
            scene->hideTurn();
            scene->hideBase();

            selectedObject = object;
            scene->showAttributes(object);

            if (object->getGroupType() == BASE) {
                scene->showBase(static_cast <Base*> (object));
            }

            else if (object->getGroupType() == UNIT) {
                setCellMovementMap(static_cast <Unit*> (object));
            }
        }
    }

    else if (uiCommand == UI_INTERACT_OBJECT) {
        if (selectedObject == nullptr || selectedObject->getGroupType() != UNIT)
            return;

        UnitActionHandler handler;
        handler.handle(static_cast<IUnit*>(selectedObject), object);
    }

    // Создание юнитов базой
    else if (uiCommand == UI_PRODUCE) {
        Base* base = static_cast <Base*> (selectedObject);
        BaseProduceCommand command(base, parameter);
        command.execute();
        scene->showAttributes(selectedObject);
    }
}



void GameFacade::setCellMovementMap(IUnit* unit) {
    Field* field = game->field;

    Cell* cell = field->getCell(unit->getPoint());
    Cell* prevCell = nullptr;
    uint8_t balance = unit->getMovePoints();

    cellMovementMap.clear();

    std::vector <std::pair<Cell*, std::pair<Cell*, uint8_t>>> cellQueue;
    cellQueue.push_back(std::make_pair(cell, std::make_pair(prevCell, balance)));

    while (!cellQueue.empty()) {
        cell = cellQueue.back().first;
        std::tie(prevCell, balance) = cellQueue.back().second;
        cellQueue.pop_back();

        cellMovementMap.insert(std::make_pair(cell, std::make_pair(prevCell, balance)));


        if (cell->getPoint() != unit->getPoint() && (!cell->isUnitFree() || (cell->getBuildingGroupType() == BASE && cell->getBase()->getPlayer() != unit->getPlayer()))) {
            continue;
        }


        Point currentPoint = cell->getPoint();
        uint16_t x = currentPoint.getX();
        uint16_t y = currentPoint.getY();


        Point newPoint(0, 0);
        if (balance > 0) {
            newPoint = Point(x - 1, y);
            if (x > 0 && field->getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
            }

            newPoint = Point(x + 1, y);
            if (x < field->getWidth() - 1 && field->getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
            }

            newPoint = Point(x, y - 1);
            if (y > 0 && field->getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
            }

            newPoint = Point(x, y + 1);
            if (y < field->getHeight() - 1 && field->getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
            }


            if (y % 2 == 0) {
                newPoint = Point(x - 1, y - 1);
                if (x > 0 && y > 0 && field->getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
                }

                newPoint = Point(x - 1, y + 1);
                if (x > 0 && y < field->getHeight() - 1 && field->getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
                }
            }
            else {
                newPoint = Point(x + 1, y - 1);
                if (x < field->getWidth() - 1 && y > 0 && field->getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
                }

                newPoint = Point(x + 1, y + 1);
                if (x < field->getWidth() - 1 && y < field->getHeight() - 1 && field->getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(balance, currentPoint, newPoint, cellQueue);
                }
            }
        }
        std::sort(cellQueue.begin(), cellQueue.end(), GameFacade::cellMovementComparator);
    }
}

void GameFacade::cellMovementProcessing(uint8_t balance, Point oldPoint, Point newPoint, std::vector <std::pair<Cell*, std::pair<Cell*, uint8_t>>>& cellQueue) {
    Field* field = game->field;
    uint8_t movementCost = field->getLandscape(newPoint)->getMovementCost();

    Cell* oldCell = field->getCell(oldPoint);
    Cell* newCell = field->getCell(newPoint);

    if (cellMovementMap.find(newCell) != cellMovementMap.end())
        return;

    for (auto elem = cellQueue.begin(); elem != cellQueue.end(); elem++) {
        if (elem->first == newCell) {
            if (elem->second.second < balance - movementCost) {
                elem->second = std::make_pair(oldCell, std::max(balance - movementCost, 0));
            }
            return;
        }
    }

    cellQueue.push_back(std::make_pair(newCell, std::make_pair(oldCell, std::max(balance - movementCost, 0))));
}

bool GameFacade::cellMovementComparator(std::pair <Cell*, std::pair<Cell*, uint8_t>>& one, std::pair <Cell*, std::pair<Cell*, uint8_t>>& two) {
    if (one.second.second < two.second.second)
        return true;
    return false;
}

void GameFacade::getRoute(Point start, Point finish, std::vector <Point>& route) {
    Cell* finishCell = game->field->getCell(finish);

    if (cellMovementMap.find(finishCell) == cellMovementMap.end())
        return;

    route.push_back(finish);

    while (route.back() != start) {
        finishCell = cellMovementMap.find(finishCell)->second.first;
        finish = finishCell->getPoint();
        route.push_back(finish);
    }
    route.pop_back();
}



void GameFacade::unitWasDestructed(IUnit* unit) {
    if (scene == nullptr)
        return;

    if (unit == selectedObject) {
        scene->hideAttributes();
        selectedObject = nullptr;
    }

    VisualItem* unitItem = visualUnitMap[unit];
    delete unitItem;

    visualUnitMap.erase(unit);
}

void GameFacade::baseWasDestructed(Base* base) {
    if (scene == nullptr)
        return;

    if (base == selectedObject) {
        scene->hideAttributes();
        scene->hideBase();
        selectedObject = nullptr;
    }

    VisualItem* baseItem = visualBaseMap[base];
    delete baseItem;

    visualBaseMap.erase(base);
}
