#include <ctime>
#include <functional>

#include "../../2/Lab2Tests/src/square.h"
#include "../../2/Lab2Tests/src/righttriangle.h"
#include "../../2/Lab2Tests/src/isoscelestriangle.h"
#include "../../3/vector.h"
#include "../../4/shared_ptr.h"

stepik::shared_ptr<Shape> multipleSearch(
        stepik::vector< stepik::shared_ptr<Shape> > source,
        stepik::vector< stepik::shared_ptr<Shape> > possibleElements,
        std::function< bool (Shape*, Shape*) > condition );

Shape *generateRandomShape();
stepik::vector< stepik::shared_ptr<Shape> > generateShapes(size_t n);
