#include "Flyweight.h"


FlyweightFactory::FlyweightFactory(std::initializer_list<SharedUnit> share_units) //чтобы заранее задать легковесы при инициализации приложени€
{
	for (const SharedUnit& ss : share_units)
	{
		this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
	}
}

// ¬озвращает существующий Ћегковес с заданным состо€нием или создает новый.
Flyweight FlyweightFactory::GetFlyweight(const SharedUnit& shared_unit)
{
	std::string key = this->GetKey(shared_unit);
	if (this->flyweights_.find(key) == this->flyweights_.end())
	{
		std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
		this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_unit)));
	}
	else
	{
		std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
	}
	return this->flyweights_.at(key);
}

void FlyweightFactory::ListFlyweights() const
{
	size_t count = this->flyweights_.size();
	std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
	for (std::pair<std::string, Flyweight> pair : this->flyweights_)
	{
		std::cout << pair.first << "\n";
	}
}