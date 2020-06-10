#ifndef ADAPTER_H
#define ADAPTER_H
#include <string>

class Target
{
public:
    virtual std::string request(const std::string&);
    virtual ~Target() = default;
};

class Adaptee
{
    static unsigned long long counter;
public:
    std::string specificRequest(const std::string&);
};

class Adapter : public Target
{
public:
    std::string request(const std::string &) override;
    ~Adapter() override;
private:
    Adaptee* adaptee = new Adaptee;
};

#endif // ADAPTER_H
