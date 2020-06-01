#include "gfield.h"

using namespace std;

GField::GField(int x, int y) {
    x = max(x,y);
    this->length = x;
    this->width = x;
    this->numberUnit = 0;

    //map = new Unit** [this->length];
    map1.resize(this->width);
    for (int i = 0; i < this->width; i++)
    {
        //map[i] = new Unit* [x];
        map1[i].resize(this->length);
        for (int j = 0; j < this->length; j++){
            //map[i][j] = nullptr;
            map1[i][j] = nullptr;
        }
    }


}

GField::GField(const GField &gfield) {}



void GField::addUnit(Unit* unite, int x, int y) {
        if (x < this->length && y < this->width && this->numberUnit < this->maxnumberUnit) {
            //map[unite->x][unite->y] = unite;
            map1[x][y] = unite;
            this->numberUnit++;
        }
        else
            if(this->numberUnit >= this->maxnumberUnit)
                std::cout << "На поле максимальное количество юнитов" << std::endl;
    }

void GField::moveUnite(Unit* unite, int newx, int newy) {
        if (map1[newx][newy] == nullptr) {
            map1[unite->x][unite->y] = nullptr;
            unite->move(newx, newy);
            unite->x = newx;
            unite->y = newy;
            map1[unite->x][unite->y] = unite;
        }
        else {
            std::cout << "Клетка игрового поля занята" << std::endl;
        }
    }

void GField::deleteUnite(Unit* unite) {
        int x = unite->x;
        int y = unite->y;
        delete map1[unite->x][unite->y];
        map1[x][y] = nullptr;

        this->numberUnit--;
    }

void GField::printField() {
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < this->width; j++)
            if (map1[i][j] != nullptr) {
                cout << map1[i][j]->name << " ";
            }
            else {
                cout << "X ";
            }
        cout << endl;
    }
}

std::vector<std::vector<Unit*>> GField::getMap(){
    return map1;
}
void GField::setMap(std::vector<std::vector<Unit *>> map){
    map1 = map;
}
int GField::getMaxUnit(){
    return maxnumberUnit;
}
int GField::getNumUnit(){
    return numberUnit;
}
void GField::setNumUnit(int num){
    numberUnit = num;
}


