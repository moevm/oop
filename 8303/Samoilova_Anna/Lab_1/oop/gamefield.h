#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <iostream>
#include "unit.h"


class Cell  // класс одной клеточки в поле
{
private:
    Unit* hero = nullptr;
    // тип клетки
public:
    Cell(){

    }

    void create_unit(int type);
    void copy_unit(Unit* original);
    char get_let();
    bool no_hero();
    Unit* hero_ad();
    void get_hero(Unit* h);
    void del_unit();
};




class GameField  // класс игрового поля
{
private:
    Cell*** field;
    int n, m, unit_max = 0;
    int unit_count = 0;
//    int unit_count_red = 0;
//    int unit_count_blue = 0;

public:
    GameField(int x, int y): n(x), m(y){
        unit_max = x*y / 4;
        if((x>0 || y>0) && unit_max==0)
            unit_max++;
        field = new Cell**[x];
        for(int i=0; i<x; i++){
            field[i] = new Cell*[y];
            for(int j=0; j<y; j++){
                field[i][j] = new Cell;
            }
        }
    }
    ~GameField(){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                field[i][j]->del_unit();
                delete field[i][j];
            }
            delete field[i];
        }
        delete field;
    }
//    int get_unit_count_red();
//    bool set_unit_count_red(int count);
//    int get_unit_count_blue();
//    bool set_unit_count_blue(int count);
    int get_unit_max();
    int get_unit_count();
    bool set_unit_count(int count);
    void fill_field();
    void print_field();
    void move_hero(int x1, int y1, int x2, int y2);
    void add_hero(int x, int y, int hero_code);
    void add_copy_hero(int x, int y, Unit* original);
    void delete_hero(int x, int y);

    void copy_field();
};

#endif // GAMEFIELD_H
