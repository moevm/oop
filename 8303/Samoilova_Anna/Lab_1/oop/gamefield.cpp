#include "gamefield.h"

using std::cout;
using std::endl;

int GameField::get_unit_count(){
    return unit_count;
}

//int GameField::get_unit_count_red(){
//    return unit_count_red;
//}

//int GameField::get_unit_count_blue(){
//    return unit_count_blue;
//}

int GameField::get_unit_max(){
    return unit_max;
}

bool GameField::set_unit_count(int count){
    if(count > unit_max){
        return false;
    }
    unit_count = count;
    return true;
}

//bool GameField::set_unit_count_red(int count){
//    if(count > unit_max){
//        return false;
//    }
//    unit_count_red = count;
//    return true;
//}

//bool GameField::set_unit_count_blue(int count){
//    if(count > unit_max){
//        return false;
//    }
//    unit_count_blue = count;
//    return true;
//}

void Cell::create_unit(int type){
    if(hero != nullptr)
        return;
    switch (type) {
    case 1:
        hero = new Unit_1;
        break;
    case 2:
        hero = new Unit_2;
        break;
    case 3:
        hero = new Unit_3;
        break;
    default:
        break;
    }

}

void GameField::fill_field(){
//    if(n*m > 3){
        field[0][0]->create_unit(1);
        unit_count++;
//    }
}

char Cell::get_let(){
    return hero->let;
}

bool Cell::no_hero(){
    if(hero == nullptr)
        return true;
    else
        return false;
}

void GameField::print_field(){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(field[i][j]->no_hero()){
                cout << ". ";
            }
            else{
                cout << field[i][j]->get_let() << " ";
            }
        }
        cout << endl;
    }
}

void Cell::get_hero(Unit *h){
    hero = h;
}

Unit* Cell::hero_ad(){
    return hero;
}

void GameField::move_hero(int x_from, int y_from, int x_to, int y_to){
    if(field[x_from][y_from]->no_hero())
        return;
    if(field[x_to][y_to]->no_hero()){
        field[x_to][y_to]->get_hero(field[x_from][y_from]->hero_ad());
        field[x_from][y_from]->get_hero(nullptr);
    }
}

void GameField::add_hero(int x, int y, int hero_code){
    if(unit_count + 1 > unit_max){
        cout << "Too many units, can't add one more!" << endl;
        return;
    }
    if(field[x][y]->no_hero()){
        field[x][y]->create_unit(hero_code);
        unit_count++;
    }
}

void Cell::del_unit(){
    delete hero;
    hero = nullptr;
}

void GameField::delete_hero(int x, int y){
    field[x][y]->del_unit();
    unit_count--;
}

void Cell::copy_unit(Unit *original){
    hero = new Unit(*original);
}

void GameField::add_copy_hero(int x, int y, Unit *original){
    field[x][y]->copy_unit(original);
}

void GameField::copy_field(){
    GameField* new_F = new GameField(n, m);
    new_F->set_unit_count(unit_count);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(!field[i][j]->no_hero()){
                new_F->add_copy_hero(i, j, field[i][j]->hero_ad());
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(field[i][j]->no_hero()){
                cout << ". ";
            }
            else{
                cout << field[i][j]->get_let() << " ";
            }
        }
        cout << "\t";
        for(int j=0; j<m; j++){
            if(new_F->field[i][j]->no_hero()){
                cout << ". ";
            }
            else{
                cout << new_F->field[i][j]->get_let() << " ";
            }
        }
        cout << endl;
    }
}
