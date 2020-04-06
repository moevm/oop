#include "NeutralObject.h"

NeutralObject::NeutralObject(char name, int healthEffect, int damageEffect, int view) {
	setName(name);
	this->healthEffect = healthEffect;
	this->damageEffect = damageEffect;
	setView(view);
}

HolyCross::HolyCross() : NeutralObject((char)390, 100, 0,  8) {}     
Tablet::Tablet() : NeutralObject((char)299, 150, 0, 7) {}
Snake::Snake() : NeutralObject((char)382, 100, 0, 8) {}

SurpriseBox::SurpriseBox(int typeBox) : NeutralObject((char)63, 200, 200, 7) {
	this->typeBox = typeBox;
}
