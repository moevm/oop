#include <iostream>
#include <string>
#include <Windows.h>
#include "Field.h"
#include "Unit_types.h"
using namespace std;



int main() 
{
	string ctrl;
	int W, H;
	cout << "Input field size\n";
	W = 10; H = 10;
	Field field(W, H);
	Field field_save(W, H);
	Field f = Field(W,H);

	Berserks b(15);
	b.set_cords(1, 4);
	b.set_team(1);
	b.place(field);

	field.add_unit("CC", 4, 5, 99);
	field.add_unit("CC", 5, 4, 19);
	field.move_unit(4, 5, 4, 3);
	Field::Iterator iter = field.begin();
	
	while (iter != field.end()) {
		std::cout << iter.operator*()->health << " " << iter.operator*()->armor  << " " <<  iter.operator*()->attack << std::endl;
		iter++;
	}

	while (1)
	{
		
		field.print();
		cin >> ctrl;
		
		if (ctrl == "q")
			break;
		if (ctrl == "c")
		{
			cout << "Input: code X Y N\n";
			int X, Y, N;
			cin >> ctrl;
			cin >> X; cin >> Y; cin >> N;
			field.add_unit(ctrl, X, Y, N);
		}
		if (ctrl == "m")
		{
			cout << "Input: code X1 Y1 X2 Y2\n";
			int X1, Y1, X2, Y2;
			cin >> X1; cin >> Y1; cin >> X2; cin >> Y2;
			field.move_unit(X1, Y1, X2, Y2);
		}
		if (ctrl == "s")
		{
			field.save(field_save);
			cout << "Saved\n";
		}
		if (ctrl == "l")
		{
			field.load(field_save);
			cout << "Loaded\n";
		}//f.print();
		system("pause");
		system("cls");
	}
	
	return 0;
}