#include "field.h"

Field::Field(int M, int N, int maxNumOfObjects){
    rows = M;
    columns = N;
    this->maxNumOfObjects = maxNumOfObjects;
    field = new Cell**[this->rows];
    for (int i = 0; i < rows; i++){
        field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            field[i][j] = new Cell;
            field[i][j]->base = nullptr;
            field[i][j]->unit = nullptr;
            field[i][j]->nObject = nullptr;
            if (i == 3 && j == 7){
                field[i][j]->nObject = new Stone();
            }
            if (i == 6 && j == 4){
                field[i][j]->nObject = new Gold();
            }
            if (i == 11 && j == 15){
                field[i][j]->nObject = new LifeWell();
            }
            if (i == 15 && j == 5){
                field[i][j]->nObject = new ForceWell();
            }
         //   if ((i != 6 && j != 4) || (i != 3 && j != 7) || (i != 9 && j != 5) || (i != 15 && j != 10)){

         //   }
            if (i > 3 && i < 9){            // потом сделаю рандомизированно
                if (j > columns/2-3 && j < columns/2 + 3){
                    field[i][j]->landScape = new Forest;
                    continue;
                }
            }
            if (i > rows/2+2 && i < rows/2 + 8){
                if (j > columns/2-1 && j < columns/2 + 5){
                    field[i][j]->landScape = new Swamp;
                    continue;
                }
            }
            field[i][j]->landScape = new Plain;
        }
    }
    units = new Unit**[countOfDiffUnits*2];
    for(int i = 0; i< countOfDiffUnits*2; i++){
        units[i] = new Unit*[maxNumOfObjects];
        for(int j = 0; j < maxNumOfObjects; j++){
            units[i][j] = new Unit;
            units[i][j] = nullptr;
        }
    }
}

Field::Field(const Field& field) : rows(field.rows), columns(field.columns), countOfObjects(field.countOfObjects), maxNumOfObjects(field.maxNumOfObjects){     // конструктор копирования
    cout << "Call the construktor of copy\n";
    this->field = new Cell**[rows];
    for (int i = 0; i < field.rows; i++){
        this->field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            this->field[i][j] = new Cell;
            if (field.field[i][j]->landScape){
                if (field.field[i][j]->landScape->sym == '|'){
                    this->field[i][j]->landScape = new Forest;
                }
                if (field.field[i][j]->landScape->sym == '_'){
                    this->field[i][j]->landScape = new Plain;
                }
                if (field.field[i][j]->landScape->sym == ' '){
                    this->field[i][j]->landScape = new Swamp;
                }
            }
            if (field.field[i][j]->base){
                this->field[i][j]->base = new Base;
                this->field[i][j]->base->hp = field.field[i][j]->base->hp;
                this->field[i][j]->base->sym = field.field[i][j]->base->sym;
            }
            if (field.field[i][j]->nObject){
                if (field.field[i][j]->nObject->sym == 's'){
                    this->field[i][j]->nObject = new Stone;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'g'){
                    this->field[i][j]->nObject = new Gold;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'l'){
                    this->field[i][j]->nObject = new LifeWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'f'){
                    this->field[i][j]->nObject = new ForceWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
            }
            if (field.field[i][j]->unit){
                this->field[i][j]->unit = new Unit;
                this->field[i][j]->unit->x = field.field[i][j]->unit->x;
                this->field[i][j]->unit->y = field.field[i][j]->unit->y;
                this->field[i][j]->unit->id.code = field.field[i][j]->unit->id.code;
                this->field[i][j]->unit->id.index = field.field[i][j]->unit->id.index;
                this->field[i][j]->unit->sym = field.field[i][j]->unit->sym;
            }
            this->field[i][j]->landScape->sym = field.field[i][j]->landScape->sym;
        }
    }

    this->units = new Unit**[COUNT_OF_UNITS_TYPE*2];
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        this->units[i] = new Unit*[maxNumOfObjects];
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                this->units[i][j] = new Unit;
                this->units[i][j]->x = field.units[i][j]->x;
                this->units[i][j]->y = field.units[i][j]->y;
                this->units[i][j]->id.code = field.units[i][j]->id.code;
                this->units[i][j]->id.index = field.units[i][j]->id.index;
                this->units[i][j]->sym = field.units[i][j]->sym;
            }
        }
    }

}

