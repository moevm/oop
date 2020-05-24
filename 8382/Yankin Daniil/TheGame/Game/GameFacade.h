#pragma once

#include <queue>
#include <stack>
#include "UI/ModifiedScene.h"
#include "UI/VisualItem.h"
#include "Trivia/Point.h"

class Game;
class Cell;
class Object;
class ILandscape;
class IUnit;
class Base;
class NeutralContext;


class GameFacade
{
    friend class Game;
    friend class GameMediator;
    friend class RouteHandler;

public:
    ~GameFacade();

    void setScene(std::shared_ptr<ModifiedScene> scene);
    void userCommand(uint16_t uiCommand, Object* object, uint16_t parameter = 0);

    static bool cellMovementComparator(std::pair <Cell*, std::pair<Cell*, uint16_t>>& one, std::pair <Cell*, std::pair<Cell*, uint16_t>>& two);

private:
    GameFacade(Game* game);
    void clear();

    void addLandToScene();
    void addUnitsToScene();
    void addBasesToScene();
    void addBuldingsToScene();

    void addVisualItemToScene(VisualItem* item);
    void setVisualLandPos(ILandscape* landscape);
    void setVisualUnitPos(IUnit* unit);
    void setVisualBasePos(Base* base);
    void setVisualBuildingPos(NeutralContext* building);

    void setCellMovementMap(IUnit* unit);
    void cellMovementProcessing(uint16_t movePoints, Point oldPoint, Point newPoint, std::vector <std::pair<Cell*, std::pair<Cell*, uint16_t>>>& cellQueue);
    void getRoute(Point start, Point finish, std::vector <Point>& routeVector);

    void unitWasDestructed(IUnit* unit);
    void baseWasDestructed(Base* base);


    Game* game;
    std::shared_ptr<ModifiedScene> scene;

    Object* selectedObject;
    std::map <Cell*, std::pair<Cell*, uint16_t>> cellMovementMap;

    std::vector <std::vector <VisualItem*>> visualLandVector;
    std::map <IUnit*, VisualItem*> visualUnitMap;
    std::map <Base*, VisualItem*> visualBaseMap;
    std::map <NeutralContext*, VisualItem*> visualBuildingMap;
};
