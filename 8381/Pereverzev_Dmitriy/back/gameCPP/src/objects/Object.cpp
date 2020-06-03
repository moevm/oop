#include "Object.hpp"

unsigned int Object::getObjectType() { return objectType; }
std::string Object::getPlayerID() { return playerID; }

v8::Local<v8::Object> Object::getFullInfo()
{
    v8::Local<v8::Object> info = Nan::New<v8::Object>();

    SetObjProperty(info, "objectType", objectType);
    SetObjProperty(info, "move", move);
    SetObjProperty(info, "ID", ID);
    SetObjProperty(info, "playerID", playerID);

    return info;
}
