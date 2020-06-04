#include "napi.h"
#include <string>
#include "utils/json.hpp"
#include "online/api.hpp"

// Arg0 - Json string
void Start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments is Start()").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Argument isn't a string in Start()").ThrowAsJavaScriptException();
        return;
    }
    json config = json::parse(info[0].ToString().Utf8Value());
    online::api::get().start(config);
    return;
}

Napi::String Update(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() > 0) {
        Napi::TypeError::New(env, "Wrong number of arguments is Update()").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }
    json output;
    online::api::get().update(output);
    return Napi::String::New(env, output.dump());
}

// Arg0 - Json string
Napi::String Signal(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments is Signal()").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Argument isn't a string in Signal()").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }
    json input = json::parse(info[0].ToString().Utf8Value());
    json output;
    online::api::get().signal(input, output);
    return Napi::String::New(env, output.dump());
}

// Callback for registering module with node.js
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "Start"),
        Napi::Function::New(env, Start)
    );
    exports.Set(
        Napi::String::New(env, "Update"),
        Napi::Function::New(env, Update)
    );
    exports.Set(
        Napi::String::New(env, "Signal"),
        Napi::Function::New(env, Signal)
    );
    return exports;
}


// Register 'naviteoop' module
NODE_API_MODULE(nativeoop, Init)