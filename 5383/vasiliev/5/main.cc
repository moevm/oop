#include <chrono>
#include <random>
#include <functional>
#include <cmath>
#include <iostream>
#include "shapes.h"

#include "vector.h"
#include "shared_ptr.h"

etuoop::shared_ptr<etuoop::Shape> createRandomShape()
{
    static const double magicborder = 1 << 8;
    static const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine rng(seed);
    switch (std::uniform_int_distribution<int>(0, 2)(rng)) {
    case 0:
        return etuoop::shared_ptr<etuoop::Rectangle> ( new etuoop::Rectangle(
                    std::uniform_real_distribution<double>(1, magicborder)(rng), // length
                    std::uniform_real_distribution<double>(1, magicborder)(rng), // width
                    etuoop::Point(
                        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
                        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng) // y
                    ),
                    std::uniform_real_distribution<double>(0, 2 * M_PI)(rng), // angle
                    std::uniform_int_distribution<unsigned int>(0, 0xFFFFFFFF)(rng) // color
                ));
    case 1:
        return etuoop::shared_ptr<etuoop::Square> ( new etuoop::Square(
                    std::uniform_real_distribution<double>(1, magicborder)(rng), // side
                    etuoop::Point(
                        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
                        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng) // y
                    ),
                    std::uniform_real_distribution<double>(0, 2 * M_PI)(rng), // angle
                    std::uniform_int_distribution<unsigned int>(0, 0xFFFFFFFF)(rng) // color
                ));
    default:
        return etuoop::shared_ptr<etuoop::Ellipse> ( new etuoop::Ellipse(
                    std::uniform_real_distribution<double>(1, magicborder)(rng), // length
                    std::uniform_real_distribution<double>(1, magicborder)(rng), // width
                    etuoop::Point(
                        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
                        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng) // y
                    ),
                    std::uniform_real_distribution<double>(0, 2 * M_PI)(rng), // angle
                    std::uniform_int_distribution<unsigned int>(0, 0xFFFFFFFF)(rng) // color
                ));
    }
};

etuoop::vector< etuoop::shared_ptr< etuoop::Shape> >
findShapes(etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > source,
           size_t count,
           std::function<bool (etuoop::Shape*)> cond)
{
    etuoop::vector< etuoop::shared_ptr< etuoop::Shape> > r;
    size_t found = 0;
    for (auto& it : source) {
        if (found == count) break;
        if (cond(it.get())) {
            r.push_back(it);
            ++found;
        }
    }
    return r;
}

etuoop::vector< etuoop::shared_ptr< etuoop::Shape> >
copyShapes(etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > source,
           std::function<bool (etuoop::Shape*)> cond)
{
    etuoop::vector< etuoop::shared_ptr< etuoop::Shape> > r;
    for (auto& it : source) {
        if (cond(it.get())) {
            r.push_back(etuoop::shared_ptr< etuoop::Shape> (it->clone()) );
        }
    }
    return r;
}

int main(int argc, char const *argv[])
{
    etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > shapes(1000);
    for (auto& it : shapes) {
        it = createRandomShape();
    }

    etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > foundShapes = findShapes(
                shapes, 250,
    [](etuoop::Shape * shape)->bool {
        return (shape->getColor() > 0x7FFFFFFF);
    }
            );

    etuoop::vector< etuoop::shared_ptr< etuoop::Shape > > copiedShapes = copyShapes(
                shapes,
    [](etuoop::Shape * shape)->bool {
        return (shape->getColor() > 0x7FFFFFFF);
    }
            );

    return 0;
}
