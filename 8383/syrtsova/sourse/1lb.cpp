// 1lb.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include "Game.hpp"
#include <Windows.h>
#include "Rule_1.h"
#include "Rule_2.h"
#include "Rules.h"

using namespace std;

int main() {
	system("chcp 1251");  //русский язык
	system("cls");        //очистить консоль
	std::shared_ptr<Rules> rule = std::make_shared<Rule_1>();
	Game<Rules>* game = Game<Rules>::get_game(rule);
}









