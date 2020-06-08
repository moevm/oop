#pragma once
#include <iostream>
#include "Unit.h"
enum landscape { Mountain = 1, Lake = 2, Forest = 3, Sunflower = 5};


//л€гушки и орущие €щерки: поле - норм, озеро - реген, гора - норм, дорога и пики - боль
//волки и гиены: 
//вороны и д€тлы: 
//ланшафты: поле подсолнухов, обычна€ гравива€ дорога, лес пик, озеро, гора

//биомы		поле	пики	озеро	гора
//+:		всем	живот	земно	птицы
//0:		норм	земно	птицы	живот
//-:		ваще	птицы	живот	земно
class biome {
protected:
	char icon;
	int color;
	int background;

public:
	biome();
	int get_color();
	int get_background();
	char get_icon();
	int get_effect(unit* uni);
};

class sunflower:public biome {
public:
	sunflower();
};

class lake :public biome {
public:
	lake();
};

class forest :public biome {
public:
	forest();
};

class mountain :public biome {
public:
	mountain();
};