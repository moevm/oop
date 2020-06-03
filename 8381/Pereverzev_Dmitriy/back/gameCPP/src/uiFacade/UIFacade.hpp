#ifndef UIFacade_hpp
#define UIFacade_hpp

#include <node.h>
#include <nan.h>
#include <node_object_wrap.h>

#include "../command/gameCommand/GameCommand.hpp"
#include "../eventProvider/EventProvider.hpp"
#include "../logger/loggerProxy/LoggerProxy.hpp"

namespace demo
{

class UIFacade : public node::ObjectWrap, public EventProvider
{
private:
    
    Game *game;
    Logger *logger;
    v8::Local<v8::Array> response;

    explicit UIFacade();
    ~UIFacade();

    static void New(const v8::FunctionCallbackInfo<v8::Value> &args);

    static void sendRequest(const v8::FunctionCallbackInfo<v8::Value> &args);
    void eventHandler(Event *event) override;

public:
    static void Init(v8::Local<v8::Object> exports);
};
} 
#endif /* UIFacade_hpp */
