#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
using namespace std;
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include "Field.h"
#include "Logger.h"
#include "Rules.h"
#include "Graphic.h"
#include "Player.h"
#include "Exept.h"


template <typename T>
class game {
private:
	T* rul;
	char in;
	field* F;
	player* first;
	player* second;
	int level;

	graphic* gui;

	int load_number(ifstream& fin) {
		int num = 0;
		bool negative = false;

		fin.get(in);
		if (in == '-') {
			negative = true;
			fin.get(in);
		}
		while (in != ' ' && in != '\n') {
			if (in == '\n') break;
			if (isdigit(in)) num = num * 10 + in - '0';
			else throw except("(game::load_number) Expect to read _number_ or _number\\n, but read other symbols!\n");
			fin.get(in);
		}
		if (negative) num = num * -1;


		return num;
	}
	player* load_player(ifstream& fin) {
		string w = "";
		int num = 0;

		fin.get(in);

		if (in == 'p') {
			fin.get(in);
			if (in != ' ') return NULL;

			fin.get(in);
			while (in != ' ') {
				if (in == '\n') return NULL;
				w.push_back(in);
				fin.get(in);
			}

			fin.get(in);
			while (in != ' ' && in != '\n') {
				if (in == '\n') break;
				if (isdigit(in)) num = num * 10 + in - '0';
				else break;
				fin.get(in);
			}
		}
		player* ple = new player(w, num);
		return ple;
	}
	void load_item(ifstream& fin) {
		int y = 0, x = 0, type = 0;

		fin.get(in);

		if (in == 'i') {
			fin.get(in);
			if (in != ' ') return;

			y = load_number(fin);
			x = load_number(fin);
			type = load_number(fin);

			printf("i %d %d %d\n", y, x, type);

			if (x < 0 || y < 0 || x >= F->get_x_size() || y >= F->get_y_size()) return;
			F->get_cell(x, y)->set_item(type);
		}
		else throw except("(game::load_item) Expected first-char i, was reseved " + to_string(in) + "\n");


		return;
	}
	base* load_base(ifstream& fin) {
		int y = 0, x = 0, number = 0, hp = 0;

		fin.get(in);

		if (in == 'b') {
			fin.get(in);
			if (in != ' ')	 throw except("(game::load_base) expected _ after b, but get: " + to_string(in) + "\n");

			y = load_number(fin);
			x = load_number(fin);
			number = load_number(fin);
			hp = load_number(fin);

			printf("b %d %d %d %d\n", y, x, number, hp);
		}
		else throw except("(game::load_base) Expected first-char b, was reseved " + to_string(in) + "\n");
		if (x < 0 || y < 0 || x >= F->get_x_size() || y >= F->get_y_size()) throw except("(game::load_base) Wrong base-coords(" + to_string(x) + "," + to_string(y) + "), dosn't fit field sizes(" + to_string(F->get_x_size()) + "," + to_string(F->get_y_size()) + ")!\n");

		base* b = new base(number);
		b->set_coords(x, y);
		b->set_hp(hp);
		return b;
	}
	void load_unit(ifstream& fin, base* b, int i) {
		char name = ' ';
		int y = 0, x = 0, hp = 0, hp_max = 0,
			armor = 0, attack = 0, xp = 0, xp_level = 1, level = 1;

		fin.get(in);

		if (in == 'u') {
			fin.get(in);
			if (in != ' ')  throw except("(game::load_base) expected _ after u, but get: " + to_string(in) + "\n");;

			y = load_number(fin);
			x = load_number(fin);

			fin.get(in);
			name = in;
			fin.get(in);

			hp = load_number(fin);
			hp_max = load_number(fin);
			armor = load_number(fin);
			attack = load_number(fin);
			xp = load_number(fin);
			xp_level = load_number(fin);
			level = load_number(fin);

			if (x < 0 || y < 0 || x >= F->get_x_size() || y >= F->get_y_size()) return;
			printf("u %d %d %c %d %d %d %d %d %d %d\n", y, x, name, hp, hp_max, armor, attack, xp, xp_level, level);
			b->set_unit(y, x, name, hp, hp_max, armor, attack, xp, xp_level, level, i);


		}
		else throw except("(game::load_unit) Expected first-char u, was reseved " + to_string(in) + "\n");

		return;
	}
	bool level_load() {
		bool i = false;
		if (level == 1) i = level1_load();
		if (level == 2) i = level2_load();
		if (level == 3) i = load_game();

		if (!i) return false;
		rul = new T;
		rul->starts(F);
		return true;
	}
	bool level1_load() {
		try {
			level = 1;
			first = new player("first", 1);
			second = new player("second", 2);
			F = new field(10, 10);
			first->get_base()->set_coords(2, 2);
			second->get_base()->set_coords(8, 8);
			F->set_base(8, 8, second->get_base());
			F->set_base(2, 2, first->get_base());

			F->find_empty(8, 8)->set_unit(second->get_base()->get_unit(0));
			F->find_empty(8, 8)->set_unit(second->get_base()->get_unit(1));
			F->find_empty(8, 8)->set_unit(second->get_base()->get_unit(2));
			F->find_empty(2, 2)->set_unit(first->get_base()->get_unit(0));
			F->find_empty(2, 2)->set_unit(first->get_base()->get_unit(1));
			F->find_empty(2, 2)->set_unit(first->get_base()->get_unit(2));
			logger::add("Level 1 sucessfully load\n");
			return true;
		}
		catch (except &ex) {
			level = 1;
			cout << "(game::level1_load) Something goes wrong with loading first level!\n\t" << ex.what() << "\n";
			return false;
		}
		return true;
	}
	bool level2_load() {
		try {
			first = new player("first", 1);
			second = new player("second", 2);
			F = new field(50, 30);
			first->get_base()->set_coords(25, 25);
			second->get_base()->set_coords(5, 5);
			F->set_base(5, 5, second->get_base());
			F->set_base(25, 25, first->get_base());

			F->find_empty(5, 5)->set_unit(second->get_base()->get_unit(0));
			F->find_empty(5, 5)->set_unit(second->get_base()->get_unit(1));
			F->find_empty(5, 5)->set_unit(second->get_base()->get_unit(2));
			F->find_empty(25, 25)->set_unit(first->get_base()->get_unit(0));
			F->find_empty(25, 25)->set_unit(first->get_base()->get_unit(1));
			F->find_empty(25, 25)->set_unit(first->get_base()->get_unit(2));
			logger::add("Level 1 sucessfully load\n");
			return true;
		}
		catch (except &ex) {
			level = 1;
			cout << "(game::level2_load) Something goes wrong with loading second level!\n\t" << ex.what() << "\n";
			return false;
		}
	}
	void level_unload() {
		
		level = 1;
		delete first;
		delete second;
		delete F;
		logger::add("Level sucessfully unload\n");
	}	
	void save_game() {
		if (level == 0) return;
		//ПРОВЕРКА ЗАГРУЖЕНА ЛИ ИГРА
		string name;
		time_t rawtime;
		struct tm* timeinfo;
		string SF = "SaveFiles\\";

		time(&rawtime);                         // текущая дата, выраженная в секундах
		timeinfo = localtime(&rawtime);   // текущая дата, представленная в нормальной форме
		name = asctime(timeinfo);
		for (int i = 0; i < name.size(); i++) {
			if (name[i] == ' ') name[i] = '-';
			if (name[i] == ':') name[i] = '-';
		}
		
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.push_back('.');
		name.push_back('t');
		name.push_back('x');
		name.push_back('t');
		
		name = SF + name;
		ofstream fout(name);

		//====================================================
		if (level == 0) return;
		fout << "p " << first->get_name() << " " << first->get_base()->get_number() << "\n";
		fout << "p " << second->get_name() << " " << second->get_base()->get_number() << "\n";

		int x = F->get_x_size();
		int y = F->get_y_size();
		fout << x << " " << y << "\n";
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				fout << F->get_cell(j, i)->get_land_number() ;
				if (j < x - 1) fout << " ";
			}
			fout << "\n";
		}
		fout << F->get_item_count() << "\n";
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (F->get_cell(j, i)->get_item_type() != Non) {
					fout << "i " << i << " " << j << " " << F->get_cell(j, i)->get_item_type() << "\n";
				}
			}
		}
		base* bb;
		unit* uu;

		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (F->get_cell(j, i)->is_base()) {
					bb = F->get_cell(j, i)->get_base();
					fout << "b " << i << " " << j << " " << bb->get_number() <<" "<< bb->get_hp() << "\n";
					fout << bb->how_many_alive() << "\n";
					for (int k = 0; k < 3; k++) {
						uu = bb->get_unit(k);
						if (bb->is_unit_alive(k)) {
							fout << "u " << uu->get_y() << " " << uu->get_x() << " " << uu->get_name() << " " << uu->get_hp() << " " << uu->get_hp_max() << " ";
							fout << uu->get_armor() << " " << uu->get_attack() << " " << uu->get_xp() << " " << uu->get_xp_for_next_level() << " " << uu->get_level() << "\n";
						}
					}
				
				}
			}
		}
		

		//ПРАВИЛА
		fout.close();
	}
	bool load_game() {
		try {
			string fname = "";
			cout << "Enter load-file name:\n";
			cin >> fname;
			fname = "SaveFiles\\" + fname;
			char buff[4];
			char in;
			int num = 0;
			ifstream finn(fname);
			string w = "";
			if (!finn.is_open()) {
				throw except("(game::load_game) File with name \"" + fname + "\" can't be found or opened\n");
			}
			else {

				first = load_player(finn);
				if (first == NULL) {
					throw except("(game::load_game) First player can't be load: input structure corrapted\n");
				}

				second = load_player(finn);
				if (second == NULL) {
					throw except("(game::load_game) Second player can't be load: input structure corrapted\n");
				}

				int w = load_number(finn);
				int h = load_number(finn);
				printf("[%d], [%d]\n\n", w, h);
				if (w <= 0 || h < 0) throw except("(game::load_game) Currupted field-size: w = " + to_string(w) + " h = " + to_string(h) + "\n");

				int** fieldMatrix = new int* [h];
				for (int i = 0; i < h; i++) {
					fieldMatrix[i] = new int[w];
					for (int j = 0; j < w; j++) {
						fieldMatrix[i][j] = load_number(finn);
						printf("%d", fieldMatrix[i][j]);
					}
					printf("\n");
				}

				F = new field(w, h, fieldMatrix);

				int itemCounter = load_number(finn);
				printf("%d\n", itemCounter);

				
				for (int i = 0; i < itemCounter; i++) {
					load_item(finn);
				}

				base* b;

				b = load_base(finn);
				b->delete_unit(0);
				b->delete_unit(1);
				b->delete_unit(2);
				int n = load_number(finn);
				if (n < 0 || n > 3) throw except("(game::load_game) Incorrect units number: " + to_string(n) + "\n");
			

				if (first->get_base()->get_number() == b->get_number()) {
					first->set_base(b);
					F->set_base(b->get_x(), b->get_y(), first->get_base());
					for (int i = 0; i < n; i++) {
						load_unit(finn, first->get_base(), i); //base_number 0
						if (first->get_base()->is_unit_alive(i)) {
							F->get_cell(first->get_base()->get_unit(i)->get_x(), first->get_base()->get_unit(i)->get_y())->set_unit(first->get_base()->get_unit(i));
						}
					}
					first->set_tmp_unit(first->get_base()->is_any_alive());
				}
				else if (second->get_base()->get_number() == b->get_number()) {
					second->set_base(b);
					F->set_base(b->get_x(), b->get_y(), second->get_base());
					for (int i = 0; i < n; i++) {
						load_unit(finn, second->get_base(), i); //base_number 0
						if (second->get_base()->is_unit_alive(i)) {
							F->get_cell(second->get_base()->get_unit(i)->get_x(), second->get_base()->get_unit(i)->get_y())->set_unit(second->get_base()->get_unit(i));
						}
					}
					second->set_tmp_unit(second->get_base()->is_any_alive());
				}

				else throw except("(game::load_game) Loaded base-number: "+to_string(b->get_number())+" doesn't match any players base-numbers: "+to_string(first->get_base()->get_number())+" and "+to_string(second->get_base()->get_number())+"\n");
				
				b = load_base(finn);
				b->delete_unit(0);
				b->delete_unit(1);
				b->delete_unit(2);

				n = load_number(finn);
				if (n < 0 || n > 3) throw except("(game::load_game) Incorrect units number: " + to_string(n) + "\n");


				if (first->get_base()->get_number() == b->get_number()) {
					first->set_base(b);
					F->set_base(b->get_x(), b->get_y(), first->get_base());
					for (int i = 0; i < n; i++) {
						load_unit(finn, first->get_base(), i); //base_number 0
						if (first->get_base()->is_unit_alive(i)) {
							F->get_cell(first->get_base()->get_unit(i)->get_x(), first->get_base()->get_unit(i)->get_y())->set_unit(first->get_base()->get_unit(i));
						}
					}
					first->set_tmp_unit(first->get_base()->is_any_alive());
				}
				else if (second->get_base()->get_number() == b->get_number()) {
					second->set_base(b);
					F->set_base(b->get_x(), b->get_y(), second->get_base());
					for (int i = 0; i < n; i++) {
						load_unit(finn, second->get_base(), i); //base_number 0
						if (second->get_base()->is_unit_alive(i)) {
							F->get_cell(second->get_base()->get_unit(i)->get_x(), second->get_base()->get_unit(i)->get_y())->set_unit(second->get_base()->get_unit(i));
						}
					}
					second->set_tmp_unit(second->get_base()->is_any_alive());


				}
				else throw except("(game::load_game) Loaded base-number: " + to_string(b->get_number()) + " doesn't match any players base-numbers: " + to_string(first->get_base()->get_number()) + " and " + to_string(second->get_base()->get_number()) + "\n");




				finn.close();
				level = 3;
				return true;
			}

		}
		catch (except &ex) {
			cout << "Something goes wrong with loading game!\n  " << ex.what() << "\n";
			level = 1;
			return false;
		}
	}

