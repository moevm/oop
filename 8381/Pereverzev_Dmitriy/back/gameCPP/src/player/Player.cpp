#include "Player.hpp"

Player::Player(std::string playerID, std::string playerName, Field *field, UUID *uuidGen, CombatObjectTypeFactory *combatObjectTypeFactory)
{
    this->playerID = playerID;
    this->playerName = playerName;
    this->field = field;

    this->uuidGen = uuidGen;
    this->combatObjectTypeFactory = combatObjectTypeFactory;
    resourceBag = new ResourceBag;
}

Player ::~Player()
{
    
    
    
}

std::string Player::getPlayerID() { return this->playerID; }
std::string Player::getPlayerName() { return this->playerName; }
Base *Player::getBase() { return this->base; }
ResourceBag *Player::getResourceBag() { return resourceBag; }

void Player::createBase(unsigned int rowNumber, unsigned int columnNumber)
{

    this->base = new Base(playerID, uuidGen->generateUUID(), 100, 1000, 4, combatObjectTypeFactory);
    this->field->addObject(rowNumber, columnNumber, base);
}

void Player::createUnit(unsigned int rowNumber, unsigned int columnNumber, unsigned int type)
{
    if (base == nullptr)
    {
        
        throw(Except("Create the base first", "Player::createUnit(unsigned int rowNumber, unsigned int columnNumber, unsigned int type)", 0));

        return;
    }

    Unit *unit = base->createUnit(type, uuidGen->generateUUID(), combatObjectTypeFactory);

    unit->attachEvent("object death", field);
    unit->attachEvent("found resources", this);

    field->addObject(rowNumber, columnNumber, unit);
}
void Player::moveObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)
{
    field->moveObject(fromRowNumber, fromColumnNumber, toRowNumber, toColumnNumber);
}
void Player::interactionObject(unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)
{
    field->getMediator()->interactionObjObj(field, fromRowNumber, fromColumnNumber, toRowNumber, toColumnNumber);
}

void Player::eventHandler(Event *event)
{
    if (event->getSEventId() == "found resources")
    {
        unsigned int type;
        double quantity;

        if (!GetObjProperty(event->getData()->ToObject(), "type", type))
            return;
        if (!GetObjProperty(event->getData()->ToObject(), "quantity", quantity))
            return;
        resourceBag->addResource(type, quantity);
    }
}

v8::Local<v8::Object> Player::getFullInfo()
{
    v8::Local<v8::Object> info = Nan::New<v8::Object>();
    v8::Local<v8::Object> ResourceBag = Nan::New<v8::Object>();
    
    SetObjProperty(info, "resourceBag", resourceBag->getFullInfo());
    SetObjProperty(info, "playerName", playerName);
    SetObjProperty(info, "playerID", playerID);
    
    SetObjProperty(info, "base", field->getObjectData(base));
    

    return info;
}
