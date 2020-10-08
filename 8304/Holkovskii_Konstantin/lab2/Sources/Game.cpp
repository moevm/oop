#include "../Headers/Game.h"

#include <memory>

Game::Game(int s, int l):field(Field(s,l)), selected({{-1,-1},false}) {}

void Game::select(Point const &a) {
    if(a.x < 0 || a.y<0 || a.x >= field.width || a.y >= field.height) {
        std::cout << "Задана некорректная координата" << std::endl;
        return;
    }
    selected.pos.x = a.x;
    selected.pos.y = a.y;
    selected.isBase = field[a.y][a.x].base != nullptr;
}

void Game::addUnit(Point const &a, char Name) {
    if(!selected.isBase) {
        std::cout << "Чтобы добавить юнита, нужно выбрать его базу!" << std::endl;
        return;
    }
    if(a.x < 0 || a.y<0 || a.x >= field.width || a.y >= field.height) {
        std::cout << "Задана некоректная координата" << std::endl;
        return;
    }
    if(std::pow(a.x - selected.pos.x,2) + std::pow(a.y - selected.pos.y,2) > 16){
        std::cout << "Данная точка находится слишком далеко от базы" << std::endl;
        return;
    }
    if(field[a.y][a.x].base != nullptr || field[a.y][a.x].unit != nullptr){
        std::cout << "На заданной точке уже кто-то/что-то стоит" << std::endl;
        return;
    }
    if(field.Count == field.MaxCount || field[selected.pos.y][selected.pos.x].base->count == field[selected.pos.y][selected.pos.x].base->max_count) {
        std::cout << "Лимит добавления юнитов!!!" << std::endl;
        return;
    }
    field.addUnit(a, Name);
    field[selected.pos.y][selected.pos.x].base->addUnit(a);
}

void Game::addBase() {
    if(selected.pos.y == -1 || selected.pos.x == -1){
        std::cout << "Сначала выберите, куда добавить базу" << std::endl;
    }
    if(selected.isBase || field[selected.pos.y][selected.pos.x].unit != nullptr){
        std::cout << "На заданной точке уже кто-то/что-то стоит" << std::endl;
        return;
    }
    selected.isBase = true;
    field[selected.pos.y][selected.pos.x].base = static_cast<std::shared_ptr<Base>>(new Base());
    field.ListBases.push_back(field[selected.pos.y][selected.pos.x].base);
}

void Game::show() {
    field.show();
}

void Game::moveUp() {
    if(selected.isBase) {
        std::cout << "Здания не умеют ходить" << std::endl;
        return;
    }
    if(selected.pos.x == -1 && selected.pos.y == -1) {
        std::cout << "Сначала выберите юнита" << std::endl;
        return;
    }
    if(selected.pos.y+1 == field.height || field[selected.pos.y + 1][selected.pos.x].base != nullptr || field[selected.pos.y + 1][selected.pos.x].unit != nullptr){
        std::cout << "Дальше какое-то препятствие" << std::endl;
        return;
    }
    field.move(selected.pos, {selected.pos.x,selected.pos.y + 1});
}

void Game::moveLeft() {
    if(selected.isBase) {
        std::cout << "Здания не умеют ходить" << std::endl;
        return;
    }
    if(selected.pos.x == -1 && selected.pos.y == -1) {
        std::cout << "Сначала выберите юнита" << std::endl;
        return;
    }
    if(selected.pos.x == 0 || field[selected.pos.y][selected.pos.x - 1].base != nullptr || field[selected.pos.y][selected.pos.x - 1].unit != nullptr){
        std::cout << "Дальше какое-то препятствие" << std::endl;
        return;
    }
    field.move(selected.pos, {selected.pos.x - 1,selected.pos.y});
}

void Game::moveRight() {
    if(selected.isBase) {
        std::cout << "Здания не умеют ходить" << std::endl;
        return;
    }
    if(selected.pos.x == -1 && selected.pos.y == -1) {
        std::cout << "Сначала выберите юнита" << std::endl;
        return;
    }
    if(selected.pos.x + 1== field.width || field[selected.pos.y][selected.pos.x + 1].base != nullptr || field[selected.pos.y][selected.pos.x + 1].unit != nullptr){
        std::cout << "Дальше какое-то препятствие" << std::endl;
        return;
    }
    field.move(selected.pos, {selected.pos.x + 1,selected.pos.y});
}

void Game::moveDown() {
    if(selected.isBase) {
        std::cout << "Здания не умеют ходить" << std::endl;
        return;
    }
    if(selected.pos.x == -1 && selected.pos.y == -1) {
        std::cout << "Сначала выберите юнита" << std::endl;
        return;
    }
    if(selected.pos.y == 0 || field[selected.pos.y - 1][selected.pos.x].base != nullptr || field[selected.pos.y - 1][selected.pos.x].unit != nullptr){
        std::cout << "Дальше какое-то препятствие" << std::endl;
        return;
    }
    field.move(selected.pos, {selected.pos.x,selected.pos.y - 1});
}

void Game::Attack(Point const &a) {
    if(a.x < 0 || a.y<0 || a.x >= field.width || a.y >= field.height) {
        std::cout << "Задана некорректная координата" << std::endl;
        return;
    }
    if(field[selected.pos.y][selected.pos.x].unit == nullptr){
        std::cout << "Выберите юнита которым хотите атаковать" << std::endl;
        return;
    }
    if(std::pow(a.x - selected.pos.x,2)+std::pow(a.y - selected.pos.y,2) > std::pow(field[selected.pos.y][selected.pos.x].unit->range,2)) {
        std::cout << "Дальность атаки не позволяет" << std::endl;
        return;
    }
    if(field[a.y][a.x].unit == nullptr) {
        std::cout << "Вы бъете воздух ;)" << std::endl;
        return;
    }
    field[a.y][a.x].unit->takeDmg(field[selected.pos.y][selected.pos.x].unit->damage.get());
    int oleg = field[a.y][a.x].unit->hp.hp;
    if(field[a.y][a.x].unit->hp.hp == 0)
        field.remUnit(a);
}

