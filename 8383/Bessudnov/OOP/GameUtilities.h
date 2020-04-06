#pragma once

#define UNIT_L_BEE 'A'
#define UNIT_D_FLY 'B'
#define UNIT_L_FLOWER 'C'
#define UNIT_D_COAL 'D'
#define UNIT_L_SPRINKLER 'E'
#define UNIT_D_COLLECTOR 'F'

#define FIELD_MAX_SIZE 50
#define FIELD_MIN_SIZE 10

class Vector2D {
public:
	int x;
	int y;

	Vector2D(const Vector2D &vec) : x(vec.x), y(vec.y){}
	Vector2D(int x, int y) : x(x), y(y) {}
	Vector2D() : x(0), y(0) {}

	Vector2D &operator=(const Vector2D &vec) {
		if (&vec == this) return *this;

		x = vec.x;
		y = vec.y;

		return *this;
	}

	Vector2D operator+(const Vector2D &vec) {
		Vector2D newVec;

		newVec.x = vec.x + x;
		newVec.y = vec.y + y;

		return Vector2D(vec.x + x, vec.y + y);
	}

	int operator==(const Vector2D &vec) {
		if (x == vec.x && y == vec.y) return 1;

		return 0;
	}
};


class GameUtilities {
public:
	static void clamp(int &value, int max, int min);
	static void clamp(Vector2D &value, int max, int min);
	static void clamp(Vector2D &value, Vector2D max, Vector2D min);
	GameUtilities();
	~GameUtilities();
};

template <typename type> class Field {
protected:
	Vector2D dimensions;
	type **field;
public:

	Field(Vector2D size) : dimensions(size) {
		field = new type*[size.x];
		for (int i = 0; i < size.x; i++) {
			field[i] = new type[size.y];
		}
	}

	~Field() {
		for (int i = 0; i < dimensions.x; i++) {
			delete[] field[i];
		}

		delete field;
	}

	void emplaceElement(type elem, Vector2D location);
	type getElement(Vector2D location);
};

template<typename type>
inline void Field<type>::emplaceElement(type elem, Vector2D location) {
	field[location.x][location.y] = elem;
}

template<typename type>
inline type Field<type>::getElement(Vector2D location) {
	return field[location.x][location.y];
}