Field& Field::operator= (const Field& field){          // оператор присваивания для копирования
    if (&field == this)
        return *this;
    cout << "new operator =\n";
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->field[i][j]->base)
                delete this->field[i][j]->base;
            if (this->field[i][j]->unit)
                delete this->field[i][j]->unit;
            if(this->field[i][j]->nObject)
                delete this->field[i][j]->nObject;
        //    if (this->field[i][j]->landScape)
          //      delete this->field[i][j]->landScape;
        }
        delete [] this->field[i];
    }
    for (int i = 0; i < COUNT_OF_UNITS_TYPE; i++){
        delete [] this->units[i];
    }
    delete[] this->field;
    delete[] this->units;
    this->field = new Cell**[rows];
    for (int i = 0; i < field.rows; i++){
        this->field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            this->field[i][j] = new Cell;
            if (field.field[i][j]->landScape){
                if (field.field[i][j]->landScape->sym == '|'){
                    this->field[i][j]->landScape = new Forest;
                }
                if (field.field[i][j]->landScape->sym == '_'){
                    this->field[i][j]->landScape = new Plain;
                }
                if (field.field[i][j]->landScape->sym == ' '){
                    this->field[i][j]->landScape = new Swamp;
                }
            }
            if (field.field[i][j]->base){
                this->field[i][j]->base = new Base;
                this->field[i][j]->base->hp = field.field[i][j]->base->hp;
                this->field[i][j]->base->sym = field.field[i][j]->base->sym;
            }
            if (field.field[i][j]->nObject){
                if (field.field[i][j]->nObject->sym == 's'){
                    this->field[i][j]->nObject = new Stone;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'g'){
                    this->field[i][j]->nObject = new Gold;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'l'){
                    this->field[i][j]->nObject = new LifeWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'f'){
                    this->field[i][j]->nObject = new ForceWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
            }
            if (field.field[i][j]->unit){
                this->field[i][j]->unit = new Unit;
                this->field[i][j]->unit->x = field.field[i][j]->unit->x;
                this->field[i][j]->unit->y = field.field[i][j]->unit->y;
                this->field[i][j]->unit->id.code = field.field[i][j]->unit->id.code;
                this->field[i][j]->unit->id.index = field.field[i][j]->unit->id.index;
                this->field[i][j]->unit->sym = field.field[i][j]->unit->sym;
            }
            this->field[i][j]->landScape->sym = field.field[i][j]->landScape->sym;
        }
    }
    this->units = new Unit**[COUNT_OF_UNITS_TYPE*2];
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        this->units[i] = new Unit*[maxNumOfObjects];
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                this->units[i][j] = new Unit;
                this->units[i][j]->x = field.units[i][j]->x;
                this->units[i][j]->y = field.units[i][j]->y;
                this->units[i][j]->id.code = field.units[i][j]->id.code;
                this->units[i][j]->id.index = field.units[i][j]->id.index;
                this->units[i][j]->sym = field.units[i][j]->sym;
            }
        }
    }
    return *this;
}

Field::Field(Field&& field) : rows(field.rows), columns(field.columns), countOfObjects(field.countOfObjects), maxNumOfObjects(field.maxNumOfObjects){  // конструктор перемещения
    cout << "Call the construktor of relocation\n";
    field.rows = 0;
    field.columns = 0;
    field.countOfObjects = 0;
    field.maxNumOfObjects = 0;
    this->field = field.field;
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            field.field[i][j]->landScape = nullptr;
            if (field.field[i][j]->base){
                field.field[i][j]->base = nullptr;
            }
            if (field.field[i][j]->nObject){
                field.field[i][j]->nObject = nullptr;
            }
            if (field.field[i][j]->unit){
                field.field[i][j]->unit = nullptr;
            }
        }
        field.field = nullptr;
    }

    this->units = field.units;
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                field.units[i][j] = nullptr;
            }
        }
    }
    field.units = nullptr;
}

