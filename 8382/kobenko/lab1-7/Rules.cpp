//
// Created by vlad on 02.06.2020.
//

#include "Rules.h"

template<typename T>
bool Rules<T>::maxUnits(Field& field){
    int counter = 0;
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if (field.field[i][j] == base.type)
                counter++;
        }
    }
    return counter == 0;
}

template<typename T>
bool Rules<T>::isBaseStillAlive(){
    return (base.health > 0);
}

template<typename T>
bool Rules<T>::TooMuchTurns(int turn){
    return turn == 50;
}


