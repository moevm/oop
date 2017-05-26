#include "vector.h"
#include "shared_ptr.h"
#include "figure.h"
#include "lab_fun.h"
#include <iostream>


int main () {
  shapeVec a;
  shapeVec b;

  generateShapes(a,5000);
  generateShapes(a,5000);

  std::cout << alg1(a) << "\n";
  std::cout << (alg2(a, b)).size();
  
  return 0;
}