Field& Field::operator=(Field&& field){            // оператор присваивания для перемещения
    if (&field == this)
        return *this;
    cout << "new relocation operator =\n";
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->field[i][j]->base)
                delete this->field[i][j]->base;
            if (this->field[i][j]->unit)
                delete this->field[i][j]->unit;
            if(this->field[i][j]->nObject)
                delete this->field[i][j]->nObject;
         //   if (this->field[i][j]->landScape)
           //     delete this->field[i][j]->landScape;
        }
        delete [] this->field[i];
    }
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        delete [] this->units[i];
    }
    delete[] this->field;
    delete[] this->units;
    field.rows = 0;
    field.columns = 0;
    field.countOfObjects = 0;
    field.maxNumOfObjects = 0;
    this->field = field.field;
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            field.field[i][j]->landScape = nullptr;
            if (field.field[i][j]->base){
                field.field[i][j]->base = nullptr;
            }
            if (field.field[i][j]->nObject){
                field.field[i][j]->nObject = nullptr;
            }
            if (field.field[i][j]->unit){
                field.field[i][j]->unit = nullptr;
            }
        }
        field.field = nullptr;
    }
    this->units = field.units;
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                field.units[i][j] = nullptr;
            }
        }
    }
    field.units = nullptr;
    return *this;
}

int Field::checkEmptySpace(int code){
    int in = 0;
    while(units[code][in]){
        in++;
    }
    return in;
}

void Field::setUnit1(Unit* unit){
    if (unit->x < this->rows && unit->y < this->columns && this->countOfObjects < this->maxNumOfObjects){
        int in = checkEmptySpace(unit->id.code);
        units[unit->id.code][in] = unit;
        unit->id.index = in;
        field[unit->y][unit->x]->unit = unit;
    }
}

void Field::deleteUnit1(Unit* unit){
    field[rows/2][0]->base->gold += unit->cost/2;
    field[rows/2][0]->base->countOfUnits--;
    units[unit->id.code][unit->id.index] = nullptr;
    field[unit->y][unit->x]->unit = nullptr;
    delete unit;
}

Unit* Field::changeUnit1 (Unit* unit){                      // need to be fixed
    int code = unit->id.code;
    int index = unit->id.index;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < maxNumOfObjects; j++){
            if (units[i][j] && units[i][j] != unit){
                return units[i][j];
            }
        }
    }
}

void Field::setUnit2(Unit* unit){
    if (unit->x < this->rows && unit->y < this->columns && this->countOfObjects < this->maxNumOfObjects){
        int in = checkEmptySpace(unit->id.code);
        units[unit->id.code][in] = unit;
        unit->id.index = in;
        field[unit->y][unit->x]->unit = unit;
    }
}

void Field::deleteUnit2(Unit* unit){
    field[rows/2][columns-1]->base->gold += unit->cost/2;
    field[rows/2][columns-1]->base->countOfUnits--;
    units[unit->id.code][unit->id.index] = nullptr;
    field[unit->y][unit->x]->unit = nullptr;
    delete unit;
}

Unit* Field::changeUnit2(Unit* unit){                      // need to be fixed
    for (int i = 6; i < 12; i++){
        for (int j = 0; j < maxNumOfObjects; j++){
            if (units[i][j] && units[i][j] != unit){
                return units[i][j];
            }
        }
    }
}

