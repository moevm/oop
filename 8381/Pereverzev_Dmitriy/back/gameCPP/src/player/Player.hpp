#ifndef Player_hpp
#define Player_hpp

#include <map>
#include "../field/Field.hpp"
#include "../objects/combatObject/base/Base.hpp"
#include "../uuid/UUID.hpp"
#include "../TypeСonstants.hpp"
#include "../eventProvider/EventProvider.hpp"
#include "../resourceBag/ResourceBag.hpp"

class Player : public EventProvider
{
private:
    Field *field;
    Base *base;
    UUID *uuidGen;
    CombatObjectTypeFactory *combatObjectTypeFactory;

    std::string playerID;
    std::string playerName;

    ResourceBag *resourceBag;

public:
    Player(std::string playerID, std::string playerName, Field *field, UUID *uuidGen, CombatObjectTypeFactory *combatObjectTypeFactory);
    ~Player();

    std::string getPlayerID();
    std::string getPlayerName();
    Base *getBase();
    ResourceBag *getResourceBag();

    void
    createBase(unsigned int rowNumber, unsigned int columnNumber);
    void createUnit(unsigned int rowNumber, unsigned int columnNumber, unsigned int type);
    void moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber);
    void interactionObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber);
    void eventHandler(Event *event) override;
    v8::Local<v8::Object> getFullInfo();
};

#endif /* Player_hpp */
