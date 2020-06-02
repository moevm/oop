#pragma once

#include "Bases.h"
#include "Map.h"
#include "Recorder.h"
#include "Landscape.h"
#include "Neutral.h"

///Класс управления базой 
class Facade {
private:
	int _x_max, _y_max;
	Bases* base = nullptr;
	Bases* base_2 = nullptr;
	Map* field = nullptr;
	Recorder *rec = nullptr;
	Landscape *land = nullptr;
	Creating *neutral = nullptr;
public:
	Facade(Bases* base, Map* field) : base(base), field(field) {}
	bool generation();
};