void Field::move(Unit* unit, int x, int y){                        // передвижение юнитов
    if (field[y][x]->unit){
        return;
    }
    else{
        if (field[y][x]->landScape->sym != field[unit->y][unit->x]->landScape->sym){
            if (!field[y][x]->landScape->interaction(unit)){
                return;
            }
        }
        if (field[y][x]->nObject){
            if (field[y][x]->nObject->sym == 'f'){
                if (unit->compFlag){
                    field[y][x]->nObject->strategy(unit);
                }
                return;
            }
            if (field[y][x]->nObject->sym == 'l'){
                if (unit->compFlag){
                    field[y][x]->nObject->strategy(unit);
                }
                return;
            }
            if (field[y][x]->nObject->sym == 's'){
                return;
            }
            if (field[y][x]->nObject->sym == 'g'){
                NitralObject* g = field[y][x]->nObject;
                field[y][x]->nObject = nullptr;
                delete g;
                field[rows/2][0]->base->gold += 200;
            }
        }
        field[unit->y][unit->x]->unit = nullptr;
        units[unit->id.code][unit->id.index]->x = x;
        units[unit->id.code][unit->id.index]->y = y;
        unit->x = x;
        unit->y = y;
        field[y][x]->unit = unit;
    }
}

void Field::createBase(int x, int y){
    field[y][x]->base = new Base;
    field[y][x]->base->x = x;
    field[y][x]->base->y = y;
}

void Field::setUnitFromBase(ArmyFactory& factory, int x, int y, int code){
    Unit* unit;
    if (code > 5){
        unit = field[y][x]->base->createUnit(code-6, factory);
    }
    else{
        unit = field[y][x]->base->createUnit(code, factory);
    }
    if (unit == nullptr){
        return;
    }
    field[unit->y][unit->x]->unit = unit;
    int in = checkEmptySpace(code);
    units[code][in] = unit;
    unit->id.index = in;
}

Unit* Field::getLastUnit(int code){    // чето ломается
    Unit* unit = new Unit;
    int i = 0;
    while (units[code][i+1]){
        i++;
    }
    if (units[code][i]){
        unit = units[code][i];
        return unit;
    }
    else {
        return nullptr;
    }
    /*

    int code1 = code;                   // второй вариант
    Unit* unit = new Unit;
    for (int i = 0; i <= code1; i++){
        for (int j = 0; j < checkEmptySpace(code1); j++){
            if (units[code1][i]){
                unit = units[code1][i];
                return unit;
            }
        }
    }
    return nullptr;
    */
}

int Field::getBaseGold(int x, int y){
    return field[y][x]->base->gold;
}

int Field::getBaseCountOfUnits(int x, int y){
    return field[y][x]->base->countOfUnits;
}

void Field::printField(Unit* unit){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if (field[i][j]->unit){
                cout << field[i][j]->unit->sym;
                continue;
            }
            if (field[i][j]->base){
                cout << field[i][j]->base->sym;
                continue;
            }
            if (field[i][j]->nObject){
                cout << field[i][j]->nObject->sym;
                continue;
            }
            if(field[i][j]->landScape){
                cout << field[i][j]->landScape->sym;
                continue;
            }
        }
        cout << '\n';
    }
 //   cout << '\n';
    // cout << "Gold of your base: " << field[rows/2][0]->base->gold << " | Count of your units: " << field[rows/2][0]->base->countOfUnits;
   // cout << '\n';
    if (unit)
        cout << "\nForce of current unit: " << unit->force << "\t\tHp of current unit: " << unit->hp << endl;

}

Field::~Field(){
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->field[i][j]->base)
                delete this->field[i][j]->base;
            if (this->field[i][j]->unit)
                delete this->field[i][j]->unit;
            if(this->field[i][j]->nObject)
                delete this->field[i][j]->nObject;
          //  if (this->field[i][j]->landScape)
            //    delete this->field[i][j]->landScape;
        }
        delete [] this->field[i];
    }
    for (int i = 0; i < COUNT_OF_UNITS_TYPE; i++){
        delete [] this->units[i];
    }
    delete[] this->field;
    delete[] this->units;
}

/* Паттерн команда */

void MoveUpCommand::execute(Unit* unit){
    gField->move(unit, unit->x, unit->y-1);
}

void MoveDownCommand::execute(Unit* unit){
    gField->move(unit, unit->x, unit->y+1);
}

void MoveLeftCommand::execute(Unit* unit){
    gField->move(unit, unit->x-1, unit->y);
}

void MoveRightCommand::execute(Unit* unit){
    gField->move(unit, unit->x+1, unit->y);
}

