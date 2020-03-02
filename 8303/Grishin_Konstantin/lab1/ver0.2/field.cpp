#include "field.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <map>


#include "Units/unit.h"
#include "abstractcombatfactory.h"
#include "objectcontainer.h"

#include "point.h"
#include "cellgrid.h"
#include "cell.h"


void Field::calculatePossibleWays(){
    struct Vertex{
        Cell *cell;
        float power;
    };

    std::vector<Vertex> vStepConductor;
    vStepConductor.push_back(Vertex{markedUnit->getCell(),
                                    markedUnit->steps()});

    while(!vStepConductor.empty()){
        auto vertex = vStepConductor.back();

        bool isIn = 0;
        for(auto cell: possibleWays){
            if(cell == vertex.cell)
                isIn = 1;
        }
        if(!isIn)
            possibleWays.push_back(vertex.cell);

        vStepConductor.pop_back();

        if(vertex.power > 0 ){
            Cell *neighbours[4];

            // UPPER CELL
            neighbours[0] = grid->getCell(vertex.cell->getPoint().x,
                                          vertex.cell->getPoint().y - 1);
            // LOWER CELL
            neighbours[1] = grid->getCell(vertex.cell->getPoint().x,
                                          vertex.cell->getPoint().y + 1);
            // LEFT CELL
            neighbours[2] = grid->getCell(vertex.cell->getPoint().x - 1,
                                          vertex.cell->getPoint().y);
            // RIGHT CELL
            neighbours[3] = grid->getCell(vertex.cell->getPoint().x + 1,
                                          vertex.cell->getPoint().y);

            for(int i = 0; i < 4; i++){
                if(neighbours[i] != nullptr)
                    if(neighbours[i]->getType() == Cell::Open){
                        vStepConductor.push_back(Vertex{neighbours[i], vertex.power - neighbours[i]->getMoveModifier()});
                        if(vStepConductor.back().power < 0)
                            vStepConductor.pop_back();
                    }
            }
        }
    }
    if(!possibleWays.empty()){
        possibleWays.erase(possibleWays.begin());
    }
}


Field::Field(unsigned int iWidth, unsigned int iHeight):
    iWidth(iWidth), iHeight(iHeight),
    iMaxUnits(static_cast<unsigned int>(iWidth*iHeight*0.8f))
{
    grid = new CellGrid(iWidth, iHeight);

    objects = new ObjectContainer;
    bluObjects = new ObjectContainer;
    redObjects = new ObjectContainer;

    bluCF = new BluCombatFactory;
    redCF = new RedCombatFactory;
}


Field::Field(const Field& field):
    Field(unsigned(field.getSize().x), unsigned(field.getSize().y))
{
    for(unsigned int i = 0; i < field.objects->length(); i++){
        auto src_obj = (*field.objects)[i];
        auto dst_obj = src_obj->copy(grid);
        if(dst_obj->getTeam() == Object::Blu){
            bluObjects->pushBack(dst_obj);
        }
        if(dst_obj->getTeam() == Object::Red){
            redObjects->pushBack(dst_obj);
        }
        objects->pushBack(dst_obj);
    }
}


Field::Field(Field&& other):
    iWidth(other.iWidth), iHeight(other.iHeight), iMaxUnits(other.iMaxUnits)
{
    this->grid = other.grid;
    other.grid = nullptr;

    this->objects = other.objects;
    other.objects = nullptr;

    this->bluObjects = other.bluObjects;
    other.bluObjects = nullptr;

    this->redObjects = other.redObjects;
    other.redObjects = nullptr;

    this->bluCF = other.bluCF;
    other.bluCF = nullptr;

    this->redCF = other.redCF;
    other.redCF = nullptr;

    this->markedUnit = other.markedUnit;
    other.markedUnit = nullptr;

    for(auto cell: other.possibleWays){
        this->possibleWays.push_back(cell);
    }

    other.possibleWays.clear();
}


Field::~Field(){
    delete grid;

    delete objects;
    delete bluObjects;
    delete redObjects;

    delete bluCF;
    delete redCF;
}


Point2i Field::getSize() const
{
    return Point2i(int(iWidth), int(iHeight));
}


Point2i Field::getPointFromPixels(sf::RenderTarget *target, int x_pix, int y_pix){
    if(x_pix < 0) x_pix = 0;
    if(x_pix >= int(target->getSize().x)) x_pix = int(target->getSize().x) - 1;
    if(y_pix < 0) y_pix = 0;
    if(y_pix >= int(target->getSize().y)) y_pix = int(target->getSize().y) - 1;

    auto p_vector = target->mapPixelToCoords(sf::Vector2i(x_pix, y_pix));
    p_vector.x /= cell_size;
    p_vector.y /= cell_size;

    if(p_vector.x < 0) p_vector.x = 0;
    if(p_vector.x >= getSize().x) p_vector.x = getSize().x - 1;
    if(p_vector.y < 0) p_vector.y = 0;
    if(p_vector.y >= getSize().y) p_vector.y = getSize().y - 1;

    return Point2i{int(p_vector.x), int(p_vector.y)};
}


