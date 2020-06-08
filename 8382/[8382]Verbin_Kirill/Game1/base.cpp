#include "base.h"
Base::Base(int fr) {
	x = 4;
	fraction = fr;
	hp = 500;
	id_array = new int[6];
	respawn_point = 6;
	for (int i = 0; i < 6; i++) {
		id_array[i] = 0;
	}
	if (fraction == 0) {
		id = 0;
		u_id = 1;
		y = 0;
	}
	else {
		id = 100;
		u_id = 101;
		y = 13;
	}
}

HeavyArcher* Base::CreateHeavyArcher(int x, int y) {
	if (this->u_id - this->id < 40 && this->respawn_point > 0) {
		HeavyArcher* tmp = new HeavyArcher();
		tmp->Mapping(x, y, this->u_id);
		for (int i = 0; i < 6; i++) {
			if (this->id_array[i] == 0) {
				this->id_array[i] = tmp->id;
				break;
			}
		}
		this->u_id++;
		this->respawn_point--;
		return tmp;
	}
	else {
		return NULL;
	}
}
HeavyRider* Base::CreateHeavyRider(int x, int y) {
	if (this->u_id - this->id < 40 && this->respawn_point > 0) {
		HeavyRider* tmp = new HeavyRider();
		tmp->Mapping(x, y, this->u_id);
		for (int i = 0; i < 6; i++) {
			if (this->id_array[i] == 0) {
				this->id_array[i] = tmp->id;
				break;
			}
		}
		this->u_id++;
		this->respawn_point--;
		return tmp;
	}
	else {
		return NULL;
	}
 }

HeavySaber* Base::CreateHeavySaber(int x, int y) {
	if (this->u_id - this->id < 40 && this->respawn_point > 0) {
		HeavySaber* tmp = new HeavySaber();
		tmp->Mapping(x, y, this->u_id);
		for (int i = 0; i < 6; i++) {
			if (this->id_array[i] == 0) {
				this->id_array[i] = tmp->id;
				break;
			}
		}
		this->u_id++;
		this->respawn_point--;
		return tmp;
	}
	else {
		return NULL;
	}
}

LightArcher* Base::CreateLightArcher(int x, int y) {
	if (this->u_id - this->id < 40 && this->respawn_point > 0) {
		LightArcher* tmp = new LightArcher();
		tmp->Mapping(x, y, this->u_id);
		for (int i = 0; i < 6; i++) {
			if (this->id_array[i] == 0) {
				this->id_array[i] = tmp->id;
				break;
			}
		}
		this->u_id++;
		this->respawn_point--;
		return tmp;
	}
	else {
		return NULL;
	}
}

LightRider* Base::CreateLightRider(int x, int y) {
	if (this->u_id - this->id < 40 && this->respawn_point > 0) {
		LightRider* tmp = new LightRider();
		tmp->Mapping(x, y, this->u_id);
		for (int i = 0; i < 6; i++) {
			if (this->id_array[i] == 0) {
				this->id_array[i] = tmp->id;
				break;
			}
		}
		this->u_id++;
		this->respawn_point--;
		return tmp;
	}
	else {
		return NULL;
	}
}

LightSaber* Base::CreateLightSaber(int x, int y) {
	if (this->u_id - this->id < 40 && this->respawn_point > 0) {
		LightSaber* tmp = new LightSaber();
		tmp->Mapping(x, y, this->u_id);
		for (int i = 0; i < 6; i++) {
			if (this->id_array[i] == 0) {
				this->id_array[i] = tmp->id;
				break;
			}
		}
		this->u_id++;
		this->respawn_point--;
		return tmp;
	}
	else {
		return NULL;
	}
}

int Base::UnitsCount() {
	int count = 0;
	for (int i = 0; i < 6; i++) {
		if (this->id_array[i] != 0) {
			count++;
		}
	}
	return count;
}
void Base::UnitDeathControl(int* detharr) {
	for (int i = 0; i < 12; i++) {
		if (this->fraction == 0) {
			if (detharr[i] < 100 && detharr[i] > 0) {
				for (int j = 0; j < 6; j++) {
					if (this->id_array[j] == detharr[i]) {
						this->id_array[j] = 0;
						this->respawn_point++;
					}
				}
			}
		} else {
			if (detharr[i] > 100) {
				for (int j = 0; j < 6; j++) {
					if (this->id_array[j] == detharr[i]) {
						this->id_array[j] = 0;
						this->respawn_point++;
					}
				}
			}
		}
	}
}
void Base::GetDamage(int d) {
	this->hp -= d;
}