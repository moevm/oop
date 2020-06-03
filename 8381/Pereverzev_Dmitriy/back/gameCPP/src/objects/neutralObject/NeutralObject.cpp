#include "NeutralObject.hpp"

void NeutralObject::eventHandler(Event *event) {}

v8::Local<v8::Object> NeutralObject::getFullInfo()
{
    v8::Local<v8::Object> info = Object::getFullInfo();

    return info;
}