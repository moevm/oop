#include "Field.h"
#include "Base.h"
#include "DrinkStamina.h"
#include "Poisen.h"
#include "Potion.h"
#include "DrinkStrong.h"

Field::Field(int x, int y, int maxCountObject): lenghtX(x), lengthY(y), maxCountObject(maxCountObject), countUnit(0){

    mapCell = new Cell**[this->lengthY];
        for (int i=0; i<this->lengthY; i++) {
            mapCell[i] = new Cell *[x];
            for (int j=0; j<this->lenghtX; j++) {
                mapCell[i][j] = new Cell;
                mapCell[i][j]->x = j;
                mapCell[i][j]->y = i;
                mapCell[i][j]->unit = nullptr;
                mapCell[i][j]->base = nullptr;
                mapCell[i][j]->neutralObject = nullptr;
            }
        }

    }

    Field::Field(const Field& field) : lenghtX(field.lenghtX), lengthY(field.lengthY), maxCountObject(field.maxCountObject), countUnit(field.countUnit), mapCell(new Cell**[field.lengthY]){
        for (int i=0; i<field.lengthY; i++) {
            mapCell[i] = new Cell *[field.lenghtX];
            for (int j=0; j<field.lenghtX; j++) {
                mapCell[i][j] = field.mapCell[i][j];
            }
        }
    }

    Field::Field(Field&& field) : lenghtX(field.lenghtX), lengthY(field.lengthY), maxCountObject(field.maxCountObject), countUnit(field.countUnit), mapCell(new Cell**[field.lengthY]){
        for (int i=0; i<field.lengthY; i++) {
            mapCell[i] = new Cell *[field.lenghtX];
            for (int j=0; j<field.lenghtX; j++)
                mapCell[i][j] = field.mapCell[i][j];
        }

        for (int i=0; i<field.lengthY; i++)
            delete[] field.mapCell[i];
        delete[] field.mapCell;
    }


    bool Field::addUnit(Unit* unit, int unitX, int unitY){
        if (unitX < this->lenghtX   &&   unitY < this->lengthY   &&   this->countUnit < this->maxCountObject  && (!mapCell[unitY][unitX]->unit) && mapCell[unitY][unitX]->landscape->isMoved(unit)) {
            mapCell[unitY][unitX]->unit = unit;
            this->countUnit++;
            return true;
        }
        return false;
    }


    void Field::removeUnit(Unit* unit){
        for (int i=0; i<this->lengthY; i++){
            for (int j=0; j<this->lenghtX; j++)
                if (mapCell[i][j]->unit == unit){
                    mapCell[i][j]->unit = nullptr;
                    this->countUnit--;
                    return;
                }
        }
    }

    void Field::printAll(){
        for (int i=0; i<this->lengthY; i++){
            for (int j=0; j<this->lenghtX; j++) {
                if (mapCell[i][j]->base != nullptr) {
                    std::cout << "b ";
                    continue;
                }
                if (mapCell[i][j]->unit != nullptr) {
                    std::cout <<mapCell[i][j]->unit->name<< " ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }

    void Field::addNeutral(int neutralX, int neutralY, char name) {
        if(this->lenghtX > neutralX && this->lengthY > neutralY && neutralX >= 0 && neutralY >=0 &&  (name == 'z' || name=='p' || name == 's' || name == 'a')){
            if (name == 'a'){
                mapCell[neutralY][neutralX]->neutralObject = new DrinkStaminaAction();
            }
            else if (name == 'z'){
                mapCell[neutralY][neutralX]->neutralObject = new PotionAction();
            }
            else if (name == 'p'){
                mapCell[neutralY][neutralX]->neutralObject = new PoisenAction();
            }
            else if (name == 's'){
                mapCell[neutralY][neutralX]->neutralObject = new DrinkStrongAction();
            }
        }
    }

    void Field::printNeutral(){
        for (int i=0; i<this->lengthY; i++){
            for (int j=0; j<this->lenghtX; j++) {
                if (mapCell[i][j]->neutralObject != nullptr) {
                    std::cout <<mapCell[i][j]->neutralObject->name<< " ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }


    void Field::moveUnit(Unit* unit, int unitX, int unitY) {
        if (unitX < this->lenghtX && unitY < this->lengthY && unitX >=0 && unitY >= 0 && (!mapCell[unitY][unitX]->unit) && mapCell[unitY][unitX]->landscape->isMoved(unit) && mapCell[unitY][unitX]->base != nullptr) {
            removeUnit(unit);
            addUnit(unit, unitX, unitY);
        }
    }

    Cell* Field::findUnit(Unit* unit){
        for (int i = 0; i<this->lengthY; i++){
            for (int j = 0; j < this->lenghtX; j++){
                if (mapCell[i][j]->unit == unit){
                    return mapCell[i][j];
                }
            }
        }
    }

    void Field::addLandscape(){
        for (int i=0; i<this->lengthY; i++){
            for (int j=0; j<this->lenghtX; j++){
                int randomLandscape = (i+j)%3;
                if (randomLandscape == 0)
                    mapCell[i][j]->landscape = new Wall();
                else if (randomLandscape == 1)
                    mapCell[i][j]->landscape = new Water();
                else if (randomLandscape == 2)
                    mapCell[i][j]->landscape = new Ground();
            }
        }
    }

    void Field::printLandscape(){
        for (int i=0; i<this->lengthY; i++){
            for (int j=0; j<this->lenghtX; j++){
                std::cout << mapCell[i][j]->landscape->getNameLandscape() << " ";
            }
            std::cout << std::endl;
        }
    }

    void Field::moveUnitLeft(Unit* unit){
        Cell* bufCell = this->findUnit(unit);
        moveUnit(unit, bufCell->x-1, bufCell->y);
    }

    void Field::moveUnitUp(Unit* unit){
        Cell* bufCell = this->findUnit(unit);
        moveUnit(unit, bufCell->x, bufCell->y-1);
    }

    void Field::moveUnitRight(Unit* unit){
        Cell* bufCell = this->findUnit(unit);
        moveUnit(unit, bufCell->x+1, bufCell->y);
    }

    void Field::moveUnitDown(Unit* unit){
        Cell* bufCell = this->findUnit(unit);
        moveUnit(unit, bufCell->x, bufCell->y + 1);
    }

    Base* Field::createBase(int BaseX, int BaseY, int maxCountUnit, int health){
        Base* base = new Base(this, maxCountUnit, health, BaseX, BaseY);
        mapCell[BaseY][BaseX]->base = base;
        return base;
    }








