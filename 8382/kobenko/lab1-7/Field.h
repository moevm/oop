//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_FIELD_H
#define UNTITLED_FIELD_H
#include <iostream>
#include "LightArmy.h"
#include "DarkArmy.h"
#include "Landshaft.h"
#include "defaultCeil.h"
#include "deathCeil.h"
#include "AwesomeCeil.h"
#include "AwesomeItem.h"
#include "DeathItem.h"
#include "Heal.h"
#include "BigHeal.h"
#include "LogF.h"
#include "Logg.h"
#include <vector>


using namespace std;

class Field {
public:
    Field();
    Field(const Field &other);
    Field(Field &&other);
    Field& operator=(const Field& other);
    Field& operator=(Field &&other);
    void PrintField();
    void CreatingField(defaultCeil defC, deathCeil deaC, AwesomeCeil aweC, AwesomeItem aweI, DeathItem deaI, Heal h, BigHeal bh);
    void CreateAnything(char, int, int);
    int CheckField(char);
    //pair<int,int> searchEnemy(int flag, char Enemy, Army* army);
    void SaveField(int );
    void LoadField(int );
    void newMem();
    void del();
    char** field = new char* [10];
    char*** saveF = new char** [50];
};


#endif //UNTITLED_FIELD_H
