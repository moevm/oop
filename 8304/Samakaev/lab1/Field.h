#pragma once
#include "unit.h"

class Field {
public:

	Field(size_t x, size_t y) {
		field_cells = new char[x * y];
		x_size = x;
		y_size = y;
		unit_field = new Unit * [x * y];
		for (size_t i = 0; i < x * y; i++) {
			field_cells[i] = ' ';
		}
	}

	~Field() {
		delete field_cells;
		for (size_t i = 0; i < this->x_size * this->y_size; i++) {
			if (unit_field[i] != nullptr)
				unit_field[i]->~Unit();
		}
		delete unit_field;
	}

	void add_unit(Unit* test) {
		field_cells[test->get_x() + x_size * test->get_y()] = test->get_unit_name();
		unit_field[test->get_x() + x_size * test->get_y()] = test;
	}

	void delete_unit(size_t x, size_t y) {
		field_cells[x + x_size * y] = ' ';
		unit_field[x + x_size * y]->~Unit();
		return;
	}

	void relocate_unit(size_t old_x, size_t old_y, size_t x, size_t y) {
		unit_field[old_x + x_size * old_y]->change_position(x, y);
		add_unit(unit_field[old_x + x_size * old_y]);
		delete_unit(old_x, old_y);

		field_cells[x + x_size * y] = unit_field[x + x_size * y]->get_unit_name();
	}

	void print_field() {
		std::cout << " ";
		for (size_t i = 0; i < this->x_size; i++)
			std::cout << "_";
		for (size_t i = 0; i < this->x_size * this->y_size; i++) {
			if (i % x_size == 0) {
				if (i != 0)
					std::cout << "|" << std::endl;
				else
					std::cout << std::endl;
				std::cout << "|";
			}
			std::cout << field_cells[i];
		}
		std::cout << "|" << "\n" << " ";
		for (size_t i = 0; i < this->x_size; i++)
			std::cout << "-";
		std::cout << std::endl;
	}

	Field& operator=(const Field& field) {
		this->~Field();
		x_size = field.x_size;
		y_size = field.y_size;
		field_cells = new char[x_size * y_size];
		unit_field = new Unit * [x_size * y_size];
		for (size_t i = 0; i < field.x_size * field.y_size; i++) {
			if (field.field_cells[i] != ' ') {
				unit_field[i] = new Unit(*field.unit_field[i]);
			}
			field_cells[i] = field.field_cells[i];
		}
		return *this;
	}
private:
	size_t x_size = 0;
	size_t y_size = 0;

	char* field_cells;

	Unit** unit_field;
};