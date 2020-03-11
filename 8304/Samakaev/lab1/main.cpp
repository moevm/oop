#include "field.h"
#include "unit.h"

int main() {

	Field field = { 6, 6 };
	field.print_field();
	Vehicle vehicle{ 0,0,0,2,2,'V' };
	Humans human{ 0,0,0,1,2,'H' };
	Beasts beast{ 0,0,0,3,3,'B' };
	field.add_unit(&vehicle);
	field.print_field();
	
	Field field_cpy = { 4, 4 };
	field_cpy.add_unit(&human);
	field_cpy.print_field();
	field_cpy = field;
	field_cpy.add_unit(&beast);
	field_cpy.print_field();
	field_cpy.relocate_unit(3, 3, 5, 5);
	field_cpy.print_field();

	

	return 0;
}