public:
	game(graphic* e, int leveli) {
		level = leveli;
		in = 1;
		gui = e;
	}
	void training() {
		try {
			F = new field(3, 3);
			first = new player("YOU", 404);
			first->get_base()->delete_unit(1);
			first->get_base()->delete_unit(2);
			first->get_tmp_unit()->set_hp(500);
			first->set_tmp_unit(0);
			F->find_empty(0, 0)->set_unit(first->get_base()->get_unit(0));
			gui->camera(*F, first, false);
			gui->setTextColor(12);
			cout << "THIS IS YOU. FRESH AND CLEAN\n Try to move with 'wasd'\n";
			int x = first->get_tmp_unit()->get_x();
			int y = first->get_tmp_unit()->get_y();
			int steps = 0;
			char iter = 'e';

			while (steps < 5) {
				x = first->get_tmp_unit()->get_x();
				y = first->get_tmp_unit()->get_y();
				iter = _getch();
				if (iter == 's') {
					F->move_unit(x, y, x, y + 1);
					steps++;
				}
				else if (iter == 'w') {
					F->move_unit(x, y, x, y - 1);
					steps++;
				}
				else if (iter == 'a') {
					F->move_unit(x, y, x - 1, y);
					steps++;
				}
				else if (iter == 'd') {
					F->move_unit(x, y, x + 1, y);
					steps++;
				}
			
				gui->camera(*F, first, false);
				cout << "THIS IS YOU. FRESH AND CLEAN\n Try to move with 'wasd'\n";
			}

			field_cell* e = F->find_empty(0, 0);
			first->get_base()->set_coords(e->get_x(), e->get_y());
			F->set_base(e->get_x(), e->get_y(), first->get_base());

			gui->camera(*F, first, false);
			cout << "Great job! Now look: it's yours base, you can create units with it! Press r to make one!\n";
			iter = 'q';
			while (iter != 'r') {
				iter = _getch();
				if (iter == 'r') {
					int nunit = first->get_base()->create_unit();
					if (nunit != -1) {
						e = F->find_empty(first->get_base()->get_x(), first->get_base()->get_y());
						e->set_unit(first->get_base()->get_unit(nunit));
						e->get_unit()->set_hp(500);
					}
				}
				gui->camera(*F, first, false);
				cout << "Great job! Now look: it's yours base, you can create units with it! Press r to make one!\n";
			}
			cout << "Cool! Look this is your bro, you can't attack him (even if you try)\n Now: try to press 1-2-3 to swech between them and walk!\n";
			steps = 0;
			while (steps < 4) {
				x = first->get_tmp_unit()->get_x();
				y = first->get_tmp_unit()->get_y();
				iter = _getch();
				if (iter == '1')  first->set_tmp_unit(0);
				else if (iter == '2')  first->set_tmp_unit(1);
				else if (iter == '3')  first->set_tmp_unit(2);
				else if (iter == 's') {
					F->move_unit(x, y, x, y + 1);
					steps++;
				}
				else if (iter == 'w') {
					F->move_unit(x, y, x, y - 1);
					steps++;
				}
				else if (iter == 'a') {
					F->move_unit(x, y, x - 1, y);
					steps++;
				}
				else if (iter == 'd') {
					F->move_unit(x, y, x + 1, y);
					steps++;
				}

				gui->camera(*F, first, false);
				cout << "Cool! Look this is your bro, you can't attack him (even if you try)\n Now: try to press 1-2-3 to swech between them and walk!\n";
			}
			cout << "Brilliant! Okey, now i'll show you some more info about you and your base!\n Pay attention for landscape!(just walk arounde while i prepare next test for you)\n";
				steps = 0;
			while (steps < 5) {
				x = first->get_tmp_unit()->get_x();
				y = first->get_tmp_unit()->get_y();
				iter = _getch();
				if (iter == '1')  first->set_tmp_unit(0);
				else if (iter == '2')  first->set_tmp_unit(1);
				else if (iter == '3')  first->set_tmp_unit(2);
				else if (iter == 's') {
					F->move_unit(x, y, x, y + 1);
					steps++;
				}
				else if (iter == 'w') {
					F->move_unit(x, y, x, y - 1);
					steps++;
				}
				else if (iter == 'a') {
					F->move_unit(x, y, x - 1, y);
					steps++;
				}
				else if (iter == 'd') {
					F->move_unit(x, y, x + 1, y);
					steps++;
				}

				gui->camera(*F, first);
				cout << "Brilliant! Okey, now i'll show you some more info about you and your base!\n Pay attention for landscape!(just walk arounde while i prepare next test for you)\n";

			}
			int f = 0;
			base* b = new base(-2);
			b->delete_unit(1);
			b->delete_unit(2);
			 e = F->find_empty(0, 0);
			e->set_unit(b->get_unit(0));
			e->get_unit()->set_all(10, 10, 3, 3, 5, 1, 1);


			gui->camera(*F, first);
			cout << "How are you so far? Nice! Let's try something new!\n It wasn't easy, but i found immobilized enemy for you!\n Kill him now, just try to 'walk' in him\n";
			while (!e->is_empty()) {
				x = first->get_tmp_unit()->get_x();
				y = first->get_tmp_unit()->get_y();
				iter = _getch();
				if (iter == '1')  first->set_tmp_unit(0);
				else if (iter == '2')  first->set_tmp_unit(1);
				else if (iter == '3')  first->set_tmp_unit(2);
				else if (iter == 's') {
					F->move_unit(x, y, x, y + 1);
					steps++;
				}
				else if (iter == 'w') {
					F->move_unit(x, y, x, y - 1);
					steps++;
				}
				else if (iter == 'a') {
					F->move_unit(x, y, x - 1, y);
					steps++;
				}
				else if (iter == 'd') {
					F->move_unit(x, y, x + 1, y);
					steps++;
				}
				gui->camera(*F, first);
				cout << "How are you so far? Nice! Let's try something new!\n It wasn't easy, but i found immobilized enemy for you!\n Kill him now, just try to 'walk' in him\n";

			}
			cout << "Wow you are so smart! Now i hope, you can play some real games! See you soon(press any key to exit)\n";
			iter = _getch();
			
			delete first;
			delete F;
			delete b;
			system("cls");
			return;
		}
		catch (except & ex) {
			cout << "Something while training goes wrong!\n" << ex.what() << "\n";
			return;
		}
	
	}
	void game_on() {
		try { 
			bool allright = level_load(); 
			if (!allright) throw - 1;
		}
		catch (int) {
			cout << "Can't start game after loading problems, return to menu\n" << "\n";
			return;
		}
		
		char iter = '1';
		int y = first->get_tmp_unit()->get_y();
		int x = first->get_tmp_unit()->get_x();
		player* tmp = first;
		
		int steps = 0;
		try {
			while (iter != '0') {
				// проблема - русский язык
				if (rul->who_lose(F) != -1) {
					system("cls");
					cout << "player " << rul->who_lose(F) << " lose :(\n\tGame over!\n";
					level_unload();

					return;
				}

				if (tmp->get_tmp_unit() == NULL) {
					system("cls");
					cout << "YOU DEAD!!!\n";
					int f = tmp->is_any_alive();
					if (f == -1) {
						system("cls");
						cout << "player " << rul->who_lose(F) << " lose :(\n\tGame over!\n";
						level_unload();
						return;
					}
					tmp->set_tmp_unit(f);

				}
				x = tmp->get_tmp_unit()->get_x();
				y = tmp->get_tmp_unit()->get_y();
				gui->camera(*F, tmp);

				iter = _getch();
				if (iter == 's') {
					F->move_unit(x, y, x, y + 1);
					steps++;
				}
				else if (iter == 'w') {
					F->move_unit(x, y, x, y - 1);
					steps++;
				}
				else if (iter == 'a') {
					F->move_unit(x, y, x - 1, y);
					steps++;
				}
				else if (iter == 'd') {
					F->move_unit(x, y, x + 1, y);
					steps++;
				}
				else if (iter == 'l') {
					logger::add("=>Player ask to load game\n");
					system("cls");
					cout << "Save current game before loading? Press 1 to save\n";
					iter = _getch();
					if (iter == '1') save_game();
					level_unload();
					level = 3;
					try {
						bool allright = level_load();
						if (!allright) throw - 1;
					}
					catch (int) {
						cout << "Can't start game after loading problems, return to menu\n" << "\n";
						return;
					}
					iter = 'w';
					tmp = first;
					steps = 0;
				}
				else if (iter == '1')  tmp->set_tmp_unit(0);
				else if (iter == '2')  tmp->set_tmp_unit(1);
				else if (iter == '3')  tmp->set_tmp_unit(2);
				else if (iter == 'r') {
					logger::add("=>Player " + to_string(tmp->get_base()->get_number()) + " ask for mor units\n");
					int nunit = tmp->get_base()->create_unit();
					if (nunit != -1) {
						logger::add("=>Player get new unit\n");
						F->find_empty(tmp->get_base()->get_x(), tmp->get_base()->get_y())->set_unit(tmp->get_base()->get_unit(nunit));
					}
					steps++;
				}
				else if (iter == 'c') {
					save_game();
					logger::add("=>Player saved game\n");
				}
				else if (iter == '0') {
					logger::add("=>Player exit game ");
					system("cls");
					cout << "Save current game before exit? Press 1 to save\n";
					iter = _getch();
					if (iter == '1') {
						save_game();
						logger::add(" and save in");
					}
					logger::add("\n");
					level_unload();
					return;
				}
				try {
					if (rul->who_lose(F) != -1) {
						system("cls");
						cout << "player " << rul->who_lose(F) << " lose :(\n\tGame over!\n";
						level_unload();
						return;
					}
				}
				catch (except & ex) {
					cout << "(game::game_on) Something goes wrong with ruls:\n\t" << ex.what() << "\n";
					level_unload();

					return;
				}
				if (tmp->get_tmp_unit() == NULL) {
					system("cls");
					cout << "YOU DEAD!!!\n";
					int f = tmp->is_any_alive();
					if (f == -1) {
						system("cls");
						cout << "player " << rul->who_lose(F) << " lose :(\n\tGame over!\n";
						level_unload();
						return;
					}
					tmp->set_tmp_unit(f);

				}

				if (rul->who_next(steps) == -1) {
					if (tmp == first) tmp = second;
					else tmp = first;
					steps = 0;
				}


			}
		}
		catch (except ex) {
			cout << "(game::game_on) Something goes wrong while playing!\n\t" << ex.what() << "\n";
			level_unload();
			return;
		
		}
	}

};

