//
// Created by zahorack on 11/22/19.
//

#ifndef NUMERICAL_COMPUTING_NEWTONRAPHSON_H
#define NUMERICAL_COMPUTING_NEWTONRAPHSON_H

#include "Function.h"
#include "Point.h"

using namespace TwoDimensional;

namespace Optimization {

class NewtonRaphson {
    Function m_function;
    Point m_point;
    float m_precision;

public:
    NewtonRaphson(Function f, Point begin);
    NewtonRaphson(Function f, Point begin, float precision);

    Point findMinimum();
};

}

#endif //NUMERICAL_COMPUTING_NEWTONRAPHSON_H
