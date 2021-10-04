#include "Iterator.h"
#include "Unit.h"

    Iterator::Iterator(Field& field) : field(field), cur(field.mapCell[0][0]->unit), x(0), y(0){

    }

    /*Unit*& Iterator::operator++ () {
        if (x >= this->field.lenghtX){
            x = 0;
            y++;
        }
        cur = field.mapCell[y][x++]->unit;
        return cur;
    }*/

    bool Iterator::operator!= (const Iterator& iter) {
        return cur != iter.cur;
    }

    bool Iterator::hasNext(){
        for (int i=0; i<field.lengthY; i++){
            for (int j=0; j<field.lenghtX; j++){
                if (field.mapCell[i][j]->unit != nullptr){
                    if (i > y) {
                        x = j;
                        y = i;
                        isFind = true;
                        return true;
                    }
                    else if ((i==y && j>x) || !isFind){
                        x = j;
                        y = i;
                        isFind = true;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    Unit*& Iterator::operator* () {
        return field.mapCell[y][x]->unit;
    }
