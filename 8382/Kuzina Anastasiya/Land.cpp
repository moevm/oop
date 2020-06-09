#include "Land.h"


biome::biome() {
	icon = 'M';
	color = 15;
	background = 0;
}

char biome::get_icon() {
	return icon;
}

int biome::get_background() {
	return background;
}

int biome::get_color() {
	return color;
}

int biome::get_effect(unit* uni) {
	if (icon == 'M')return 0;
	char nam = uni->get_name();
	switch (nam) {
	case 'w': {}
	case 'h': {
		if (icon == 15) { return 0; }
		if (icon == 126) { return -3; }
		if (icon == 6) { return 1; }
		if (icon == 94) { return 0; }
		break;
	}
	case 'l': {}
	case 'f': {
		if (icon == 15) { return 0; }
		if (icon == 126) { return 1; }
		if (icon == 6) { return 0; }
		if (icon == 94) { return -3; }
		break;
	}
	case 'c': {}
	case 'd': {
		if (icon == 15) { return 0; }
		if (icon == 126) { return 0; }
		if (icon == 6) { return -3; }
		if (icon == 94) { return 1; }
		break;
	}
	}
	return 0;
}

sunflower::sunflower():biome(){
	icon = 15;
	color = 14;
	background = 2;
}

lake::lake() : biome() {
	icon = 126;
	color = 9;
	background = 1;
}

forest::forest() : biome() {
	icon = 6;//24 6
	color = 4;//2
	background = 6;//6
}

mountain::mountain() : biome() {
	icon = 94; //251 30 !94! 94
	color = 7;
	background = 8;//8
}

