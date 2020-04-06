// 1lb.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <Windows.h>
#include "Game.h"


using namespace std;

int main() {
	system("chcp 1251");  //русский язык
	system("cls");        //очистить консоль
	Game game;
	game.choice_map();
}









