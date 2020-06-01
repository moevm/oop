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
	attributes.setAll(300,100,40,0);

}

WarriorDamager::WarriorDamager() {
	name = "Warrior Damager";
	shortName = "W_d";
	attributes.setAll(220, 70, 60, 0);

}

ShooterTank::ShooterTank() {
	name = "Shooter Tank";
	shortName = "S_t";
	attributes.setAll(165, 60, 60, 1);


}

ShooterDamager::ShooterDamager() {
	name = "Shooter Damager";
	shortName = "H_d";
	attributes.setAll(150, 50, 150, 3);

}

BufferTank::BufferTank() {
	name = "Buffer Tank";
	shortName = "B_t";
	attributes.setAll(250, 60, 35, 0);

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
	std::string out = "Info class: Warrior, specialization: Tank, " + attributes.getInfoAttributes();
	return out;
}

std::string WarriorDamager::info() {
	std::string out = "Info class: Warrior, specialization: Damager, "  + attributes.getInfoAttributes();
	return out;
}

std::string ShooterTank::info() {
	std::string out = "Info class: Shooter, specialization: Tank, "+attributes.getInfoAttributes();
	return out;
}

std::string ShooterDamager::info() {
	std::string out = "Info class: Shooter, specialization: Damager, "+attributes.getInfoAttributes();
	return out;
}

std::string BufferTank::info() {
	std::string out = "Info class: Buffer, specialization: Tank, " + attributes.getInfoAttributes();
	return out;
}
std::string BufferDamager::info() {
	std::string out = "Info class: Buffer, specialization: Damager, " + attributes.getInfoAttributes();
	return out;
}

