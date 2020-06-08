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
        if (x < this->length && y < this->width ){
            map1[x][y] = unite;
            unite->x = x;
            unite->y = y;
        }
    }

void GField::moveUnite(Unit* unite, int newx, int newy) {
        if (map1[newx][newy]->type == "landscape") {
            int a = unite->x, b = unite->y;
            land = new Land;
            addUnit(land, a, b);
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
        map1[x][y] = new Land();
        this->numberUnit--;
    }

void GField::printField() {
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < this->width; j++){
            if (map1[i][j]->type != "landscape" && map1[i][j]->type !="neutral") {
                cout << map1[i][j]->name << " ";
            }
            else {
                cout << "X ";
            }
        }
        cout << endl;
    }
}

void GField::addLabdscape(){
    for (int i = 0; i < this->length; i++)
        for (int j = 0; j < this->length; j++){
            land = new Land;
            addUnit(land, i,j);
        }
    for(int i = 0; i < this->length / 2; i++){
        srand(time(NULL));
        int randomLandscape_x =  rand()% 10;
        srand(time(NULL));
        int randomLandscape_y =  rand()% 10;
        map1[randomLandscape_x][randomLandscape_y] = new Swamp;
    }
    for(int i = 0; i < this->length / 3; i++){
        srand(time(NULL));
        int randomLandscape_x =  rand()% this->length;
        srand(time(NULL));
        int randomLandscape_y =  rand()% this->length;
        map1[randomLandscape_x][randomLandscape_y] = new Forest;
    }
}

void GField::addNeutralObject(std::string name_object){
    int k = 0;
    while(k<1){
        srand(time(NULL));
        int randomLandscape_x =  rand()% this->length;
        srand(time(NULL));
        int randomLandscape_y =  rand()% this->length;
        if(map1[randomLandscape_x][randomLandscape_y]->type == "landscape"){
            if(name_object == "positive card")
                map1[randomLandscape_x][randomLandscape_y] = new PositiveCard;
            if(name_object == "negative card")
                map1[randomLandscape_x][randomLandscape_y] = new NegativeCard;
            if(name_object == "c card")
                map1[randomLandscape_x][randomLandscape_y] = new TransformationCard;
            k++;
        }
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
int GField::getLength(){
    return length;
}
void GField::setNumUnit(int num){
    numberUnit = num;
}
Land* GField::getLand(){
    return land;
}

