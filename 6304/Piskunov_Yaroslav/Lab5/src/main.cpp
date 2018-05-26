#include <iostream>
#include <shape.hpp>
#include <vector.hpp>
#include <shared_ptr.hpp>

using namespace std;
typedef stepik::shared_ptr<shape> vectorType;
using stepik::shared_ptr;

int main()
{
    stepik::vector<vectorType> kontainer;

    for (int i=1; i<=1000; i++)
    {
        switch (i % 3)
        {
        case 0:
        {
            eclipse* b = new eclipse(0, 0, 4, 10);
            b->setColor(0x0ffff0);
            kontainer.push_back(shared_ptr<shape>(b));
            break;
        }
        case 1:
        {
            NOtrap* c = new NOtrap(0, 0, 4, 10, 6);
            c->setColor(0x0f00f0);
            kontainer.push_back(shared_ptr<shape>(c));
            break;
        }
        case 2:
        {
            trap* d = new trap(0, 0, 4, 10, 6, 3);
            d->setColor(0x0ffff0);
            kontainer.push_back(shared_ptr<shape>(d));
            break;
        }
        }
    }

    size_t i = 0;
    unsigned int temp = 0;
    for (auto current: kontainer)
    {
        if (current->getColor() == temp)
            cout << "Elements " << i << " and " << i+1 << " are ok" << endl;
        temp = current->getColor();
        i++;
    }
    int k = 0;
    for(i=0; i<1000; i++)
    {
        if (i >= kontainer.size() - 1)
            break;
        unsigned int temp = (kontainer.operator [](i))->getColor();

        if(temp < 0x0ffff0)
        {
            kontainer.erase(&(kontainer.operator [](i)));
            cout << "Element deleted - " << i + k << endl;
            k++;
        }
    }

    return 0;
}
