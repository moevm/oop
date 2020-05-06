#include "Field.h"
#include "Unit.h"
#include "Adapter.h"
#include <sstream>

void Unit::setSerialNumber(int num)
{
	properties.serialNumber = num;
}
void Unit::setNumber(int new_num)
{
	if (new_num > max_number)
	{
		return;
	}
	if (new_num <= 0) clearUnit(); 
	else
	{
		if (properties.number != new_num && properties.number != 0)
		{
			properties.number = new_num;
			adapter->number_Unit(this);
		}
		properties.number = new_num;
		
	}
	
	
}
void Unit::setTeam(int t)
{
	properties.team = t;
}
void Unit::setBase(Base * Base)
{
	base = Base;
}
void Unit::setField(Field * Field)
{
	field = Field;
}
void Unit::setCords(Point p)
{
	place = p;
}
void Unit::setAdapter(Adapter * a)
{
	adapter = a;
}

void Unit::clearUnit()
{
	properties.number = 0;
	if (properties.serialNumber > 0)
		//cout << "Unit" << properties.serialNumber << ": DEAD\n";
		adapter->dead_Unit(to_string(properties.serialNumber));
	properties.serialNumber = 0;
	army = "nan";
	s_class = "nan";
	notify();
}
void Unit::enableAttack(bool t)
{
	properties.enableAttack = t;
}

int Unit::getTeam() const
{
	return properties.team;
}
Base * Unit::getBase() const
{
	return base;
}
sf::Sprite Unit::getSprite(float frame) 
{
	return(TextureFactory ::getTexture(this, frame)->sprite);
}
Point Unit::getCords() 
{
	return place;
}
int Unit::getNumber()
{
	return  properties.number;
}
int Unit::getSerialNumber() const
{
	return properties.serialNumber;
}
int Unit::getHealth() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->health);
}
int Unit::getAttack() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->attack);
}
int Unit::getArmor() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->armor);
}
int Unit::getRange() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->range);
}
int Unit::getStamina() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->stamina);
}
string Unit::getSubclass()
{
	return s_class;
}
string Unit::getClass() const
{
	return army;
}
bool Unit::isEmpty() const
{
	return(getClass() == "nan");
}

void Unit::debuffStamina(float t)
{
	if (properties.debuffStamina != t)
		//cout << "Unit" + to_string(properties.serialNumber) + ": current stamina - " + to_string(t * getStamina()) << endl;
		adapter->stamina_Unit(this);
	properties.debuffStamina = t;
	
}
void Unit::debuffAttack(float t)
{
	if(properties.debuffAttack != t)
		//cout << "Unit" + to_string(properties.serialNumber) + ": current attack - " + to_string(t * getAttack()) << endl;
	adapter->attackRate_Unit(this);
	properties.debuffAttack = t;
	
}
void Unit::debuffArmor(float t)
{
	if (properties.debuffArmor != t)
		//cout << "Unit" + to_string(properties.serialNumber) + ": current armor - " + to_string(t * getArmor()) << endl;
		adapter->armor_Unit(this);
	properties.debuffArmor = t;
	
}
float Unit::debuffArmor()
{
	return properties.debuffArmor;
}
float Unit::debuffStamina()
{
	return properties.debuffStamina;
}
float Unit::debuffAttack()
{
	return properties.debuffAttack;
}
/*
void Unit ::interact(Unit * enemy)
{
	attack(enemy->getCords().x, enemy->getCords().y);
}*/
bool Unit::attack(int x, int y)
{
	int distance = int(sqrt((place.x - x) * (place.x - x) + (place.y - y) * (place.y - y)));
	if (getRange() < distance)
	{
		//cout <<"Unit " << properties.serialNumber << ": Target is not in range\n";
		adapter->failAttack_Unit(this);
		return false;
	}
	if (!properties.enableAttack)
	{
		//cout << "Unit " << properties.serialNumber << ": I can't attack\n";
		adapter->failAttack_Unit(this);
		return false;
	}
	Unit * enemy = field->getUnit(x, y);
	if (enemy->getClass() == "nan")
		return false;
	int n = enemy->getNumber();
	enemy->setNumber(int((enemy->getHealth() * n - getAttack() * properties.debuffAttack * getNumber()) / enemy->getHealth())); 
	enemy->isAttacked = 10;
	isAttack = 10;
	return true;
}
bool Unit::go(string dir)
{
	if (dir == "left")
		if (field->moveUnit(place.x, place.y, place.x - 1, place.y))
		{
			place.x--;	return true;
		}
	if (dir == "right")
		if (field->moveUnit(place.x, place.y, place.x + 1, place.y))
		{
			place.x++; return true;
		}
	if (dir == "up")
		if (field->moveUnit(place.x, place.y, place.x, place.y - 1))
		{
			place.y--; return true;
		}
	if (dir == "down")
		if (field->moveUnit(place.x, place.y, place.x, place.y + 1))
		{
			place.y++; return true;
		}
	//cout << "Unit " << properties.serialNumber << ": I can't go there\n";
	adapter->failMove_Unit(this);
	return false;
}
/*
bool Unit::volunteer()
{
	Component::traverse();
	//if (rand() * 100 % 6 != 0)
		Component::volunteer();
}*/

