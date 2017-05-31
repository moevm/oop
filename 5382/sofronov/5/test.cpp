#include <iostream>
#include <algorithm>
#include "shared_ptr.h"
#include "Shapes.h"
#include "List.h"
#include "gtest/gtest.h"


list<shared_ptr<Shape>> generation ();

bool binary_predicate(const shared_ptr<Shape> &a, const shared_ptr<Shape> &b) {
    return a->doinsert(*b);
}

bool unary_predicate(const shared_ptr<Shape> &a) {
    return (a->radius()<50);
}


list<shared_ptr<Shape>> my_random_list = generation();


TEST(test, is_partitioned_1) {
    list<shared_ptr<Shape>> my_list;

    Shape* first_smaller = new Circle (Point(10,10), 49, red);
    Shape* second_smaller = new Ellipse (Point(-10,0),Point(0,10), red);
    Shape* third_smaller = new Arc (Point (50,0), Point(10,10), 100, red);

    Shape* first_bigger = new Circle (Point(-200,0), 51, red);
    Shape* second_bigger = new Ellipse (Point(-100,0),Point(0,100), red);
    Shape* third_bigger = new Arc (Point (500,0), Point(10,10), 100, red);


    my_list.push_back(shared_ptr<Shape>(first_smaller));
    my_list.push_back(shared_ptr<Shape>(second_smaller));
    my_list.push_back(shared_ptr<Shape>(third_smaller));
    my_list.push_back(shared_ptr<Shape>(first_bigger));
    my_list.push_back(shared_ptr<Shape>(second_bigger));
    my_list.push_back(shared_ptr<Shape>(third_bigger));


    EXPECT_TRUE(std::is_partitioned(my_list.begin(),my_list.end(),unary_predicate));
}


TEST(test, is_partitioned_2) {
    list<shared_ptr<Shape>> my_list;

    Shape* first_smaller = new Circle (Point(10,10), 49, red);
    Shape* second_smaller = new Ellipse (Point(-10,0),Point(0,10), red);
    Shape* third_smaller = new Arc (Point (50,0), Point(10,10), 100, red);

    Shape* first_bigger = new Circle (Point(-200,0), 51, red);
    Shape* second_bigger = new Ellipse (Point(-100,0),Point(0,100), red);
    Shape* third_bigger = new Arc (Point (500,0), Point(10,10), 100, red);


    my_list.push_back(shared_ptr<Shape>(first_smaller));
    my_list.push_back(shared_ptr<Shape>(first_bigger));
    my_list.push_back(shared_ptr<Shape>(second_smaller));
    my_list.push_back(shared_ptr<Shape>(second_bigger));
    my_list.push_back(shared_ptr<Shape>(third_smaller));
    my_list.push_back(shared_ptr<Shape>(third_bigger));


    EXPECT_FALSE(std::is_partitioned(my_list.begin(),my_list.end(),unary_predicate));
}


TEST(test, set_difference_1) {

    list<shared_ptr<Shape>> examine_list;
    list<shared_ptr<Shape>> search_list;
    list<shared_ptr<Shape>> difference_list;

    Shape* to_first_list_1 = new Circle (Point(10,10), 49, red);
    Shape* to_first_list_2 = new Ellipse (Point(-10,0), Point(0,10), red);
    Shape* to_second_list_1 = new Arc (Point (500,0), Point(10,10), 100, red);
    Shape* to_second_list_2 = new Circle (Point(-200,0), 51, red);


    examine_list.push_back(shared_ptr<Shape>(to_first_list_1));
    examine_list.push_back(shared_ptr<Shape>(to_first_list_2));

    search_list.push_back(shared_ptr<Shape>(to_second_list_1));
    search_list.push_back(shared_ptr<Shape>(to_second_list_2));

    std::set_difference(examine_list.begin(), examine_list.end(), search_list.begin(), search_list.end(), std::inserter(difference_list, difference_list.begin()));

    EXPECT_TRUE(difference_list.front()->_id==to_first_list_1->_id);
}