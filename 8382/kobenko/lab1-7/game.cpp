//
// Created by vlad on 01.06.2020.
//

#include "game.h"

bool flag = true;
int counter = 1;
char BestEverStr, chooseUnit, EnemyUnit, s;
int x, y, it, LOAD;
Logg g;
LogF f;
BigHeal bh;
Heal h;
Rules<DarkBase> RD;
Rules<LightBase> RL;
Rules<LightArcher> Rla;
Rules<DarkArcher> Rda;
Rules<LightCavalry> Rlc;
Rules<DarkCavalry> Rdc;
Rules<LightInfantry> Rli;
Rules<DarkInfantry> Rdi;
LightArcher la;
DarkArcher da;
LightCavalry lc;
DarkCavalry dc;
LightInfantry li;
DarkInfantry di;
deathCeil deaC;
AwesomeCeil aweC;
LightBase lb;
DarkBase db;

void Game::init(Field& field){
    field.field[lb.x][lb.y] = lb.type;
    field.field[db.x][db.y] = db.type;
    field.field[la.x][la.y] = la.type;
    field.field[da.x][da.y] = da.type;
    field.field[li.x][li.y] = li.type;
    field.field[di.x][di.y] = di.type;
    field.field[lc.x][lc.y] = lc.type;
    field.field[dc.x][dc.y] = dc.type;
    field.PrintField();
}

void Game::InfiniteCycle(Field& field){
    init(field);
    field.newMem();
    while(true){
        field.SaveField(counter);
        /*if (counter > 2){
            field.PrintCpyField(counter - 1);
            field.PrintCpyField(counter - 2);
            exit(1);
        }*/
        cout << "Press 'e' to exit the game\n Press 'b', if u are playing for Light or 'B' for Dark"
                "\nIf u want to check amount of ur units and their location"
                "\nYou can also press any other key to continue the game"
                "\n {a/A, i/I} units can go through 1 ceil, {c/C} units can go through 2 ceils."
                "\n{a/A} units have attack range 2 ceils, {i/I, c/C} units have attack range 1 cels.\n" << endl;
        cin >> BestEverStr;
        if (BestEverStr == 'e')
            break;
        if (BestEverStr == 'b') {
            it = lb.ControlUnits(field);
            cout << "You have " << it << "units" <<  endl;
        }
        if (BestEverStr == 'B'){
            it = db.ControlUnits(field);
            cout << "You have " << it << "units" <<  endl;
        }
        field.PrintField();
        cout << "Enter your unit" << endl;
        cin >> chooseUnit;
        try{
            if(field.CheckField(chooseUnit))
                throw "you are trying to use not-exist unit";
        }
        catch (const char* exception) {
            std::cerr << "Error: " << exception << endl;
            break;
        }
        cout << "Enter your destination: " << endl;
        cin >> x >> y;
        if (MovingUnits(field))
            break;
        field.PrintField();
        cout << "Choose unit, that you want to attack, if you can't attack someone, then enter 'z'" << endl;
        cin >> EnemyUnit;
        if(AttackingUnits(field))
            break;
        if(checkRules(field))
            break;
        field.PrintField();
        try {
            if(counter + 1 > 50)
                throw "Game over";
        }
        catch (const char* exception) {
            std::cerr << "Error: " << exception << endl;
            break;
        }
        counter++;
        flag = !flag;
        cout << "The next " << counter << " is starting" << endl;
        cout << "If you want to load the game, enter s " << endl;
        cin >> s;
        if (s  == 's') {
            cout << "enter turn " << endl;
            cin >> LOAD;
            try {
                if (LOAD >= counter || LOAD < 1)
                    throw "You entered wrong turn";
                else {
                    field.LoadField(LOAD);
                    counter = LOAD;
                    flag = counter % 2 == 1;
                }
            }
            catch (const char *exception) {
                std::cerr << exception << endl;
            }
        }
    }
    field.del();
}

int Game::checkRules(Field &field) {
    if (Rla.maxUnits(field) && Rli.maxUnits(field) && Rlc.maxUnits(field))
        return 1;
    if (Rda.maxUnits(field) && Rdi.maxUnits(field) && Rdc.maxUnits(field))
        return 1;
}

