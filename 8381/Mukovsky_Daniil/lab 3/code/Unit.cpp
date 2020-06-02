#include "Unit.h"

int Unit::count = 0;


Unit::Unit() {
	name = "Abstract Unit";
	shortName = "A_u";
	canMove = true;
	alive = true;
	number = count;
	count++;

}

WarriorTank::WarriorTank() {
	name = "Warrior Tank";
	shortName = "W_t";
	attributes.setAll(300,100,40,1);

}

WarriorDamager::WarriorDamager() {
	name = "Warrior Damager";
	shortName = "W_d";
	attributes.setAll(220, 70, 60, 1);

}

ShooterTank::ShooterTank() {
	name = "Shooter Tank";
	shortName = "S_t";
	attributes.setAll(165, 60, 60, 2);


}

ShooterDamager::ShooterDamager() {
	name = "Shooter Damager";
	shortName = "H_d";
	attributes.setAll(150, 50, 150, 2);

}

BufferTank::BufferTank() {
	name = "Buffer Tank";
	shortName = "B_t";
	attributes.setAll(250, 60, 35, 1);

}


BufferDamager::BufferDamager() {
	name = "Buffer Damager";
	shortName = "B_d";
	attributes.setAll(150, 50, 70, 2);
	
}


std::string Unit::getShortName() {
	return shortName;
}
std::string Unit::getName() {
	return name;
}

std::string WarriorTank::info() {
	std::string player;
	curPlayer ? player = "1" : player = "2";
	std::string out = "Info class: Warrior, player: " + player + " specialization: Tank, " + attributes.getInfoAttributes();
	return out;
}

std::string WarriorDamager::info() {
	std::string player;
	curPlayer ? player = "1" : player = "2";
	std::string out = "Info class: Warrior, player: " + player + " specialization: Damager, " + attributes.getInfoAttributes();
	return out;
}

std::string ShooterTank::info() {
	std::string player;
	curPlayer ? player = "1" : player = "2";
	std::string out = "Info class: Shooter, player: " + player + " specialization: Tank, " + attributes.getInfoAttributes();
	return out;
}

std::string ShooterDamager::info() {
	std::string player;
	curPlayer ? player = "1": player = "2";
	std::string out = "Info class: Shooter, player: " + player + " specialization: Damager, " + attributes.getInfoAttributes();
	return out;
}

std::string BufferTank::info() {
	std::string player;
	curPlayer ? player = "1" : player = "2";
	std::string out = "Info class: Buffer, player: " + player + " specialization: Tank, " + attributes.getInfoAttributes();
	return out;
}
std::string BufferDamager::info() {
	std::string player;
	curPlayer ? player = "1" : player = "2";
	std::string out = "Info class: Buffer, player: " + player + " specialization: Damager, " + attributes.getInfoAttributes();
	return out;
}

