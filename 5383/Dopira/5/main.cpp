#include <iostream>
#include <string>

#include "5.h"

using namespace stepik;

void printList(list< shared_ptr<Shape> > &container, std::string name)
{
    std::cout << "List #" + name + ":" << std::endl;
    for(list_iterator< shared_ptr<Shape> > it = container.begin();
        it != container.end(); it++)
    {
        //std::cout << it.operator ->() << " ";
        (*it)->print(std::cout);
    }
    std::cout << std::endl << "-----------------" << std::endl;

}

int main(/*int argc, char *argv[]*/)
{
    list< shared_ptr<Shape> > container1  = createRandomShapeList(10);
    list< shared_ptr<Shape> > container2  = createRandomShapeList(10);

    /*std::vector< shared_ptr<Shape> > v1 =
            {
                    shared_ptr<Shape> (new Ellipse(Color(100, 0, 0), Point(0, 0), 3, 2, 0)),
                    shared_ptr<Shape> (new SectorOfEllipse(Color(0, 0, 0), Point(1, 1), 3, 2, 0, 0, 90)),
                    shared_ptr<Shape> (new Parallelogram(Color(0, 0, 100), Point(0, 0), Point(0, 1), Point(1, 0), Point(1, 1)))
            };

    list< shared_ptr<Shape> > container1;
    for(auto it : v1)
    {
        container1.push_back(it);
    }


    list< shared_ptr<Shape> > container2 ;
    for(auto it : v1)
    {
        container2.push_back(it);
    }*/

    std::cout << std::endl << "Origin Lists:" << std::endl;

    printList(container1, "Container 1");
    printList(container2, "Container 2");
    std::cout << std::endl << "-----------------" << std::endl;


    std::cout << std::endl << "Nonmodify Algorithm:" << std::endl;
    bool isAssign = checkLists(container1, container2, isEqual);
    if(isAssign)
    {
        std::cout << "Containers are equal" << std::endl;
    }
    else
    {
        std::cout << "Containers are different" << std::endl;
    }


    std::cout << std::endl << "Modify Algorithm:" << std::endl;
    eraseElement(container1, redis);
    eraseElement(container2, redis);

    printList(container1, "Container 1");
    printList(container2, "Container 2");
    std::cout << std::endl << "-----------------" << std::endl;



    std::cout << std::endl << "Nonmodify Algorithm:" << std::endl;
    isAssign = checkLists(container1, container2, isEqual);
    if(isAssign)
    {
        std::cout << "Containers are equal" << std::endl;
    }
    else
    {
        std::cout << "Containers are different" << std::endl;
    }

    return 0;
}
