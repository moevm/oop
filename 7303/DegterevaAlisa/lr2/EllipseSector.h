#include "Shape.h"

class EllipseSector : public Shape {

	struct radius {

		double rad;
		double angle;
	};

private:

	radius rd[2];

public:

	EllipseSector(radius rd0, radius rd1, point _centre) : Shape(_centre) {

		rd[0].rad = rd0.rad;
		rd[1].rad = rd1.rad;
		rd[0].angle = rd0.angle;
		rd[1].angle = rd1.angle;

		make_coordinates();

	}

	void scale(double coefficient) {

		for (int i = 0; i < 2; ++i) {

			rd[i].rad = rd[i].rad * coefficient;
		}
		make_coordinates();
	}

	~EllipseSector() {

		coordinates.clear();
	}

private:

	void make_coordinates() {

		coordinates.clear();
		coordinates.push_back(centre);

		for (int i = 0; i < 2; ++i) {

			double _x = rd[i].rad;
			double _y = 0;

			point _point;
			_point.x = _x * cos(rd[i].angle) + centre.x;
			_point.y = _x * sin(rd[i].angle) + centre.y;

			coordinates.push_back(_point);
		}

		rotate(ang);
	}

	void print(ostream& out) {

		out << "Сектор эллипса" << endl;
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