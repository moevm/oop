#ifndef Except_hpp
#define Except_hpp

#include <exception>
#include <string>

#include "../simplifiedConverter/SimplifiedConverter.hpp"

class Except : virtual public std::exception, SimplifiedConverter
{

protected:
    unsigned int error_number;
    std::string error_place;
    std::string error_message;

public:
    explicit Except(const std::string &msg, const std::string &place, int err_num) : error_number(err_num),
                                                                                     error_message(msg),
                                                                                     error_place(place)

    {
    }

    virtual ~Except() throw() {}
    virtual const char *what() const throw()
    {
        return error_message.c_str();
    }
    virtual std::string getErrorPlace() const throw()
    {
        return error_place;
    }
    virtual int getErrorNumber() const throw()
    {
        return error_number;
    }

    v8::Local<v8::Value> getLog()
    {
        v8::Local<v8::Object> data = Nan::New<v8::Object>();
        SetObjProperty(data, "msg", error_message);
        SetObjProperty(data, "num", error_number);
        SetObjProperty(data, "place", error_place);
        return data;
    }
};
#endif /* Except_hpp */