class menu {
	bool hardcore;
	int level;
	graphic* gui;

public:
	menu() {
		logger::set_name();
		hardcore = false;
		gui = new graphic();
		gui->setTitle();
		level = 1;
	}
	void start() {
		char in = 'q';
		while (in != '0') {
			gui->setTextColor(yellow);
			cout << "Hello, Player! How are you? Here is something you can do:\n ";
			gui->setTextColor(12);
			cout << "Press 1 to start game\n ";
			gui->setTextColor();
			cout << "Press 2 for choosing level or loading game\n ";
			cout << "Press 3 for help\n ";
			cout << "Press 4 for training\n ";
			cout << "Press 5 for choosing hardcore mode!\n ";
			cout << "Press 0 for exit\n ";
			in = _getch();
			switch (in) {
			case '1': {
				logger::add("=>Player starts game!\n");
				if (hardcore) {
					game<ruls2> hard = game<ruls2>(gui, level);
					hard.game_on();
				}
				else {
					game<ruls1> easy = game<ruls1>(gui, level);
					easy.game_on();
				}
				break;
			}
			case '2': {
				in = 'q';

				while (in != '1' && in != '2' && in != '3') {
					system("cls");
					cout << "If you want small level press 1\nif you want big level press 2\nif you want to load game press 3\n";
					in = _getch();
					if (in == '1') level = 1;
					if (in == '2') level = 2;
					if (in == '3') level = 3;
				}
				cout << "Now in menu just choose 'start game' and it will be this level\n";
				logger::add("=>Player choose " + to_string(level) + " level\n");
				break;
			}
			case '3': {
				logger::add("=>Player call help\n");
				gui->help();
				break;
			}
			case '4': {
				logger::add("=>Player start training\n");
				if (hardcore) {
					game<ruls2> hard = game<ruls2>(gui, level);
					hard.training();
					
					return;
				}
				else {
					game<ruls1> easy = game<ruls1>(gui, level);
					easy.training();
					return;
				}
				 
				break;
			}
			case '5': {
				hardcore = true;
				cout << "HARDCOREEE\n";
				logger::add("=>Player choose hardcore mode\n");
				break;
			}
			case '0': {
				logger::add("=>Player exit game\n");
				system("cls");
				cout << "BYE :*\n";
				return;
			}
			default: {
				logger::add("=>Player press " + to_string(in) + " in menu\n");
				system("cls");
				cout << "OOOPS, you press wrong button, try again!\n\n";
			}

			}


		}
	
	
	}



};


int main(){
	menu* everething = new menu();
	everething->start();
	return 0;
}

