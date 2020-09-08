#include "pch.h"

#include <iostream>
#include "Unit.h"
#include "Field.h"
#include "FieldIterator.h"

void doNothing(Field fi) {
	//hi

};

int main()
{


	while (1488) {
		std::cout << "Choose game field size (2 positive integer numbers)" << std::endl;

		int w(0), h(0);

		std::cin >> w >> h;

		Field f(w, h);

		f.print();

		while (228) {
			std::cout << "Choose action" << std::endl;
			std::cout << "'+' - add Unit, '-' - remove Unit, 'a' - attack, 'm' - move" << std::endl;

			char action(0);
			std::cin >> action;
			int x(0), y(0);
			char unit(0);
			Unit* newUnit;
			int Ax(0), Ay(0);
			int Tx(0), Ty(0);
			int dx(0), dy(0);

			switch (action) {
			case '+':
				std::cout << "Enter position (2 positive integer numbers)" << std::endl;
				
				std::cin >> x >> y;

				std::cout << "Choose Unit type:" << std::endl;

				std::cout << "'m' - mortar" << std::endl
					<< "'c' - catapult" << std::endl
					<< "'s' - spearman" << std::endl
					<< "'r' - rogue" << std::endl
					<< "'l' - horsemen leader" << std::endl
					<< "'h' - regular horseman" << std::endl;

				std::cin >> unit;

				switch (unit) {
				case 'm':
					newUnit = new Mortar;
					break;

				case 'c':
					newUnit = new Catapult;
					break;

				case 's':
					newUnit = new Spearman;
					break;

				case 'r':
					newUnit = new Rogue;
					break;

				case 'l':
					newUnit = new HorsemenLeader;
					break;

				case 'h':
					newUnit = new RegularHorseman;
					break;

				default:
					newUnit = new Spearman;
					break;
				}

				f.addObj(newUnit, x, y);

				break;

			case '-':
				std::cout << "Enter coordinates (2 positive integer numbers)" << std::endl;

				std::cin >> x >> y;

				f.removeObj(location(x, y));
				break;

			case 'a':
				std::cout << "Enter attacker coordinates (2 positive integer numbers)" << std::endl;

				std::cin >> Ax >> Ay;

				std::cout << "Enter target coordinates (2 positive integer numbers)" << std::endl;

				std::cin >> Tx >> Ty;

				((f.GetHead())[Ay * f.getSize().width + Ax])->attack(&f, (f.GetHead())[Ty * f.getSize().width + Tx]);
				break;

			case 'm':
				std::cout << "Enter Unit coordinates (2 positive integer numbers)" << std::endl;

				std::cin >> x >> y;

				std::cout << "Enter horizontal and vertical steps (2 positive integer numbers)" << std::endl;

				std::cin >> dx >> dy;

				if (!((f.GetHead())[(y - 1) * f.getSize().width + (x - 1)]))
					break;

				((f.GetHead())[(y - 1) * f.getSize().width + (x - 1)])->move(&f, dx, dy);
				break;

			default:
				break;
			}

			f.print();
		}


	}

	return 0;
}


