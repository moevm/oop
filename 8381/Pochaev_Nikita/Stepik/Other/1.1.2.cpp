class A
{
public:
    A() {};

private:
    A(const A &a) {};
    A(A &&a) {}
};