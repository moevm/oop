#pragma once
#include "unit_factory.h"
#include "Landscape.h"
#include "Nobjects.h"
#include "GameBase.h"
#include <fstream>
#include <map>
#include <regex>

class Field {
public:
	Field() = default;
	Field(size_t x, size_t y) {
		max_unit_cnt = x * y;

		cell_land_types = new LandscapeType[x * y];
		cell_nobj_types = new Nobjects*[x * y];
		cell_base = new GameBase*[x * y];
		field_cells = new char[x * y];
		unit_field = new Unit*[x * y];
		x_size = x;
		y_size = y;
		for (size_t i = 0; i < x * y; i++) {
			field_cells[i] = ' ';
			unit_field[i] = nullptr;
			cell_base[i] = nullptr;

			size_t chance = std::rand() % 3;
			switch (chance)
			{
			case 0:
				cell_land_types[i] = LandscapeType::desert;
				break;
			case 1:
				cell_land_types[i] = LandscapeType::mountain;
				break;
			case 2:
				cell_land_types[i] = LandscapeType::swamp;
				break;
			default:
				break;
			}

			chance = std::rand() % 10;

			switch (chance)
			{
			case 0:
				cell_nobj_types[i] = new HillingSatue;
				break;
			case 1:
				cell_nobj_types[i] = new ArmorStatue;
				break;
			case 2:
				cell_nobj_types[i] = new DamageStatue;
				break;
			case 3:
				cell_nobj_types[i] = new BigStatue;
				break;
			default:
				cell_nobj_types[i] = nullptr;
				break;
			}
		}
	}

	Field(size_t x, size_t y, size_t max_unit_cnt) {
		this->max_unit_cnt = max_unit_cnt;

		cell_land_types = new LandscapeType[x * y];
		cell_nobj_types = new Nobjects*[x * y];
		cell_base = new GameBase * [x * y];
		field_cells = new char[x * y];
		x_size = x;
		y_size = y;
		unit_field = new Unit*[x * y];
		for (size_t i = 0; i < x * y; i++) {
			field_cells[i] = ' ';
			unit_field[i] = nullptr;
			cell_base[i] = nullptr;

			size_t chance = std::rand() % 3;
			switch (chance)
			{
			case 0:
				cell_land_types[i] = LandscapeType::desert;
				break;
			case 1:
				cell_land_types[i] = LandscapeType::mountain;
				break;
			case 2:
				cell_land_types[i] = LandscapeType::swamp;
				break;
			default:
				break;
			}

			chance = std::rand() % 10;

			switch (chance)
			{
			case 0:
				cell_nobj_types[i] = new HillingSatue;
				break;
			case 1:
				cell_nobj_types[i] = new ArmorStatue;
				break;
			case 2:
				cell_nobj_types[i] = new DamageStatue;
				break;
			case 3:
				cell_nobj_types[i] = new BigStatue;
				break;
			default:
				cell_nobj_types[i] = nullptr;
				break;
			}
		}
	}

	~Field() {

	}

	void add_unit(Unit* unit, size_t x, size_t y) {

		LandscapeProxy proxy(cell_land_types[x + x_size * y]);
		proxy.setEffect(unit);
		unit->ind = x + x_size * y;

		if (cell_nobj_types[x + x_size * y] != nullptr)
			(*cell_nobj_types[x + x_size * y])(unit);

		field_cells[x + x_size * y] = unit->name;
		unit_field[x + x_size * y] = unit;
		current_unit_cnt++;
	}

	void delete_unit(size_t x, size_t y) {
		if (unit_field[x + x_size * y]->my_base != nullptr)
			unit_field[x + x_size * y]->my_base->unsubscribe(unit_field[x + x_size * y]);

		field_cells[x + x_size * y] = ' ';
		current_unit_cnt--;
		delete unit_field[x + x_size * y];
		unit_field[x + x_size * y] = nullptr;
	}

