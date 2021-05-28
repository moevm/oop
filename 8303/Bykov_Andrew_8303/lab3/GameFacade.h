#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Field.h"
#include "Base.h"
#include <fstream>
using namespace sf;



class GameFacade
{
private:
	RenderWindow * window;
	Field * field;
	Base * base[2];
	Texture tileSet;
	Sprite tile;
	string command;
	Clock clock;
	int squad = 0;
	int flip = 0;
	bool clicked = true;
	bool fieldIsInit = false;

public:
	GameFacade();
	bool play();
	void move();
	void click();
	void attack();
	void switchUsers();
};

