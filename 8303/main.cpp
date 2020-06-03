#include <iostream>

// Абстрактный класс Юнита
class Unit {
    friend class Field;
public:
    class Params {
    public:
        int health;
        int armor;
        int distance;
        int damage;
    } param;

protected:
    int x, y;
public:
    void move(int x, int y){
        this->x = x;
        this->y = y;
    }
    int getx() { return x; }
    int gety() { return y; }
    virtual void print() = 0;
};

class Field {
    int x, y;
    int maxUnit;
    int curUnit;
    Unit ***arrUnit; 


public:
    Field(int x, int y, int maxUnit){
        this->x = x;
        this->y = y;
        this->curUnit = 0;
        this->maxUnit = maxUnit;

        arrUnit = new Unit**[y];
        for (int i=0; i<y; i++) {
            arrUnit[i] = new Unit* [x];
            for (int j=0; j<x; j++)
                arrUnit[i][j] = nullptr;
        }
    }

 
    Field(const Field &field) : x(field.x), y(field.y), maxUnit(field.maxUnit), curUnit(field.curUnit), arrUnit(new Unit**[field.y]){
        for (int i=0; i<field.y; i++) {
            arrUnit[i] = new Unit *[field.x];
            for (int j=0; j<field.x; j++) {
                arrUnit[i][j] = field.arrUnit[i][j];
            }
        }
    }


    Field(Field &&field) : x(field.x), y(field.y), maxUnit(field.maxUnit), curUnit(field.curUnit), arrUnit(new Unit**[field.y]){
        for (int i=0; i<field.y; i++) {
            arrUnit[i] = new Unit *[field.x];
            for (int j=0; j<field.x; j++)
                arrUnit[i][j] = field.arrUnit[i][j];
        }
    }

    void addUnit(Unit* unit){ 
        if (unit->x < this->x &&   unit->y < this->y && curUnit < maxUnit) {
            arrUnit[unit->y][unit->x] = unit; 
        }
    }

    void removeUnit(Unit* unit){
        for (int i=0; i<this->y; i++){
            for (int j=0; j<this->y; j++)
                if (arrUnit[i][j] == unit){
                    delete arrUnit[i][j];
                    arrUnit[i][j] = nullptr;
                    this->curUnit--;
                    return;
                }
        }
    }

    void printAllUnit(){
        for (int i=0; i<this->y; i++){
            for (int j=0; j<this->y; j++)
                if (arrUnit[i][j] != nullptr){
                    arrUnit[i][j]->print();
                    std::cout << " ";
                }
                else{
                    std::cout << ". ";
                }
            std::cout << std::endl;
        }
        std::cout<<"\n*****************\n";
    }

    void moveUnit(Unit* unit, int x, int y) {
        arrUnit[unit->y][unit->x] = nullptr;
        unit->move(x,y);
        arrUnit[unit->y][unit->x] = unit;
    }
};

//--------------------------------
class Footman : public Unit {

};

class Rifleman : public Footman {
public:
    void print() {
        std::cout<<"R";
    }
    Rifleman(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=120;
        this->param.armor=95;
        this->param.distance=3;
        this->param.damage = 33;
    }
};

class Medic: public Footman {
public:
    void print() {
        std::cout<<"M";
    }
    Medic(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=120;
        this->param.armor=64;
        this->param.distance=4;
        this->param.damage = 25;
    }
};

//2
class RangedFighter : public Unit {

};

class Sniper : public RangedFighter {
public:
    void print() {
        std::cout<<"S";
    }
    Sniper(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=90;
        this->param.armor=55;
        this->param.distance=3;
        this->param.damage = 30;
    }
};

class RocketLauncher : public RangedFighter {
public:
    void print() {
        std::cout<<"L";
    }
    RocketLauncher(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=150;
        this->param.armor=100;
        this->param.distance=1;
        this->param.damage = 30;
    }
};

//3
class Transport : public Unit {

};

class ArmoredCar : public Transport {
public:
    void print() {
        std::cout<<"C";
    }
    ArmoredCar(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=170;
        this->param.armor=150;
        this->param.distance=15;
        this->param.damage = 60;
    }
};

class Tank : public Transport {
public:
    void print() {
        std::cout<<"T";
    }
    Tank(int x, int y){
        this->x=x;
        this->y = y;
        this->param.health=220;
        this->param.armor=170;
        this->param.distance=10;
        this->param.damage = 170;
    }
};

class Creater {  // абстрактный метод
    virtual Unit* create(int x, int y) = 0;
};

class TankCreater : public Creater {
public:
    Unit* create(int x, int y) {
        return new Tank(x,y);
    }
};

class ArmoredCarCreater : public Creater {
public:
    Unit* create(int x, int y) {
        return new ArmoredCar(x,y);
    }
};

class RiflemanCreater : public Creater {
public:
    Unit* create(int x, int y) {
        return new Rifleman(x,y);
    }
};

class MedicCreater : public Creater {
public:
    Unit* create(int x, int y) {
        return new Medic(x,y);
    }
};

class SniperCreater : public Creater {
public:
    Unit* create(int x, int y) {
        return new Sniper(x,y);
    }
};

class RocketLauncherCreater : public Creater {
public:
    Unit* create(int x, int y) {
        return new RocketLauncher(x,y);
    }
};


int main() {

    Field* field= new Field(7, 7, 10);

    Unit *tank = new Tank(2, 2);
    Unit *armoredCar = new ArmoredCar(3, 3);
    Unit *rifleman = new Rifleman(3, 5);

//    TankCreater tc;
//    Unit* tank = tc.create(2,2);
//
//    ArmoredCarCreater acc;
//    Unit* armoredCar = acc.create(3,3);

    field->addUnit(tank);
    field->addUnit(armoredCar);
    field->addUnit(rifleman);
    field->printAllUnit();

    field->moveUnit(tank, tank->getx()+1, tank->gety());
    field->moveUnit(armoredCar, armoredCar->getx(), armoredCar->gety()+1);
    field->moveUnit(rifleman, rifleman->getx()-1, rifleman->gety());
    field->printAllUnit();


     Field* Field2 = new Field(*field);
     Field2->printAllUnit();
     std::cout << "---------------------------"<< std::endl;

    return 0;
}
