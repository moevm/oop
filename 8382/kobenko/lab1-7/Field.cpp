//
// Created by vlad on 01.06.2020.
//

#include "Field.h"


Field::Field(){}

Field::Field(const Field &other)
    :field(other.field)
{}

Field::Field(Field&& other)
        :field(other.field)
{}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++)
                field[i][j] = other.field[i][j];
            field[i] = other.field[i];
        }
    }
    return *this;
}

Field& Field::operator=(Field &&other){
    if (this != &other) {
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++)
                field[i][j] = other.field[i][j];
            field[i] = other.field[i];
            delete other.field[i];
        }
        delete other.field;
    }
    return *this;
}

void Field::CreatingField(defaultCeil defC, deathCeil deaC, AwesomeCeil aweC, AwesomeItem aweI, DeathItem deaI, Heal h, BigHeal bh){
    for (int i = 0; i < 10; i++){
        this->field[i] = new char [10];
        for (int j = 0; j < 10; j++)
            this->field[i][j] = defC.type;
    }
    this->field[2][2] = deaC.type;
    this->field[7][7] = deaC.type;
    this->field[2][7] = deaC.type;
    this->field[7][2] = deaC.type;

    this->field[8][1] = aweC.type;
    this->field[1][8] = aweC.type;

    this->field[0][9] = aweI.type;
    this->field[9][0] = aweI.type;

    this->field[2][8] = deaI.type;
    this->field[8][2] = deaI.type;
    this->field[0][8] = deaI.type;
    this->field[9][1] = deaI.type;

    this->field[4][4] = h.type;
    this->field[5][5] = h.type;
    this->field[4][5] = bh.type;
    this->field[5][4] = bh.type;
}

void Field::PrintField() {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
            cout << this->field[i][j];
        cout << endl;
    }
}

void Field::CreateAnything(char a, int x, int y){
    this->field[x][y] = a;
}

void Field::del() {
    for (int i = 0; i < 10; i++)
        delete this->field[i];
    delete[] this->field;
}

int Field::CheckField(char choose){
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (this->field[i][j] == choose)
                return 0;
    return 1;
}

void Field::SaveField(int counter) {
    for (int i = 0; i < 10; i++) {
        //this->saveF[counter][i] = this->field[i];
        for (int j = 0; j < 10; j++) {
            this->saveF[counter][i][j] = this->field[i][j];
        }
    }
}

void Field::LoadField(int turn) {
    for (int i = 0; i < 10; i++) {
        this->field[i] = this->saveF[turn][i];
        for (int j = 0; j < 10; j++) {
            this->field[i][j] = this->saveF[turn][i][j];
        }
    }
}

void Field::newMem() {
    for (int i = 0; i < 50; i++) {
        this->saveF[i] = new char* [10];
        for (int j = 0; j < 10; j++){
            this->saveF[i][j] = new char [10];
        }
    }
}

void Field::PrintCpyField(int count) {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
            cout << this->saveF[count][i][j];
        cout << endl;
    }
}

/*pair<int,int> Field::searchEnemy(int flag, char Enemy, Army* army){
    if (flag){
        if (Enemy == 'I')
            return pair<int,int>(army->vi[0]->x, army->vi[0]->y);
        if (Enemy == 'A')
            return pair<int,int>(army->va[0]->x, army->va[0]->y);
        if (Enemy == 'C')
            return pair<int,int>(army->vc[0]->x, army->vc[0]->y);
    } else{
        if (Enemy == 'i')
            return pair<int,int>(army->vi[0]->x, army->vi[0]->y);
        if (Enemy == 'a')
            return pair<int,int>(army->va[0]->x, army->va[0]->y);
        if (Enemy == 'c')
            return pair<int,int>(army->vc[0]->x, army->vc[0]->y);
    }
}*/

