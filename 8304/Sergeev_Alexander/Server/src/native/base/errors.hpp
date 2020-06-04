#ifndef LOGIC_ERRORS_HPP
#define LOGIC_ERRORS_HPP

#include "third_party_includes.hpp"

// TODO iserializable constructor exception

class basic_exception : public std::exception {
private:
    std::string info;
protected:
    explicit basic_exception (const std::string& msg);
    void log();
public:
    const char* what () const noexcept override;
    void pass();
};



class shared_pointer_exception : public basic_exception {
private:
    std::string info;
public:
    explicit shared_pointer_exception (const std::string& msg);
};

class serialization_exception : public basic_exception {
private:
    std::string info;
public:
    explicit serialization_exception (const std::string& msg);
};

class deserialization_exception : public basic_exception {
private:
    std::string info;
public:
    explicit deserialization_exception (const std::string& msg);
};

class unimplemented_exception : public basic_exception {
private:
    std::string info;
public:
    explicit unimplemented_exception (const std::string& msg);
};

class recursion_exception : public basic_exception {
private:
    std::string info;
public:
    explicit recursion_exception (const std::string& msg);
};

class null_pointer_exception : public basic_exception {
private:
    std::string info;
public:
    explicit null_pointer_exception (const std::string& msg);
};

class out_of_bounds_exception : public basic_exception {
private:
    std::string info;
public:
    explicit out_of_bounds_exception (const std::string& msg);
};

class conflict_exception : public basic_exception {
private:
    std::string info;
public:
    explicit conflict_exception (const std::string& msg);
};

class rights_exception : public basic_exception {
private:
    std::string info;
public:
    explicit rights_exception (const std::string& msg);
};

class type_exception : public basic_exception {
private:
    std::string info;
public:
    explicit type_exception (const std::string& msg);
};

/*class todo_exception : public std::exception {
private:
    std::string info;

public:
    explicit todo_exception (const std::string& msg) : info(msg) { }
    const char* what () const noexcept override {
        std::cout << info;
        return "help";
        //return ("[RELEASE THIS EXCEPTION] " + ).c_str(); FIXME
    }
};*/

#endif //LOGIC_ERRORS_HPP