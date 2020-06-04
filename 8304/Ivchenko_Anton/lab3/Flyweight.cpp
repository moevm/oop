
#include "Flyweight.h"

TypeOfUnit::TypeOfUnit() {

	Atributes* infantry = new Atributes(10, 10, 3);
	Atributes* archers = new Atributes(15, 5, 2);
	Atributes* cavalry = new Atributes(10, 8, 5);
	my_map['i'] = infantry;
	my_map['a'] = archers;
	my_map['c'] = cavalry;

}
Atributes* TypeOfUnit::getType(char a) {
		return my_map[a];
}
