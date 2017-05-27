#include "shared_ptr.h"
#include "vector.h"
#include "shape.h"
#include "arc.h"
#include "circle.h"
#include "ellipse.h"

shape *generateRandomShape();
stepik::vector< stepik::shared_ptr<shape> > generateShapes(unsigned int n);

bool type_predikat(shape* first, shape* second);

int same_search(const stepik::vector<stepik::shared_ptr<shape> > &first, const stepik::vector<stepik::shared_ptr<shape> > &second);
stepik::vector< stepik::shared_ptr<shape> > intersection(const stepik::vector<stepik::shared_ptr<shape> > &first, const stepik::vector<stepik::shared_ptr<shape> > &second);