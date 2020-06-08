#include "army.h"


HeavyRider::HeavyRider() {
	hp = 50;
	dp = 10;
}

int HeavyRider::Move(int x, int y) {
	if (this->x + x < 7 && this->x + x > 0 && this->y + y < 14 && this->y + y > 0) {
		if (abs(x) + abs(y) <= 4) {
			this->x += x;
			this->y += y;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	return 1;
}

int HeavyRider::Attack(int** map, int at) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			if (map[i][j] == at && (abs(this->x - i) + abs(this->y) - i == 1)) {
				return this->dp;
			}
		}
	}
	return 0;
}

void HeavyRider::GetDamage(int d) {
	this->hp -= d;
}

void HeavyRider::Mapping(int x, int y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}

HeavyArcher::HeavyArcher() {
	hp = 30;
	dp = 5;
}

int HeavyArcher::Move(int x, int y) {
	if (this->x + x < 7 && this->x + x > 0 && this->y + y < 14 && this->y + y > 0) {
		if (abs(x) + abs(y) <= 2) {
			this->x += x;
			this->y += y;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	return 1;
}

int HeavyArcher::Attack(int** map, int at) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			if (map[i][j] == at && (abs(this->x - i) + abs(this->y) - i <= 4)) {
				return this->dp;
			}
		}
	}
	return 0;
}

void HeavyArcher::GetDamage(int d) {
	this->hp -= d;
}

void HeavyArcher::Mapping(int x, int y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}

HeavySaber::HeavySaber() {
	hp = 40;
	dp = 7;

}

int HeavySaber::Move(int x, int y) {
	if (this->x + x < 7 && this->x + x > 0 && this->y + y < 14 && this->y + y > 0) {
		if (abs(x) + abs(y) <= 2) {
			this->x += x;
			this->y += y;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	return 1;
}

int HeavySaber::Attack(int** map, int at) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			if (map[i][j] == at && (abs(this->x - i) + abs(this->y) - i == 1)) {
				return this->dp;
			}
		}
	}
	return 0;
}

void HeavySaber::GetDamage(int d) {
	this->hp -= d;
}

void HeavySaber::Mapping(int x, int y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}

LightRider::LightRider() {
	hp = 35;
	dp = 10;

}

int LightRider::Move(int x, int y) {
	if (this->x + x < 7 && this->x + x > 0 && this->y + y < 14 && this->y + y > 0) {
		if (abs(x) + abs(y) <= 5) {
			this->x += x;
			this->y += y;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	return 1;
}

int LightRider::Attack(int** map, int at) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			if (map[i][j] == at && (abs(this->x - i) + abs(this->y) - i == 1)) {
				return this->dp;
			}
		}
	}
	return 0;
}

void LightRider::GetDamage(int d) {
	this->hp -= d;
}

void LightRider::Mapping(int x, int y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}

LightArcher::LightArcher() {
	hp = 15;
	dp = 5;

}

int LightArcher::Move(int x, int y) {
	if (this->x + x < 7 && this->x + x > 0 && this->y + y < 14 && this->y + y > 0) {
		if (abs(x) + abs(y) <= 3) {
			this->x += x;
			this->y += y;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	return 1;
}

int LightArcher::Attack(int** map, int at) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			if (map[i][j] == at && (abs(this->x - i) + abs(this->y) - i <= 5)) {
				return this->dp;
			}
		}
	}
	return 0;
}

void LightArcher::GetDamage(int d) {
	this->hp -= d;
}

void LightArcher::Mapping(int x, int y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}

LightSaber::LightSaber() {
	hp = 25;
	dp = 7;
}

int LightSaber::Move(int x, int y) {
	if (this->x + x < 7 && this->x + x > 0 && this->y + y < 14 && this->y + y > 0) {
		if (abs(x) + abs(y) <= 3) {
			this->x += x;
			this->y += y;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	return 1;
}

int LightSaber::Attack(int** map, int at) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			if (map[i][j] == at && (abs(this->x - i) + abs(this->y) - i == 1)) {
				return this->dp;
			}
		}
	}
	return 0;
}

void LightSaber::GetDamage(int d) {
	this->hp -= d;
}

void LightSaber::Mapping(int x, int y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}