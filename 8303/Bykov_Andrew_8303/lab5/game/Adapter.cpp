#include <sstream>
#include "Adapter.h"
#include "Unit.h"
#include "Field.h"
#include "Base.h"


Adapter::Adapter(bool writeAble, bool fileWriteAble) : writeAble(writeAble), fileWriteAble(fileWriteAble) {}

std::ostream& operator<< (std::ostream &out, const Unit& unit)
{
	out << "Unit " << unit.getSerialNumber() << ": health - " << unit.getHealth() << ",  attack - " << unit.getAttack() << ", armor - " << unit.getArmor();
	return out;
}
std::ostream& operator<< (std::ostream &out, const Base& base)
{
	out << "Base " << base.getTeam() << ": health - " << base.getHealth() << ", gold - " << base.getGold();
	return out;
}
std::ostream& operator<< (std::ostream &out, const Field& field)
{
	out << ",  Width - " << field.width << ",  Height - " << field.height;
	return out;
}

void Adapter::create_Unit(Unit* unit) {
	std::ostringstream status;
	status << "Create unit  " << *unit;
	print(status.str(), writeAble, fileWriteAble);
}
void Adapter::createBase(Base* base) {
	std::ostringstream status;
	status << "Create " << *base;
	print(status.str(), writeAble, fileWriteAble);
}
void Adapter::createField(Field* field) {
	std::ostringstream status;
	status << "Create field" << *field;
	print(status.str(), writeAble, fileWriteAble);
}

void Adapter::dead_Unit(string unit) {
	print("Unit " + unit + " has been killed", writeAble, fileWriteAble);
}
void Adapter::attacked_Unit(string unit) {
	print("Unit " + unit + " has been attacked", writeAble, fileWriteAble);
}
void Adapter::move_Unit(string unit, string dir) {
	print("Unit " + unit + " moved " + dir, writeAble, fileWriteAble);
}
void Adapter::attack_Unit(string unit, string target) {
	print("Unit " + unit + " attacked unit " + target, writeAble, fileWriteAble);
}
void Adapter::failMove_Unit(Unit * unit) {
	print("Unit " + to_string(unit->getSerialNumber()) + ": fail to move", writeAble, fileWriteAble);
}
void Adapter::failAttack_Unit(Unit * unit) {
	print("Unit " + to_string(unit->getSerialNumber()) + ": fail to attack", writeAble, fileWriteAble);
}
void Adapter::stamina_Unit(Unit * unit) {
	print("Unit " + to_string(unit->getSerialNumber()) + ": current stamina - " + to_string(unit->getStamina()), writeAble, fileWriteAble);
}
void Adapter::armor_Unit(Unit * unit) {
	print("Unit " + to_string(unit->getSerialNumber()) + ": current armor - " + to_string(unit->getArmor()), writeAble, fileWriteAble);
}
void Adapter::attackRate_Unit(Unit * unit) {
	print("Unit " + to_string(unit->getSerialNumber()) + ": current attack - " + to_string(unit->getAttack()), writeAble, fileWriteAble);
}
void Adapter::number_Unit(Unit * unit) {
	print("Unit " + to_string(unit->getSerialNumber()) + ": current number - " + to_string(unit->getNumber()), writeAble, fileWriteAble);
}
void Adapter::interact_Unit(Unit * unit, string object) {
	print("Unit " + to_string(unit->getSerialNumber()) + ": intercat with " + object, writeAble, fileWriteAble);
}

void Adapter::move_Player(string dir)
{
	print("Player Command - Move " + dir, writeAble, fileWriteAble);
}
void Adapter::create_Player(string unit)
{
	print("Player Command - Create " + unit, writeAble, fileWriteAble);
}
void Adapter::attack_Player(string target)
{
	print("Player Command - Attack target " + target, writeAble, fileWriteAble);
}
void Adapter::switch_Player()
{
	print("Player Command - Switch Player", writeAble, fileWriteAble);
}

void Adapter::createUnit_Base(Base * base)
{
	print("Base " + base->getTeam() + ": unit created", writeAble, fileWriteAble);
}
void Adapter::failCreateUnit_Base(Base * base)
{
	print("Base " + base->getTeam() + ": creation failed", writeAble, fileWriteAble);
}
void Adapter::gold_Base(Base * base)
{
	print("Base " + base->getTeam() + ": current gold - " + to_string(base->getGold()), writeAble, fileWriteAble);
}
void Adapter::overlimit_Base(Base * base)
{
	print("Base " + base->getTeam() + ": units overlimit", writeAble, fileWriteAble);
}

void Adapter::switchLog(std::string mod) {
	print("Switch logger mode to " + mod, writeAble, fileWriteAble);
}

void Adapter::gameSaved()
{
	print("Game Saved", writeAble, fileWriteAble);
}
void Adapter::gameLoad()
{
	print("Game Load", writeAble, fileWriteAble);
}

void Adapter::loadFailClass()
{
	print("Fail to Load: Class does not exist", writeAble, fileWriteAble);
}
void Adapter::loadFailBase()
{
	print("Fail to Load: Incorrect base properties", writeAble, fileWriteAble);
}
void Adapter::loadFailField()
{
	print("Fail to Load: Incorrect field properties", writeAble, fileWriteAble);
}
void Adapter::loadFailNumber()
{
	print("Fail to Load: Incorrect unit number", writeAble, fileWriteAble);
}
void Adapter::loadFailTeam()
{
	print("Fail to Load: Incorrect team", writeAble, fileWriteAble);
}
void Adapter::loadFailLand()
{
	print("Fail to Load: Land does not exist", writeAble, fileWriteAble);
}
void Adapter::loadFailNetral()
{
	print("Fail to Load: Object does not exist", writeAble, fileWriteAble);
}