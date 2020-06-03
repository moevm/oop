#include <node.h>
// #include "gameProxy/GameProxy.hpp"
#include "uiFacade/UIFacade.hpp"

namespace demo
{

void InitAll(v8::Local<v8::Object> exports)
{
    UIFacade::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)

} // namespace demo