#include "pch.h"
#include "Landscape.h"
#include "Object.h"
#include "Map.h"
#include "ctime"
#include <Windows.h>


Land::Land(char N, int width, int height, int col) : name(N), width(width), height(width){
		object = name;
		max_size = width*height;
		color = col;
		if (name == '~') max_water = max_size * 0.2;
		else max_water = 0;
		if (name == '*') max_grass = max_size;
		else max_grass = 0;
		if (name == '^') max_stones = max_size * 0.3;
		else max_stones = 0;
}


void Land::generation(Map *field)
{
	srand(time(0));

	while (max_grass != 0)
	{
		x = 1;
		y = 1;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
			{
				(*field).add_on_map(x, y, this);
				max_grass--;
				y++;
			}
			x++;
			y = 1;
		}
	}
	while (max_water != 0)
	{

		x = rand() % width;
		y = rand() % height;
		(*field).add_on_map(x, y, this);
		max_water--;
	}

	
	while (max_stones != 0)
	{
		x = rand() % width;
		y = rand() % height;
		(*field).add_on_map(x, y, this);
		max_stones--; 
	}

}


Water::Water(int width, int height) : Land('~', width, height, colorLand::blue) {
}


Grass::Grass(int width, int height) : Land('*', width, height, colorLand::green) {
}


Stones::Stones(int width, int height) : Land('^', width, height, colorLand::grey) {
}