	void relocate_unit(size_t old_x, size_t old_y, size_t x, size_t y) {
		LandscapeProxy proxy(cell_land_types[x + x_size * y]);
		proxy.setEffect(unit_field[old_x + x_size * old_y]);
		unit_field[old_x + x_size * old_y]->ind = x + x_size * y;

		if (cell_nobj_types[x + x_size * y] != nullptr)
			(*cell_nobj_types[x + x_size * y])(unit_field[old_x + x_size * old_y]);
		unit_field[x + x_size * y] = unit_field[old_x + x_size * old_y];
		unit_field[old_x + x_size * old_y] = nullptr;
	}

	void add_base(GameBase* base, size_t x, size_t y)
	{
		cell_base[x + x_size * y] = base;
	}

	void add_base_unit(Unit* unit, size_t x, size_t y)
	{
		bool f = cell_base[x + x_size * y]->subscribe(unit);
		if (f == true)
		{
			unit->my_base = cell_base[x + x_size * y];
			add_unit(unit, x, y);
		}

	}

	Field& operator=(const Field& field) {
		
		x_size = field.x_size;
		y_size = field.y_size;

		max_unit_cnt = field.max_unit_cnt;
		current_unit_cnt = field.current_unit_cnt;

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

	Field& operator=(const Field&& field) noexcept
	{
		this->cell_base = field.cell_base;
		this->cell_land_types = field.cell_land_types;
		this->cell_nobj_types = field.cell_nobj_types;
		this->field_cells = field.field_cells;
		this->unit_field = field.unit_field;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, Field& field) {
		out << " ";
		for (size_t i = 0; i < field.x_size; i++)
			out << "_";
		for (size_t i = 0; i < field.x_size * field.y_size; i++) {
			if (i % field.x_size == 0) {
				if (i != 0)
					out << "|" << std::endl;
				else
					out << std::endl;
				out << "|";
			}
			if (field.unit_field[i] != nullptr)
				out << field.unit_field[i]->name;
			else
				out << " ";
		}
		out << "|" << "\n" << " ";
		for (size_t i = 0; i < field.x_size; i++)
			out << "-";
		out << std::endl;

		return out;
	}

	size_t getX_SIZE()
	{
		return x_size;
	}
	size_t getY_SIZE()
	{
		return y_size;
	}
	Unit** getUNIT_FIELD()
	{
		return unit_field;
	}
	GameBase** getCELL_BASE()
	{
		return cell_base;
	}

	class Snapshot
	{
		friend Field;
		std::string data;

	public:
		Snapshot(std::string& data) : data(data)
		{}

		void write()
		{
			std::ofstream out("save.txt");

			out << data;
			out.close();
		}
	};

	Snapshot* saveState()
	{
		std::string all_data;

		std::map<LandscapeType, char> land_types_converter;
		land_types_converter[LandscapeType::desert] = 'D';
		land_types_converter[LandscapeType::mountain] = 'M';
		land_types_converter[LandscapeType::swamp] = 'S';


		for (size_t i = 0; i < y_size * x_size; ++i)
		{
			std::string cur_cell_info;

			char land_name = land_types_converter[cell_land_types[i]];

			char ntrl_obj_name = '0';
			if (cell_nobj_types[i] != nullptr)
				ntrl_obj_name = cell_nobj_types[i]->getName();

			char base_name = '0';
			if (cell_base[i] != nullptr)
				base_name = 'B';

			std::string unit_data;
			if (unit_field[i] != nullptr)
			{
				Unit* unit = unit_field[i];

				unit_data += unit->name;
				unit_data += ';';
				unit_data += std::to_string(unit->hp.get());
				unit_data += ';';
				unit_data += std::to_string(unit->damage.get());
				unit_data += ';';
				unit_data += std::to_string(unit->armor.get());
				unit_data += ';';
				unit_data += std::to_string(unit->my_base->ind);
				unit_data += ';';
				unit_data += std::to_string(unit->ind);
			}

			cur_cell_info += land_name;
			cur_cell_info += ntrl_obj_name;
			cur_cell_info += base_name;
			cur_cell_info += unit_data;

			all_data += cur_cell_info;
		}

		Snapshot* snap = new Snapshot(all_data);

		return snap;
	}

	bool loadState(Snapshot* snap)
	{
		std::string data = snap->data;
		Field tmp_field(10, 10);

		size_t ind = 0;
		std::regex pattern("([DMS])([0HADB])([0B])");
		std::smatch match;

		while (std::regex_search(data, match, pattern) != 0)
		{
			char land_name = match[1].str()[0];
			char ntrl_obj_name = match[2].str()[0];
			char base_name = match[3].str()[0];

			switch (land_name)
			{
			case 'D':
				tmp_field.cell_land_types[ind] = LandscapeType::desert;
				break;
			case 'M':
				tmp_field.cell_land_types[ind] = LandscapeType::mountain;
				break;
			case 'S':
				tmp_field.cell_land_types[ind] = LandscapeType::swamp;
				break;
			default:
				break;
			}

			switch (ntrl_obj_name)
			{
			case 'H':
				tmp_field.cell_nobj_types[ind] = new HillingSatue;
				break;
			case 'A':
				tmp_field.cell_nobj_types[ind] = new ArmorStatue;
				break;
			case 'D':
				tmp_field.cell_nobj_types[ind] = new DamageStatue;
				break;
			case 'B':
				tmp_field.cell_nobj_types[ind] = new BigStatue;
				break;
			default:
				tmp_field.cell_nobj_types[ind] = nullptr;
				break;
			}

			switch (base_name)
			{
			case 'B':
				tmp_field.cell_base[ind] = new GameBase(ind);
				break;
			default:
				tmp_field.cell_base[ind] = nullptr;
				break;
			}

			data.erase(data.begin() + match.position(), data.begin() + match.position() + match.length());
			++ind;
		}

		if (ind != 100)
			return false;

		std::regex unit_pattern("([AMTCKR]);(\\d+);(\\d+);(\\d+);(\\d+);(\\d+)");
		std::smatch unit_match;

		Unit* unit = nullptr;
		while (std::regex_search(data, unit_match, unit_pattern) != 0)
		{
			char unit_name = unit_match[1].str()[0];
			int unit_hp = std::stoi(unit_match[2].str());
			int unit_damage = std::stoi(unit_match[3].str());
			int unit_armor = std::stoi(unit_match[4].str());
			int unit_base_ind = std::stoi(unit_match[5].str());
			int unit_ind = std::stoi(unit_match[6].str());

			switch (unit_name)
			{
			case 'A':
				unit = new Archer;
				break;
			case 'M':
				unit = new Mage;
				break;
			case 'T':
				unit = new Siege_tower;
				break;
			case 'C':
				unit = new Catapult;
				break;
			case 'K':
				unit = new Knight;
				break;
			case 'R':
				unit = new Rogue;
				break;
			default:
				break;
			}

			unit->hp.change(unit_hp);
			unit->damage.change(unit_damage);
			unit->armor.change(unit_armor);
			unit->ind = unit_ind;
			unit->my_base = tmp_field.cell_base[unit_base_ind];
			
			if (tmp_field.cell_base[unit_base_ind] == nullptr)
			{
				delete unit;
				return false;
			}

			unit->my_base->subscribe(unit);

			if (tmp_field.unit_field[unit_ind] != nullptr)
			{
				delete unit;
				return false;
			}

			LandscapeProxy proxy(tmp_field.cell_land_types[unit_ind]);
			proxy.setEffect(unit);

			tmp_field.unit_field[unit_ind] = unit;

			data.erase(data.begin() + unit_match.position(), data.begin() + unit_match.position() + unit_match.length());
		}

		if (data.empty())
		{
			(*this) = std::move(tmp_field);
			return true;
		}

		return false;
	}

private:
	size_t max_unit_cnt = 0;
	size_t current_unit_cnt = 0;

	size_t x_size = 0;
	size_t y_size = 0;

	char* field_cells;
	Unit** unit_field;

	LandscapeType* cell_land_types;
	Nobjects** cell_nobj_types;
	GameBase** cell_base;
};