int Game::MovingUnits(Field& field) {
    try{
        if (flag) {
            if (chooseUnit != 'i' && chooseUnit != 'a' && chooseUnit != 'c')
                throw "You don't go with your units";
        }
        else {
            if (chooseUnit != 'I' && chooseUnit != 'A' && chooseUnit != 'C')
                throw "You don't go with your units";
        }
    }
    catch (const char* exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
    try {
        if (x >= 10 || x < 0 || y >= 10 || y < 0)
            throw "You went out of the field";
        else{
            try {
                if (field.field[x][y] == 'a' || field.field[x][y] == 'c' || field.field[x][y] == 'i' ||
                    field.field[x][y] == 'A' || field.field[x][y] == 'C' || field.field[x][y] == 'I' ||
                    field.field[x][y] == 'b' || field.field[x][y] == 'B')
                    throw "You are trying to go through unit";
                else {
                    if (field.field[x][y] == '!' || field.field[x][y] == 'D') {
                        if (chooseUnit == 'a') {
                            field.field[la.x][la.y] = '.';
                            if(la.MoveUnits(x, y))
                                exit(1);
                            la.getDamage(25);
                            la.type = '.';
                        }
                        if (chooseUnit == 'i') {
                            field.field[li.x][li.y] = '.';
                            if(li.MoveUnits(x, y))
                                exit(1);
                            li.getDamage(25);
                            li.type = '.';
                        }
                        if (chooseUnit == 'c') {
                            field.field[lc.x][lc.y] = '.';
                            if(lc.MoveUnits(x, y))
                                exit(1);
                            lc.getDamage(25);
                            lc.type = '.';
                        }
                        if (chooseUnit == 'A') {
                            field.field[da.x][da.y] = '.';
                            if(da.MoveUnits(x, y))
                                exit(1);
                            da.getDamage(25);
                            da.type = '.';
                        }
                        if (chooseUnit == 'I') {
                            field.field[di.x][di.y] = '.';
                            if(di.MoveUnits(x, y))
                                exit(1);
                            di.getDamage(25);
                            di.type = '.';
                        }
                        if (chooseUnit == 'C') {
                            field.field[dc.x][dc.y] = '.';
                            if(dc.MoveUnits(x, y))
                                exit(1);
                            dc.getDamage(25);
                            dc.type = '.';
                        }
                        g.deathLog(chooseUnit);
                        f.deathLog(chooseUnit);
                    }
                    if (field.field[x][y] == 'h') {
                        if (chooseUnit == 'a') { la.health += 1; field.field[la.x][la.y] = '.'; if(la.MoveUnits(x, y)) exit(1); field.field[x][y] = la.type;}
                        if (chooseUnit == 'i') { li.health += 1; field.field[li.x][li.y] = '.'; if(li.MoveUnits(x, y)) exit(1); field.field[x][y] = li.type;}
                        if (chooseUnit == 'c') { lc.health += 1; field.field[lc.x][lc.y] = '.'; if(lc.MoveUnits(x, y)) exit(1); field.field[x][y] = lc.type;}
                        if (chooseUnit == 'A') { da.health += 1; field.field[da.x][da.y] = '.'; if(da.MoveUnits(x, y)) exit(1); field.field[x][y] = da.type;}
                        if (chooseUnit == 'I') { di.health += 1; field.field[di.x][di.y] = '.'; if(di.MoveUnits(x, y)) exit(1); field.field[x][y] = di.type;}
                        if (chooseUnit == 'C') { dc.health += 1; field.field[dc.x][dc.y] = '.'; if(dc.MoveUnits(x, y)) exit(1); field.field[x][y] = dc.type;}
                        h.type = '.';
                    }
                    if (field.field[x][y] == 'H') {
                        if (chooseUnit == 'a') { la.health += 2; field.field[la.x][la.y] = '.'; if(la.MoveUnits(x, y)) exit(1); field.field[x][y] = la.type;}
                        if (chooseUnit == 'i') { li.health += 2; field.field[li.x][li.y] = '.'; if(li.MoveUnits(x, y)) exit(1); field.field[x][y] = li.type;}
                        if (chooseUnit == 'c') { lc.health += 2; field.field[lc.x][lc.y] = '.'; if(lc.MoveUnits(x, y)) exit(1); field.field[x][y] = lc.type;}
                        if (chooseUnit == 'A') { da.health += 2; field.field[da.x][da.y] = '.'; if(da.MoveUnits(x, y)) exit(1); field.field[x][y] = da.type;}
                        if (chooseUnit == 'I') { di.health += 2; field.field[di.x][di.y] = '.'; if(di.MoveUnits(x, y)) exit(1); field.field[x][y] = di.type;}
                        if (chooseUnit == 'C') { dc.health += 2; field.field[dc.x][dc.y] = '.'; if(dc.MoveUnits(x, y)) exit(1); field.field[x][y] = dc.type;}
                        bh.type = '.';
                    }
                    if (field.field[x][y] == '#' || field.field[x][y] == 'S') {
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << (++counter % 2)<< " team" << endl;
                        exit(1);
                    }
                    if (chooseUnit == 'a') {
                        field.field[la.x][la.y] = '.';
                        if(la.MoveUnits(x, y))
                            exit(1);
                        field.field[x][y] = la.type;
                    }
                    if (chooseUnit == 'i') {
                        field.field[li.x][li.y] = '.';
                        if(li.MoveUnits(x, y))
                            exit(1);
                        field.field[x][y] = li.type;
                    }
                    if (chooseUnit == 'c') {
                        field.field[lc.x][lc.y] = '.';
                        if(lc.MoveUnits(x, y))
                            exit(1);
                        field.field[x][y] = lc.type;
                    }
                    if (chooseUnit == 'A') {
                        field.field[da.x][da.y] = '.';
                        if(da.MoveUnits(x, y))
                            exit(1);
                        field.field[x][y] = da.type;
                    }
                    if (chooseUnit == 'I') {
                        field.field[di.x][di.y] = '.';
                        if(di.MoveUnits(x, y))
                            exit(1);
                        field.field[x][y] = di.type;
                    }
                    if (chooseUnit == 'C') {
                        field.field[dc.x][dc.y] = '.';
                        if(dc.MoveUnits(x, y))
                            exit(1);
                        field.field[x][y] = dc.type;
                    }
                    g.movementLog(chooseUnit, x, y);
                    f.movementLog(chooseUnit, x, y);
                }
            }
            catch (const char* exception) {
                std::cerr << "Error: " << exception << "\n";
                return 1;
            }
        }
        return 0;
    }
    catch (const char* exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
}

int Game::AttackingUnits(Field &field){
    if (EnemyUnit == 'z')
        return 0;
    try{
        int a, b;
        if (flag) {
            if (EnemyUnit == 'I'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            di.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                        }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    if(di.type == '.'){
                        field.field[di.x][di.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            di.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    if(di.type == '.'){
                        field.field[di.x][di.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            di.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(di.type == '.'){
                        field.field[di.x][di.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;

            }
            if (EnemyUnit == 'A'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            da.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(da.type == '.'){
                        field.field[da.x][da.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            da.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(da.type == '.'){
                        field.field[da.x][da.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            da.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(da.type == '.'){
                        field.field[da.x][da.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'C'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            dc.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(dc.type == '.'){
                        field.field[dc.x][dc.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            dc.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(dc.type == '.'){
                        field.field[dc.x][dc.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            dc.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(dc.type == '.'){
                        field.field[dc.x][dc.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'B'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            db.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if((&RD)->isBaseStillAlive()) {
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << (counter % 2 )<< " team" << endl;
                        return 1;
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            db.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if((&RD)->isBaseStillAlive()) {
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << (counter % 2 )<< " team" << endl;
                        return 1;
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            db.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if((&RD)->isBaseStillAlive()) {
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << (counter % 2 )<< " team" << endl;
                        return 1;
                    }
                }
                return 0;
            }
            throw "You aren't attacking your enemies!";
        }
        else{
            if (EnemyUnit == 'i'){
                if (chooseUnit == 'A'){
                    a = da.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            li.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(li.type == '.'){
                        field.field[li.x][li.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'I'){
                    a = di.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            li.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(li.type == '.'){
                        field.field[li.x][li.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'C'){
                    a = dc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            li.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(li.type == '.'){
                        field.field[li.x][li.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'a'){
                if (chooseUnit == 'A'){
                    a = da.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            la.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(la.type == '.'){
                        field.field[la.x][la.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'I'){
                    a = di.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            la.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(la.type == '.'){
                        field.field[la.x][la.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'C'){
                    a = dc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            la.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(la.type == '.'){
                        field.field[la.x][la.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'c'){
                if (chooseUnit == 'A'){
                    a = da.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            lc.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lc.type == '.'){
                        field.field[lc.x][lc.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'I'){
                    a = di.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            lc.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lc.type == '.'){
                        field.field[lc.x][lc.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'C'){
                    a = dc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            lc.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lc.type == '.'){
                        field.field[lc.x][lc.y] = '.';
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'b') {
                if (chooseUnit == 'A') {
                    a = da.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            lb.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if((&RL)->isBaseStillAlive()){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << (counter % 2 )<< " team" << endl;
                        return 1;
                    }
                }
                if (chooseUnit == 'I') {
                    a = di.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            lb.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if((&RL)->isBaseStillAlive()){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << (counter % 2 )<< " team" << endl;
                        return 1;
                    }
                }
                if (chooseUnit == 'C') {
                    a = dc.AttackUnits(field.field, EnemyUnit);
                    try {
                        if (a != -1)
                            lb.getDamage(a);
                        else throw "You are trying to attack unit, that is out of range";
                    }
                    catch (const char *exception) {
                        std::cerr << "Error: " << exception << "\n";
                        return 1;
                    }
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if((&RL)->isBaseStillAlive()){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << (counter % 2 )<< " team" << endl;
                        return 1;
                    }
                }
                return 0;
            }
            throw "You aren't attacking your enemies!";
        }
    }
    catch (const char *exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
}