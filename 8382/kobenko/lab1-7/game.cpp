//
// Created by vlad on 01.06.2020.
//

#include "game.h"

bool flag = true;
int counter = 1;

Logg g;
LogF f;
BigHeal bh;
Heal h;

void Game::InfiniteCycle(Field& field){
    char BestEverStr, chooseUnit, EnemyUnit, s;
    int x, y, it, a, LOAD;
    deathCeil deaC;
    AwesomeCeil aweC;
    LightBase lb;
    DarkBase db;
    field.field[lb.x][lb.y] = lb.type;
    field.field[db.x][db.y] = db.type;
    LightArcher la;
    DarkArcher da;
    LightCavalry lc;
    DarkCavalry dc;
    LightInfantry li;
    DarkInfantry di;
    field.field[la.x][la.y] = la.type;
    field.field[da.x][da.y] = da.type;
    field.field[li.x][li.y] = li.type;
    field.field[di.x][di.y] = di.type;
    field.field[lc.x][lc.y] = lc.type;
    field.field[dc.x][dc.y] = dc.type;
    field.PrintField();
    field.newMem();
    while(true){
        field.SaveField(counter);
        cout << "Press 'e' to exit the game\n Press 'b', if u are playing for Light or 'B' for Dark"
                "\nIf u want to check amount of ur units and their location"
                "\nYou can also press any other key to continue the game" << endl;
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
        if (MovingUnits(chooseUnit, x, y, li, lc, la, di, dc, da, field))
            break;
        field.PrintField();
        cout << "Choose unit, that you want to attack, if you can't attack someone, then enter 'z'" << endl;
        cin >> EnemyUnit;
        if (AttackingUnits(chooseUnit, EnemyUnit,  li, lc, la, di, dc, da, db, lb))
            break;
        field.PrintField();
        try {
            if(++counter > 50)
                throw "Game over";
        }
        catch (const char* exception) {
            std::cerr << "Error: " << exception << endl;
            break;
        }
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
                    if (counter % 2 == 1)
                        flag = true;
                    else flag = false;
                }
            }
            catch (const char *exception) {
                std::cerr << exception << endl;
            }
        }
    }
}

int Game::MovingUnits(char chooseUnit, int x, int y,  LightInfantry &li, LightCavalry &lc, LightArcher &la, DarkInfantry &di, DarkCavalry &dc, DarkArcher &da, Field& field) {
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
            if (field.field[x][y] == '!' || field.field[x][y] == 'D'){
                if(chooseUnit == 'a'){ field.field[la.x][la.y] = '.';la.getDamage(25); la.type = '.';}
                if(chooseUnit== 'i'){ field.field[li.x][li.y] = '.';li.getDamage(25); li.type = '.';}
                if(chooseUnit == 'c'){ field.field[lc.x][lc.y] = '.';lc.getDamage(25); lc.type = '.';}
                if(chooseUnit == 'A'){ field.field[da.x][da.y] = '.';da.getDamage(25); da.type = '.';}
                if(chooseUnit == 'I'){ field.field[di.x][di.y] = '.';di.getDamage(25); di.type = '.';}
                if(chooseUnit == 'C'){ field.field[dc.x][dc.y] = '.';dc.getDamage(25); dc.type = '.';}
                g.deathLog(chooseUnit);
                f.deathLog(chooseUnit);
            }
            if (field.field[x][y] == 'h') {
                if (chooseUnit == 'a') { la.health += 1; }
                if (chooseUnit == 'i') { li.health += 1; }
                if (chooseUnit == 'c') { lc.health += 1; }
                if (chooseUnit == 'A') { da.health += 1; }
                if (chooseUnit == 'I') { di.health += 1; }
                if (chooseUnit == 'C') { dc.health += 1; }
                h.type = '.';
            }
            if (field.field[x][y] == 'H') {
                if (chooseUnit == 'a') { la.health += 2; }
                if (chooseUnit == 'i') { li.health += 2; }
                if (chooseUnit == 'c') { lc.health += 2; }
                if (chooseUnit == 'A') { da.health += 2; }
                if (chooseUnit == 'I') { di.health += 2; }
                if (chooseUnit == 'C') { dc.health += 2; }
                bh.type = '.';
            }
            if (field.field[x][y] == '#' || field.field[x][y] == 'S'){
                g.gameoverLog();
                f.gameoverLog();
                cout << "Game over, win " << ++counter << " team" << endl;
                exit(1);
            }
            if (chooseUnit == 'a') {
                field.field[la.x][la.y] = '.';
                la.MoveUnits(x, y);
                field.field[x][y] = la.type;
            }
            if (chooseUnit == 'i') {
                field.field[li.x][li.y] = '.';
                li.MoveUnits(x, y);
                field.field[x][y] = li.type;
            }
            if (chooseUnit == 'c') {
                field.field[lc.x][lc.y] = '.';
                lc.MoveUnits(x, y);
                field.field[x][y] = lc.type;
            }
            if (chooseUnit == 'A') {
                field.field[da.x][da.y] = '.';
                da.MoveUnits(x, y);
                field.field[x][y] = da.type;
            }
            if (chooseUnit == 'I') {
                field.field[di.x][di.y] = '.';
                di.MoveUnits(x, y);
                field.field[x][y] = di.type;
            }
            if (chooseUnit == 'C') {
                field.field[dc.x][dc.y] = '.';
                dc.MoveUnits(x, y);
                field.field[x][y] = dc.type;
            }
            g.movementLog(chooseUnit, x, y);
            f.movementLog(chooseUnit, x, y);
        }
        return 0;
    }
    catch (const char* exception) {
        std::cerr << "Error: " << exception << "\n";
        return 1;
    }
}

