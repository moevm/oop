#include "Shape.h"

class Ellipse : public Shape {

private:

	double minDiameter;
	double maxDiameter;

public:

	Ellipse(double diameter, double _diameter, point _centre) : Shape(_centre) {

		if (diameter > _diameter) {

			minDiameter = _diameter;
			maxDiameter = diameter;
		}
		else {

			minDiameter = diameter;
			maxDiameter = _diameter;
		}

		make_coordinates();
	}

	void scale(double coefficient) {

		minDiameter = minDiameter * coefficient;
		maxDiameter = maxDiameter * coefficient;
		make_coordinates();
	}

	~Ellipse() {

		coordinates.clear();
	}

private:

	void make_coordinates() {

		coordinates.clear();
		coordinates.push_back({ centre.x, centre.y + minDiameter / 2 });
		coordinates.push_back({ centre.x + maxDiameter / 2, centre.y });
		coordinates.push_back({ centre.x, centre.y - minDiameter / 2 });
		coordinates.push_back({ centre.x - maxDiameter / 2, centre.y });

		rotate(ang);
	}

	void print(ostream& out) {

		out << "Эллипс" << endl;
		out << "Id: " << id << endl;
		out << "Координаты крайних точек: ";

		for (unsigned int i = 0; i < coordinates.size(); ++i) {

			out << "(" << coordinates[i].x << ", " << coordinates[i].y << ") ";
		}

		out << endl << "Цвет: ";

		switch (clr) {

		case RED:
			out << "красный" << endl;
			break;
		case ORANGE:
			out << "оранжевый" << endl;
			break;
		case GREEN:
			out << "зеленый" << endl;
			break;
		case BLUE:
			out << "голубой" << endl;
			break;
		case YELLOW:
			out << "желтый" << endl;
			break;
		case NO_COLOR:
			out << "не определен" << endl;
			break;
		}
	}

};