void Subject::addObs(Observer * observer) {
	observers.push_back(observer);
}
void Subject::delObs(Observer* observer) {
	std::vector<Observer*>::iterator iter = observers.begin();
	while (iter != observers.end()) {
		if (*iter = observer) {
			observers.erase(iter);
			return;
		}
	}

}
void Subject::notify() {
	for (Observer* element : observers)
		element->update(this);
}
/*
Mediator :: Mediator(Unit * Uni1 , Unit * Unit2 , Land * Land, Netral * Netral)
{
	unit1 = Uni1;
	unit2 = Unit2;
	land = Land;
	netral = Netral;
}
void Mediator :: interact(Object * object)
{
	if (object == unit1)
	{
		object->interact(unit2);
	}
	if (object == land)
	{
		object->interact(unit1);
	}
	if (object == netral)
	{
		object->interact(unit1);
	}
}
*/

bool AttackMediator :: interact(Unit * unit)
{
	if (unit == unit1)
		return(unit1->attack(unit2->getCords().x, unit2->getCords().y));
	if (unit == unit2)
		return(unit2->attack(unit1->getCords().x, unit1->getCords().y));
	return false;
}
AttackMediator :: AttackMediator(Unit * u1, Unit * u2)
{
	unit1 = u1;
	unit2 = u2;
	u1->mediator = this;
	u2->mediator = this;

}

FlyWeight::FlyWeight(string Name) : name(Name)
{
	if (name == "Berserks")
	{
		health = 100;
		stamina = 8;
		attack = 150;
		armor = 50;
		range = 1;
	}
	if (name == "Spearmen")
	{
		health = 100;
		stamina = 6;
		attack = 100;
		armor = 100;
		range = 2;
	}
	if (name == "Hunters")
	{
		health = 50;
		stamina = 4;
		attack = 200;
		armor = 20;
		range = 6;
	}
	if (name == "LongShooters")
	{
		health = 50;
		stamina = 2;
		attack = 100;
		armor = 60;
		range = 10;
	}
	if (name == "Ulans")
	{
		health = 150;
		stamina = 10;
		attack = 100;
		armor = 100;
		range = 1;
	}
	if (name == "Cuirassiers")
	{
		health = 150;
		stamina = 8;
		attack = 150;
		armor = 200;
		range = 1;
	}
	if (name == "nan")
	{
		health = 0;
		stamina = 0;
		attack = 0;
		armor = 0;
		range = 0;
	}
}
int FlyweightFactory::num = 0;
FlyWeight * FlyweightFactory::flyweights[];
FlyWeight * FlyweightFactory::getFlyWeight(string name)
{
	for (int i = 0; i < num; i++)
		if (name == flyweights[i]->getName())
			return flyweights[i];
	flyweights[num] = new FlyWeight(name);
	return flyweights[num++];
}


