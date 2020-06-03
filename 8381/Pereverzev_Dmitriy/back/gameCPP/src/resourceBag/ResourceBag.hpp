#ifndef ResourceBag_hpp
#define ResourceBag_hpp

#include <map>
#include "../TypeСonstants.hpp"
#include "../simplifiedConverter/SimplifiedConverter.hpp"

class ResourceBag : SimplifiedConverter
{
private:
    std::map<unsigned int, double> resourceBag;

public:
    ResourceBag();
    ~ResourceBag();
    std::map<unsigned int, double> getResourceBag();
    void addResource(unsigned int type, double quantity);
    void subtractResource(unsigned int type, double quantity);
    bool checkQuantity(std::map<unsigned int, double> price);

    v8::Local<v8::Object> getFullInfo();
};

#endif /* ResourceBag_hpp */
