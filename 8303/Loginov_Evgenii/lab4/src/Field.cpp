//
// Created by Jack on 08/03/2020.
//

#include "Field.h"
#include "Unit/Unit.h"
#include "Landscape/Landscape.h"
#include "Landscape/Water.h"
#include "Landscape/Mountain.h"
#include "Landscape/Ground.h"

#include "Neutral/damage.h"
#include "Neutral/restoreArmour.h"
#include "Neutral/restoreFuel.h"
#include "Neutral/restoreHealth.h"
#include "Neutral/none.h"

#include "Base.h"

    Field::Field(int x, int y, int maxUnit, Adapter *adapter): x(x), y(y), curUnit(0), maxUnit(maxUnit), adapter(adapter) {
//        this->x = x;
//        this->y = y;
//        this->curUnit = 0;
//        this->maxUnit = maxUnit;
        this->base = nullptr;

        cell = new Cell**[y];
        for (int i=0; i<y; i++) {
            cell[i] = new Cell* [x];
            for (int j=0; j<x; j++) {

                Landscape *l = nullptr;
                int r = rand() % 10;
                if(r<=5) l = new Ground;
                if(r==6 || r==7) l = new Mountain;
                if(r==8 || r==9) l = new Water;

                NeutralObject *obj = nullptr;
                int r2 = rand() % 10;
                if(r2==0) obj = new restoreFuelAction(new restoreFuelNight);
                if(r2==1) obj = new RestoreArmourAction(new RestoreArmourNight);
                if(r2==2) obj = new RestoreHealthAction(new RestoreHealthDay);
                if(r2==3) obj = new incDamageAction(new incDamageDay);
                if(r2>=4) obj = new NoneObj;

                cell[i][j] = new Cell(j,i,nullptr, l, obj);
            }
        }

        this->adapter->createField(this);
    }

    //копирование поля. сслыка на другое поле,
    Field::Field(const Field &field) : x(field.x), y(field.y), maxUnit(field.maxUnit), curUnit(field.curUnit){
        // копируем карту юнитов
        cell = new Cell**[field.y];
        for (int i=0; i<field.y; i++) {
            cell[i] = new Cell *[field.x];
            for (int j=0; j<field.x; j++) {
                cell[i][j] = field.cell[i][j];
            }
        }
    }

//старое поле будет уничтожено
    Field::Field(Field &&field) : x(field.x), y(field.y), maxUnit(field.maxUnit), curUnit(field.curUnit){
        cell = new Cell**[field.y];
        for (int i=0; i<field.y; i++) {
            cell[i] = new Cell *[field.x];
            for (int j=0; j<field.x; j++) {
                cell[i][j] = field.cell[i][j];
            }
        }

        for (int i = 0; i < field.y; ++i)
            delete[] field.cell[i];
        delete[] field.cell;
    }

    void Field::addUnit(Unit* unit){ //если x < чем текущий x. Координаты юнита и размер поля
        if (unit->x < this->x &&   unit->y < this->y && curUnit < maxUnit) {
            cell[unit->y][unit->x]->unit = unit; //вставляем юнит на карту
            this->curUnit++;
        }
    }

    Base *Field::createBase(int x, int y, int maxCountUnit, int health)
    {
        base = new Base(this, x, y, maxCountUnit, health); //orig
        //Base *base = new Base(this, x, y, maxCountUnit, health); //2
        if (base == nullptr) {
            std::cout << "Field::createBase - Error: can't allocate memory!" << std::endl;
            return nullptr;
        }
        adapter->createBase(base);
        return base;
    }

    void Field::removeUnit(Unit* unit){
        for (int i=0; i<this->y; i++){
            for (int j=0; j<this->y; j++)
                if (cell[i][j]->unit == unit){
                    delete cell[i][j]->unit;
                    cell[i][j]->unit = nullptr;
                    this->curUnit--;
                    return;
                }
        }
    }

    void Field::print(){
        for (int i=0; i<this->y; i++){
            for (int j=0; j<this->x; j++) {
                if(base!=nullptr && i == base->y && j==base->x) {
                    std::cout << "## |";
                    continue;
                }
                if(cell[i][j]->object!= nullptr) {
                    std::cout << cell[i][j]->object->typeNeutral();
                }
                else {
                    std::cout << " ";
                }

                if(cell[i][j]->landscape!= nullptr) {
                    std::cout << cell[i][j]->landscape->typeLandscape();
                }
                else {
                    std::cout << " ";
                }


                if (cell[i][j]->unit != nullptr){
                    cell[i][j]->unit->print();
                }
                else {
                    std::cout << " ";
                }
                std::cout<<"|";
            }

            std::cout << std::endl;
             for (int j=0; j<this->x; j++)
                 std::cout<<"----";
             std::cout<<"\n";
        }
        std::cout<<"\n";
        //std::cout<<"\n*****************\n";
    }

    bool Field::moveUnit(Unit* unit, int x, int y) {
        // если хочет зайти на базу
        if(base->x==x && base->y==y) {
            if(base->countUnit < base->maxCountUnit) {
                cell[unit->y][unit->x]->unit = nullptr;
                base->enterBase(unit);

                adapter->moveUnit(unit);
                return true;
            }
            else {
                std::cout << "Too many units at base!" << std::endl;
                return false;
            }
        }

        if(cell[y][x]->landscape->canMove(unit)) {
            cell[unit->y][unit->x]->unit = nullptr;
            unit->move(x,y);
            cell[y][x]->unit = unit;

            *(cell[y][x]->object)>>unit;

            if(base->isUnitAtBase(unit)) {
                base->exitBase(unit);
            }
            adapter->moveUnit(unit);
            return true;
        }
        else {
            std::cout  << "Can't move unit ";
            adapter->Log("Can't move unit ");

            unit->print();
            std::cout << " to cell (" << x << "," << y << ")" << std::endl;
            return false;
        }
    }

//void Field::addLandscape(){
//    for (int i=0; i<this->y; i++){
//        for (int j=0; j<this->x; j++){
//            int randomLandscape = (i+j)%3;
//            if (randomLandscape == 0)
//                arrUnit[i][j]->landscape = new Mountain();
//            else if (randomLandscape == 1)
//                arrUnit[i][j]->landscape = new Water();
//            else if (randomLandscape == 2)
//                arrUnit[i][j]->landscape = new Ground();
//        }
//    }
//}

//void Field::printLandscape(){
//    for (int i=0; i<this->y; i++){
//        for (int j=0; j<this->x; j++){
//            std::cout << arrUnit[i][j]->landscape->getNameLandscape() << " ";
//        }
//        std::cout << std::endl;
//    }
//}
