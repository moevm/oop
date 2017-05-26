#include "vector.h"
#include "shared_ptr.h"
#include "figure.h"
#include "lab_fun.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace stepik;

TEST(testSort, generateTest) {
  shapeVec a;
  generateShapes(a, 10);
  sortShapeVec(a);
  for (size_t i = 0; i < a.size()-1;i++) {
    ASSERT_FALSE((**a[i]).area() < (**a[i]).area());
  }

  a = shapeVec();
  generateShapes(a, 1000);
  sortShapeVec(a);
  for (size_t i = 0; i < a.size()-1;i++) {
    ASSERT_FALSE((**a[i]).area() < (**a[i]).area());
  }
}

TEST(testAlg1, test) {
  shapeVec a;
  stepik::shared_ptr<Shape*> q;

  q.reset(new Shape*(new Triangle(3, Point(3, 3))));
  a.push_back(q);

  ASSERT_FALSE(alg1(a));

  q.reset(new Shape*(new Triangle(3, Point(3, 3), Point(5, 5))));
  a.push_back(q);
  ASSERT_TRUE(alg1(a));

  q.reset(new Shape*(new Rhombus(1, 3.14159/3)));
  a.insert(a.begin(), q);
  ASSERT_TRUE(alg1(a));

  (*q)->scale(5);
  ASSERT_FALSE(alg1(a));

  q.reset(new Shape*(new Parallelogram(1, 1, Point(-10, 10))));
  a.push_back(q);
  ASSERT_TRUE(alg1(a, Parallelogram(100, 100, Point(-5, -5))));

  a.insert(a.begin(), q);
  ASSERT_FALSE(alg1(a, Parallelogram(100, 100, Point(-5, -5))));
}

TEST(testAlg2, test) {
  shapeVec a;
  shapeVec b;
  shapeVec temp;
  stepik::shared_ptr<Shape*> q;

  q.reset(new Shape*(new Triangle(3, Point(3, 3))));
  a.push_back(q);
  q.reset(new Shape*(new Triangle(3, Point(3, 3), Point(5, 5))));
  a.push_back(q);
  temp = alg2(a, b);
  ASSERT_TRUE(temp.size() == 0);


  b.push_back(q);
  temp = alg2(a, b);
  ASSERT_TRUE(temp.size() == 1);
  ASSERT_EQ(**temp[0], **q);
  q.reset(new Shape*(new Parallelogram(3, 90, Point(5, 5))));
  a.push_back(q);
  b.push_back(q);
  temp = alg2(a, b);
  ASSERT_TRUE(temp.size() == 2);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
