#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "GameMod.h"

using namespace sf;

class GameFacade
{
private:
	Adapter * adapter;
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
	bool mod = true;
	bool gameInProcess = true;
public:
	GameFacade();
	bool play();
	void move();
	void click();
	void attack();
	void save();
	void load();
	void fileON();
	void fileOFF();
	void logON();
	void logOFF();
	void restart();
	void switchGameMod();
};

