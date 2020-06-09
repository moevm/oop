#include "Item.h"
#include <iostream>

item::item() {
	name = 'I';
	effect = 0;
}

int item::get_effect() {
	return effect;
}

char item::get_name() {
	return name;
}

exp_bottle::exp_bottle() : item() {
	name = '$';
	effect = 20;
}

hp_pill::hp_pill() : item() {
	name = 3;
	effect = 4;
}

zatochka::zatochka() : item() {
	name = 4;
	effect = 1;
}

rpill::rpill() : item() {
	name = '*';
	effect = 1;
}