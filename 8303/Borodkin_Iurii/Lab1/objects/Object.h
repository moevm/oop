#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <utility>


class Object
{
protected:
    std::pair <int, int> _coordinates;
    std::string _name;
    unsigned _health;
    explicit Object(std::pair<int, int> coordinates, std::string = "");
public:
    enum Moves {
        BACK = -1,
        STAY     ,
        FORWARD
    };
    std::string &name();
    virtual std::string type() const;
    virtual unsigned health() const;
    virtual std::pair <int, int> coordinates() const;
    void moveX(Moves);
    void moveY(Moves);
    virtual ~Object() = default;
};

#endif // OBJECT_H
