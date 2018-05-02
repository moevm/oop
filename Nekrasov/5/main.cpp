#include <iostream>
#include <random>
#include <chrono>

#include "shapes.hpp"
#include "shared_ptr.hpp"
#include "vector.hpp"

//Поиск первого из нескольких возможных элементов по заданному критерию.
//Скопировать элементы, удовлетворяющие критерию.

void gen( custom::vector< custom::shared_ptr<Shape> >* arr )
{
    std::random_device rd;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt;
    mt.seed( rd.entropy() ? rd() : seed );

    std::uniform_int_distribution<int> rndnum(0, 255);
    std::uniform_int_distribution<int> class_type(0, 1);

    for( size_t i = 0; i < 1000; ++i )
    {
        switch (class_type(mt)){
        case 0:
        {
            Shape* bc = new Circle( rndnum(mt) % 85, rndnum(mt) % 34, rndnum(mt) );
            bc->setcolour(rndnum(mt),rndnum(mt),rndnum(mt));
            arr->push_back(custom::shared_ptr<Shape>(bc));
            break;
        }
        case 1:
        {
            Shape* bp = new Polygon( rndnum(mt) % 33, rndnum(mt) % 66, rndnum(mt), rndnum(mt) % 63, rndnum(mt) % 36 );
            bp->setcolour(rndnum(mt),rndnum(mt),rndnum(mt));
            arr->push_back(custom::shared_ptr<Shape>(bp));
            break;
        }
        }
    }
}

int find(double x, double y, custom::vector< custom::shared_ptr<Shape> > arr)
{
    for( size_t i = 0; i < arr.size(); ++i )
    {
        if( (arr[i].get()->getcenter() == point(x,y)) ) return i;
    }
    return -1;
}

size_t copy( char r, char g, char b, custom::vector< custom::shared_ptr<Shape> >* source )
{
    size_t size = source->size();
    for(size_t i = 0; i < size; ++i)
    {
        RGB temp = source->at(i).get()->getcolour();
        if( temp.R + temp.B + temp.G < r + g + b ) //copy if darker
            source->push_back(source->at(i));
    }
    return source->size();
}

void print(custom::vector< custom::shared_ptr<Shape> > input, size_t begin)
{
    for( ; begin < input.size(); ++begin )
    {
        input[begin].get()->print();
    }
}

int main()
{
    custom::vector< custom::shared_ptr<Shape> > arr;
    gen(&arr);

    double x;
    double y;
    std::cin >> x >> y;

    int ind;
    if( (ind = find(x,y, arr)) != -1 )
        std::cout << *arr[ind].get() << '\n';
    else
        std::cout << "Not" << '\n';

    char r, g, b;
    size_t size = arr.size();
    std::cin >> r >> g >> b;
    copy(r,g,b, &arr);
    if( size != arr.size() )
    {
        std::cout << "Smth changed";
        print(arr, size);
    }
    return 0;
}