int Game::AttackingUnits(char chooseUnit, char EnemyUnit, LightInfantry &li, LightCavalry &lc, LightArcher &la, DarkInfantry &di, DarkCavalry &dc, DarkArcher &da,DarkBase& db, LightBase& lb){
    if (EnemyUnit == 'z')
        return 0;
    try{
        int a, b;
        if (flag) {
            if (EnemyUnit == 'I'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits();
                    di.getDamage(a);
                    if(di.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits();
                    di.getDamage(a);
                    if(di.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits();
                    di.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(di.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;

            }
            if (EnemyUnit == 'A'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits();
                    da.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(da.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits();
                    da.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(da.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits();
                    da.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(da.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'C'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits();
                    dc.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(dc.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits();
                    dc.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(dc.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits();
                    dc.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(dc.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'B'){
                if (chooseUnit == 'a'){
                    a = la.AttackUnits();
                    db.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(db.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << ++counter << " team" << endl;
                        exit(1);
                    }
                }
                if (chooseUnit == 'i'){
                    a = li.AttackUnits();
                    db.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(db.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << ++counter << " team" << endl;
                        exit(1);
                    }
                }
                if (chooseUnit == 'c'){
                    a = lc.AttackUnits();
                    db.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(db.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << ++counter << " team" << endl;
                        exit(1);
                    }
                }
                return 0;
            }
            throw "You aren't attacking your enemies!";
        }
        else{
            if (EnemyUnit == 'i'){
                if (chooseUnit == 'A'){
                    a = da.AttackUnits();
                    li.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(li.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'I'){
                    a = di.AttackUnits();
                    li.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(li.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'C'){
                    a = dc.AttackUnits();
                    li.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(li.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'a'){
                if (chooseUnit == 'A'){
                    a = da.AttackUnits();
                    la.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(la.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'I'){
                    a = di.AttackUnits();
                    la.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(la.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'C'){
                    a = dc.AttackUnits();
                    la.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(la.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'c'){
                if (chooseUnit == 'A'){
                    a = da.AttackUnits();
                    lc.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lc.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'I'){
                    a = di.AttackUnits();
                    lc.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lc.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                if (chooseUnit == 'C'){
                    a = dc.AttackUnits();
                    lc.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lc.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                    }
                }
                return 0;
            }
            if (EnemyUnit == 'b') {
                if (chooseUnit == 'A') {
                    a = da.AttackUnits();
                    lb.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lb.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << ++counter << " team" << endl;
                        exit(1);
                    }
                }
                if (chooseUnit == 'I') {
                    a = di.AttackUnits();
                    lb.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lb.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << ++counter << " team" << endl;
                        exit(1);
                    }
                }
                if (chooseUnit == 'C') {
                    a = dc.AttackUnits();
                    lb.getDamage(a);
                    g.attackLog(chooseUnit, a, EnemyUnit);
                    f.attackLog(chooseUnit, a, EnemyUnit);
                    if(lb.type = '.'){
                        g.deathLog(EnemyUnit);
                        f.deathLog(EnemyUnit);
                        g.gameoverLog();
                        f.gameoverLog();
                        cout << "Game over, win " << ++counter << " team" << endl;
                        exit(1);
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