void Field::createUnit(const std::string &id, int x, int y, bool bPosType){

    if(bPosType == PIXELS){
        x = x/cell_size;
        y = y/cell_size;
    }

    if(objects->length() == iMaxUnits)
        return;

    auto cell = grid->getCell(x, y);
    if(cell->getObject() != nullptr){
        std::cout << "cell ain't empty" << std::endl;
        return;
    }

    if(id == "BluArcher"){
        auto archer = bluCF->createArcher(cell, "bow");
        if(archer != nullptr){
            objects->pushBack(archer);
            bluObjects->pushBack(archer);
        }
        return;
    }

    if(id == "BluBarbarian"){
        auto barbarian = bluCF->createBarbarian(cell, "club");
        if(barbarian != nullptr){
            objects->pushBack(barbarian);
            bluObjects->pushBack(barbarian);
        }
        return;
    }

    if(id == "BluBerserker"){
        auto berserker = bluCF->createBerserker(cell, "scythe");
        if(berserker != nullptr){
            objects->pushBack(berserker);
            bluObjects->pushBack(berserker);
        }
        return;
    }

    if(id == "RedArcher"){
        auto archer = redCF->createArcher(cell, "bow");
        if(archer != nullptr){
            objects->pushBack(archer);
            bluObjects->pushBack(archer);
        }
        return;
    }

    if(id == "RedBarbarian"){
        auto barbarian = redCF->createBarbarian(cell, "club");
        if(barbarian != nullptr){
            objects->pushBack(barbarian);
            bluObjects->pushBack(barbarian);
        }
        return;
    }

    if(id == "RedBerserker"){
        auto berserker = redCF->createBerserker(cell, "scythe");
        if(berserker != nullptr){
            objects->pushBack(berserker);
            bluObjects->pushBack(berserker);
        }
        return;
    }
}


void Field::deleteUnit(int x, int y, bool bPosType){
    if(bPosType == PIXELS){
        x = x/cell_size;
        y = y/cell_size;
    }

    auto toDel = grid->getCell(x, y)->pullObject();
    objects->remove(toDel);
    bluObjects->remove(toDel);
    redObjects->remove(toDel);
    delete toDel;
}


void Field::draw(sf::RenderTarget *target){
    for(int y = 0; y < int(iHeight); y++){
        for(int x = 0; x < int(iWidth); x++){
            grid->getCell(x, y)->draw(target, Point2i{x * cell_size, y * cell_size}, cell_size);
        }
    }

    for(int i = 0; i < objects->length(); i++){
        (*objects)[i]->draw(target, cell_size);
    }
}


void Field::lightSpotedUnit(sf::RenderTarget *target){
    if(markedUnit == nullptr)
        return;

    sf::CircleShape spotLight(5);
    spotLight.setOrigin(spotLight.getRadius(), spotLight.getRadius());

    spotLight.setFillColor(sf::Color::White);
    spotLight.setOutlineThickness(1);
    spotLight.setOutlineColor(sf::Color::Black);

    spotLight.setPosition((markedUnit->getPos().x + 0.5f) * cell_size,
                          (markedUnit->getPos().y + 0.5f) * cell_size);

    target->draw(spotLight);
}


void Field::lightPossibleWays(sf::RenderTarget *target){
    for(auto cell: possibleWays){
        sf::RectangleShape spotLight(sf::Vector2f(cell_size-4, cell_size-4));
        spotLight.setOrigin(spotLight.getSize().x * 0.5f, spotLight.getSize().y * 0.5f);
        spotLight.setPosition((cell->getPoint().x + 0.5f) * cell_size,
                              (cell->getPoint().y + 0.5f) * cell_size);
        spotLight.setOutlineThickness(2);

        spotLight.setFillColor(sf::Color(0x67, 0xF2, 0xB3, 178));
        spotLight.setOutlineColor(sf::Color(0x00, 0x80, 0x00, 200));

        target->draw(spotLight);
    }
}


void Field::spotCell(sf::RenderTarget *target, int x, int y, bool bPosType){

    if(bPosType == PIXELS){
        x = x/cell_size;
        y = y/cell_size;
    }

    sf::RectangleShape cell_shape(sf::Vector2f(cell_size*0.8f, cell_size*0.8f));
    cell_shape.setOrigin(cell_size*0.4f, cell_size*0.4f);
    cell_shape.setPosition((x + 0.5f) * cell_size, (y + 0.5f) * cell_size);

    cell_shape.setOutlineThickness(2);
    cell_shape.setOutlineColor(sf::Color(0xFF, 0xFF, 0xFF, 0x80));
    cell_shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, 0x96));

    target->draw(cell_shape);
}


void Field::spotUnit(Object::Team team, int x, int y, bool bPosType){

    if(bPosType == PIXELS){
        x = x/cell_size;
        y = y/cell_size;
    }

    Object* onCell = grid->getCell(x, y)->getObject();
    if(onCell == nullptr)
        return;

    if(onCell->getObjectType() != Object::Unit)
        return;

    if(team == Object::Red && onCell->getTeam() != Object::Red)
        return;

    if(team == Object::Blu && onCell->getTeam() != Object::Blu)
        return;

    possibleWays.clear();

    if(onCell == markedUnit){
        markedUnit = nullptr;
        return;
    }

    markedUnit = dynamic_cast<Unit*>(onCell);
    calculatePossibleWays();
}


void Field::clearSelection(){
    markedUnit = nullptr;
    possibleWays.clear();
}


void Field::moveSpottedUnit(int x, int y, bool bPosType){
    if(markedUnit == nullptr)
        return;

    if(bPosType == PIXELS){
        x = x/cell_size;
        y = y/cell_size;
    }

    if(markedUnit->getPos().x == x &&
       markedUnit->getPos().y == y)
        return;


    for(auto cell: possibleWays){
        if(cell->getPoint() == Point2i{x, y} && cell->getObject() == nullptr){
            markedUnit->move(cell);
            possibleWays.clear();
            calculatePossibleWays();
            return;
        }
    }
}


void Field::refresh(){
    for(int i = 0; i < objects->length(); i++){
        if((*objects)[i]->getObjectType() == Object::Type::Unit){
            dynamic_cast<Unit*>((*objects)[i])->updateSteps();
        }
    }
    iTurns++;
}


int Field::turnsPassed() const{
    return iTurns;
}






