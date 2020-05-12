#include "Snapshot.h"
#include <sstream>
#include "Field.h"
#include "Adapter.h"
#include "Base.h"

Snapshot::Snapshot(Field* field, string mod) : field(field){
	if (mod == "save")
	{
		fileWrite = new Fwrite("save.txt");
		save();
		delete fileWrite;
	}
	if (mod == "load")
	{
		fileRead = new Fread("save.txt");
		load();
		delete fileRead;
	}
		
}



Snapshot::~Snapshot() 
{
	delete fileWrite;
	delete fileRead;
}
void Snapshot::save()
{
	std::ostringstream out;
	out << field->width << " " << field->height << endl;
	out << field->getWater()->getGold() << " " << field->getWater()->getHealth() << endl;
	out << field->getFire()->getGold() << " " << field->getFire()->getHealth() << endl;
	FieldIterator iter = field->begin();
	while (iter != field->end()) {
		out << iter.operator*().unit->getTeam() << " ";
		out << iter.operator*().unit->getClass() << " ";
		out << iter.operator*().unit->getSubclass() << " ";
		out << iter.operator*().unit->getSerialNumber() << " ";
		out << iter.operator*().unit->getNumber() << " ";
		out << iter.operator*().unit->debuffArmor() << " ";
		out << iter.operator*().unit->debuffAttack() << " ";
		out << iter.operator*().unit->debuffStamina() << " ";
		out << iter.operator*().land->sprite << " ";
		out << iter.operator*().netral->sprite << " ";
		out << endl;
		iter++;
	}
	fileWrite->write(out.str());
}
void Snapshot::load()
{
	std::stringstream stream = fileRead->read();
	

	int reserveNumber1 = 0, reserveNumber2 = 0;
	int reserveSerial1, reserveSerial2;
	string reserveClass1, reserveClass2;

	Adapter * adapter = new Adapter();
	stream >> x >> y;
	if (stream.fail())
	{
		adapter->loadFailField();
		return;
	}

	stream >> gold1 >> health1;
	stream >> gold2 >> health2;
	if (health1 < 0 || health2 < 0 || stream.fail())
	{
		adapter->loadFailBase();
		return;
	}

	Field * newField = new Field(x, y, adapter);
	*field = *newField;
	
	base[0] = field->getWater();
	base[1] = field->getFire();
	base[0]->setGold(gold1); base[0]->setHealth(health1);
	base[1]->setGold(gold2); base[1]->setHealth(health2);
	base[0]->army = new CompositeUnit();
	base[1]->army = new CompositeUnit();
	base[0]->SquadsNumber = base[1]->SquadsNumber = 0;
	
	FieldIterator iter = field->begin();
	while (iter != field->end()) {
		//Unit * unit;
		stream >> team >> unitClass >> unitSub >> serial >> number >> armor >> attack >> stamina >> landSprite >> netralSprite;

		if (landSprite == "Meadow")
			iter.operator*().land = new MeadowProxy();
		else if (landSprite == "River")
			iter.operator*().land = new RiverProxy();
		else if (landSprite == "Swamp")
			iter.operator*().land = new SwampProxy();
		else if (landSprite == "Forest")
			iter.operator*().land = new ForestProxy();
		else
		{
			adapter->loadFailLand();
			return;
		}

		if (netralSprite == "Rune")
			iter.operator*().netral = new Rune();
		else if (netralSprite == "Curse")
			iter.operator*().netral = new Curse();
		else if (netralSprite == "Trap")
			iter.operator*().netral = new Trap();
		else if (netralSprite == "Gold")
			iter.operator*().netral = new Gold();
		else if (netralSprite == "nan")
			iter.operator*().netral = new EmptyObject();
		else
		{
			adapter->loadFailNetral();
			return;
		}


		if(team != 0 && team != 1)
		{
			adapter->loadFailTeam();
			return;
		}
		if (number < 0)
		{
			adapter->loadFailNumber();
			return;
		}

		if ((base[team]->spawnSpot.x == w) && (base[team]->spawnSpot.y == h) && unitSub != "nan")
		{
			if (team == 0)
			{
				reserveNumber1 = number;
				reserveClass1 = unitSub;
				reserveSerial1 = serial;
			}
			else
			{
				reserveNumber2 = number;
				reserveClass2 = unitSub;
				reserveSerial2 = serial;
			}
			h++;
			if (h == y)
			{
				w++; h = 0;
			}
			iter++;
			continue;
		}

		if (unitSub != "nan")
			loadUnit(unitSub, number, team, serial, Point(w,h));
		h++;
		if (h == y)
		{
			w++; h = 0;
		}
		iter++;
	}

	if (reserveNumber1)
	{
		loadUnit(reserveClass1, reserveNumber1, 0, reserveSerial1, base[0]->spawnSpot);
	}

	if (reserveNumber2)
	{
		loadUnit(reserveClass2, reserveNumber2, 1, reserveSerial2, base[1]->spawnSpot);
	}

	for (int i = 0; i < base[0]->SquadsNumber; i++)
	{
		cout << base[0]->army->units[i]->getCords().x << " " << base[0]->army->units[i]->getCords().y << endl;
	}


}

void Snapshot::loadUnit(string unitSub, int number, int team, int serial, Point dir)
{
	if (unitSub == "Berserks")
		base[team]->createBerserks(number);
	else if (unitSub == "Spearmen")
		base[team]->createSpearmen(number);
	else if (unitSub == "LongShooters")
		base[team]->createLongShooters(number);
	else if (unitSub == "Hunters")
		base[team]->createHunters(number);
	else if (unitSub == "Ulans")
		base[team]->createUlans(number);
	else if (unitSub == "Cuirassiers")
		base[team]->createCuirassiers(number);
	else
	{
		adapter->loadFailClass();
		return;
	}

	Unit * unit = field->getUnit(base[team]->spawnSpot.x, base[team]->spawnSpot.y);
	field->moveUnit(base[team]->spawnSpot.x, base[team]->spawnSpot.y, dir.x, dir.y);
	unit->setSerialNumber(serial);
	//unit->setField(field);
	//unit->setBase(base[team]);
	unit->setCords(dir);
	//unit->addObs(base[team]);
	base[team]->update();

}