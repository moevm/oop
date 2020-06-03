#include "ResourceBag.hpp"

ResourceBag::ResourceBag()
{
    resourceBag = {std::make_pair(GOLD, 0),
                   std::make_pair(WOOD, 0),
                   std::make_pair(FOOD, 0)};
}

std::map<unsigned int, double> ResourceBag::getResourceBag() { return resourceBag; }

void ResourceBag::addResource(unsigned int type, double quantity) { resourceBag.find(type) != resourceBag.end() ? resourceBag[type] += quantity : resourceBag[type] = quantity; }

void ResourceBag::subtractResource(unsigned int type, double quantity) { resourceBag.find(type) != resourceBag.end() ? resourceBag[type] -= quantity : resourceBag[type] = 0; }

bool ResourceBag::checkQuantity(std::map<unsigned int, double> price)
{

    for (std::map<unsigned int, double>::iterator it = price.begin(); it != price.end(); ++it)
    {
        if (resourceBag.find(it->first) != resourceBag.end())
            if (resourceBag[it->first] > price[it->first])
                continue;
        return false;
    }
    return true;
}

v8::Local<v8::Object> ResourceBag::getFullInfo()
{
    v8::Local<v8::Object> info = Nan::New<v8::Object>();
    for (std::map<unsigned int, double>::iterator it = resourceBag.begin(); it != resourceBag.end(); ++it)
    {
        SetObjProperty(info, it->first, it->second);
    }
    return info;
}