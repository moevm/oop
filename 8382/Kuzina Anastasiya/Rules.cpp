#include "Rules.h"


//basic one
int ruls1::who_lose(field* F) {
	bool is_no_base = true;
	for (int i = 0; i < F->get_y_size(); i++) {
		for (int j = 0; j < F->get_x_size(); j++) {
			if (F->get_cell(j, i)->is_base()) {
				is_no_base = false;
				if (F->get_cell(j, i)->get_base()->get_hp() <= 0) return F->get_cell(j, i)->get_base()->get_number();
			
			}
		
		}
	
	}
	if (is_no_base) throw exception("(ruls1::who_lose) There is no bases on the field!\n");
	return -1;

}
int ruls1::who_next(int i) {
	if (i > 4) return -1;
	return 1;

}
int ruls1::starts(field* F) {
	return 1;

}



int ruls2::who_lose(field* F) {
	bool is_no_base = true;
	for (int i = 0; i < F->get_y_size(); i++) {
		for (int j = 0; j < F->get_x_size(); j++) {
			if (F->get_cell(j, i)->is_base()) {
				is_no_base = false;
				if (F->get_cell(j, i)->get_base()->is_any_alive() == -1) return F->get_cell(j, i)->get_base()->get_number();

			}

		}

	}
	if (is_no_base) throw exception("(ruls2::who_lose) There is no bases on the field!\n");
	return -1;

}
int ruls2::who_next(int i) {
	if (i > 2) return -1;
	return 1;

}
int ruls2::starts(field* F) {
	bool is_no_base = true;
	for (int i = 0; i < F->get_y_size(); i++) {
		for (int j = 0; j < F->get_x_size(); j++) {
			if (F->get_cell(j, i)->is_base()) {
				is_no_base = false;
				 F->get_cell(j, i)->get_base()->set_hp(0);

			}

		}

	}
	if (is_no_base) throw except("(ruls2::starts)There is no bases on the field!\n");
	return -1;


}

