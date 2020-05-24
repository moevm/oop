#include <iostream>
#include "GameSingleton.h"



int main() {
	setlocale(LC_ALL, "RUS");
	//Game game;
	GameSingleton game;
	game.startGame();
	return 0;
}