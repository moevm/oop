#ifndef OOP_ATTRIBUTE_H
#define OOP_ATTRIBUTE_H
class Attribute{
protected:
    explicit Attribute(int val) : value(val) {};
public:
    int getValue() {return value;};
    void changeValue(int val) {value += val;};
private:
    int value;
};

#endif //OOP_ATTRIBUTE_H