TexturePack::TexturePack(string Name, int Team, int Frame) : name(Name), team(Team), frame(Frame)
{
	if (name == "Berserks" && team == 0)
	{
		tileSet.loadFromFile("WIB.png");
		sprite = sf::Sprite(tileSet);
		if(frame > 0)
			sprite.setTextureRect(sf::IntRect(45 + 60 * int(frame), 225, -45, 70));
		else
			sprite.setTextureRect(sf::IntRect(5 + 40, 5, -40, 70));
		
	}
	if (name == "Berserks" && team == 1)
	{
		tileSet.loadFromFile("FIB.png");
		sprite = sf::Sprite(tileSet);
		if (frame > 0)
			sprite.setTextureRect(sf::IntRect( 60 * int(frame), 225, 45 , 70));
		else
			sprite.setTextureRect(sf::IntRect(5 , 5, 40, 70));
	}
	if (name == "Spearmen" && team == 0)
	{
		tileSet.loadFromFile("WIS.png");
		sprite = sf::Sprite(tileSet);
		if (frame > 0)
			sprite.setTextureRect(sf::IntRect(145 + int(frame)*80 + 80, 354, -80, 40));
		else
			sprite.setTextureRect(sf::IntRect(10 + 50, 20, -50, 50));
	}
	if (name == "Spearmen" && team == 1)
	{
		tileSet.loadFromFile("FIS.png");
		sprite = sf::Sprite(tileSet);
		if (frame > 0)
			sprite.setTextureRect(sf::IntRect(90 + 80 * int(frame), 55, -80, 40));
		else
			sprite.setTextureRect(sf::IntRect(10 + 50, 0, -50, 50));
	}
	if (name == "Cuirassiers" && team == 0)
	{
		tileSet.loadFromFile("WCC.png");
		sprite = sf::Sprite(tileSet);
		if (frame > 0)
			sprite.setTextureRect(sf::IntRect(155 * int(frame)+50, 133, -50, 60));
		else
			sprite.setTextureRect(sf::IntRect(2 + 50, 18, -50, 60));
	}
	if (name == "Cuirassiers" && team == 1)
	{
		tileSet.loadFromFile("FCC.png");
		sprite = sf::Sprite(tileSet);
		if (frame > 0)
			sprite.setTextureRect(sf::IntRect(155 * int(frame), 133, 50, 60));
		else
			sprite.setTextureRect(sf::IntRect(10 , 18, 45, 60));
	}
	if (name == "LongShooters" && team == 0)
	{
		tileSet.loadFromFile("WAL.png");
		sprite = sf::Sprite(tileSet);
		if (frame > 0)
			sprite.setTextureRect(sf::IntRect(0 + int(frame) * 40, 50, -40, 40));
		else
			sprite.setTextureRect(sf::IntRect(0 + 30, 0, -30, 40));
	}
	if (name == "LongShooters" && team == 1)
	{
		tileSet.loadFromFile("FAL.png");
		sprite = sf::Sprite(tileSet);
		if (frame > 0)
			sprite.setTextureRect(sf::IntRect(95 + int(frame) * 30, 53, 30, 40));
		else
			sprite.setTextureRect(sf::IntRect(10, 0, 30, 40));
	}

	if (name == "Trap")
	{
		tileSet.loadFromFile("netral.png");
		sprite = sf::Sprite(tileSet);
		sprite.setTextureRect(sf::IntRect(243, 210, 60, 30));
		sprite.setScale(0.8f, 1.0f);
	}
	if (name == "Rune")
	{
		tileSet.loadFromFile("netral.png");
		sprite = sf::Sprite(tileSet);
		sprite.setTextureRect(sf::IntRect(250, 155, 50, 50));
	}
	if (name == "Curse")
	{
		tileSet.loadFromFile("netral.png");
		sprite = sf::Sprite(tileSet);
		sprite.setTextureRect(sf::IntRect(335, 115, 50, 60));
	}
	if (name == "Gold")
	{
		tileSet.loadFromFile("netral.png");
		sprite = sf::Sprite(tileSet);
		sprite.setTextureRect(sf::IntRect(225, 100, 80, 30));
		sprite.setScale(0.6f, 1.0f);
	}

	if (name == "Swamp")
	{
		tileSet.loadFromFile("swamp.png");
		sprite = sf::Sprite(tileSet);
		sprite.setScale(0.555f, 0.777f);
	}
	if (name == "River")
	{
		tileSet.loadFromFile("river.png");
		sprite = sf::Sprite(tileSet);
		sprite.setScale(0.357f, 0.666f);
	}
	if (name == "Forest")
	{
		tileSet.loadFromFile("forest.png");
		sprite = sf::Sprite(tileSet);
		sprite.setScale(0.211f, 0.530f);
	}

}
int TextureFactory::num = 0;
TexturePack * TextureFactory::textures[];
TexturePack * TextureFactory::getTexture(Unit * unit, float frame)
{
	for (int i = 0; i < num; i++)
		if (unit->getSubclass() == textures[i]->getName() && unit->getTeam() == textures[i]->getTeam() && int(frame) == textures[i]->getFrame())
			return textures[i];
	textures[num] = new TexturePack(unit->getSubclass(), unit->getTeam(), int(frame));
	return textures[num++];
}
TexturePack * TextureFactory::getTexture(Netral * netral)
{
	for (int i = 0; i < num; i++)
		if (netral->sprite == textures[i]->getName())
			return textures[i];
	textures[num] = new TexturePack(netral->sprite, 0, 0);
	return textures[num++];
}
TexturePack * TextureFactory::getTexture(Land * land)
{
	for (int i = 0; i < num; i++)
		if (land->sprite == textures[i]->getName())
			return textures[i];
	textures[num] = new TexturePack(land->sprite, 0, 0);
	return textures[num++];
}
