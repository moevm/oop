#ifndef SimplifiedConverter_hpp
#define SimplifiedConverter_hpp

#include <iostream>
#include <node.h>
#include <nan.h>
#include <node_object_wrap.h>
#include <map>

class SimplifiedConverter
{

public:
    
    
    
    
    

    
    bool GetObjProperty(v8::Local<v8::Object> obj, std::string propertyName, unsigned int &value);          
    bool GetObjProperty(v8::Local<v8::Object> obj, std::string propertyName, double &value);                
    bool GetObjProperty(v8::Local<v8::Object> obj, std::string propertyName, std::string &value);           
    bool GetObjProperty(v8::Local<v8::Object> obj, std::string propertyName, v8::Local<v8::Object> &value); 
    bool GetObjProperty(v8::Local<v8::Object> obj, std::string propertyName, v8::Local<v8::Array> &value);  
    bool GetObjProperty(v8::Local<v8::Object> obj, unsigned int propertyName, double &value);               

    
    bool SetObjProperty(v8::Local<v8::Object> &obj, std::string propertyName, unsigned int value);          
    bool SetObjProperty(v8::Local<v8::Object> &obj, std::string propertyName, double value);                
    bool SetObjProperty(v8::Local<v8::Object> &obj, std::string propertyName, std::string value);           
    bool SetObjProperty(v8::Local<v8::Object> &obj, std::string propertyName, v8::Local<v8::Array> value);  
    bool SetObjProperty(v8::Local<v8::Object> &obj, std::string propertyName, v8::Local<v8::Object> value); 
    bool SetObjProperty(v8::Local<v8::Object> &obj, std::string propertyName, v8::Local<v8::Value> value);  
    bool SetObjProperty(v8::Local<v8::Object> &obj, unsigned int index, v8::Local<v8::Object> value);       
    bool SetObjProperty(v8::Local<v8::Object> &obj, unsigned int index, double value);                      

    bool SetArrProperty(v8::Local<v8::Array> &array, unsigned int index, unsigned int value); 
    bool SetArrProperty(v8::Local<v8::Array> &array, unsigned int index, std::string value);  
    
    bool SetArrProperty(v8::Local<v8::Array> &array, unsigned int index, v8::Local<v8::Object> value); 
    bool SetArrProperty(v8::Local<v8::Array> &array, unsigned int index, v8::Local<v8::Array> value);  

    bool GetArrProperty(v8::Local<v8::Array> obj, unsigned int index, unsigned int &value);          
    bool GetArrProperty(v8::Local<v8::Array> obj, unsigned int index, v8::Local<v8::Object> &value); 

    std::string JSONStringified(v8::Local<v8::Object> obj);
    v8::Local<v8::Object> JSONParse(std::string json_string);

    bool ObjToMap(v8::Local<v8::Object> obj, std::map<unsigned int, double>  &map); 
};
#endif /* SimplifiedConverter_hpp */