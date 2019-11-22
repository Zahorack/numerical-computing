//
// Created by zahorack on 11/22/19.
//

#ifndef NUMERICAL_COMPUTING_LEVENBERGMARQUARDT_H
#define NUMERICAL_COMPUTING_LEVENBERGMARQUARDT_H

#include "Function.h"
#include "Point.h"

using namespace TwoDimensional;

namespace Optimization {

    class LevenbergMarquardt {
        Function m_function;
        Point m_point;
        float m_precision;

    public:
        LevenbergMarquardt(Function f, Point begin);
        LevenbergMarquardt(Function f, Point begin, float precision);

        Point findMinimum();
    };

}


#endif //NUMERICAL_COMPUTING_LEVENBERGMARQUARDT_H
