#include "iterator.h"

Iterator::Iterator(Field &field): field(field), cur(nullptr), x(-1), y(-1)
{

}

bool Iterator::operator!= (const Iterator& iter) {
    return cur != iter.cur;
}

bool Iterator::goNext()
{
    for(int i =0; i<field.x; i++){
        for(int j=0; j<field.y; j++){
            if(field.cell[i][j]->unit != nullptr){
                cur = field.cell[i][j]->unit; // найденный юнит

                if(i>y){
                    x = j;
                    y = i;
                    isfind = true;
                    return true;
                }
                else if ((i==y && j>x) || !isfind){
                    x = j;
                    y = i;
                    isfind = true;
                    return true;
                }

            }
        }
    }
    return false;
}
