#include <iostream>
#include "Field.h"
#include "unit.h"

int main() {

	Field f(10, 5, 10);
	Swordman swm;
	Spearman spm;

	f.AddObj(&swm, 1, 1);
	f.AddObj(&spm, 2, 3);
	f.Moving(&spm, 2, 3, 1, 1);
	f.RemObj(1, 1);
	f.PrintField();

	std::cout << std::endl;


	//Field newfield(10, 5, 10);
	//newfield = f;
	//Field newfield(f);
	//newfield.PrintField();

	//Field newfield(10,5,10);
	//Field *n = f.CopyField(&newfield);
	//n->PrintField();




}
