//
// Created by zahorack on 11/22/19.
//

#ifndef NUMERICAL_COMPUTING_NEWTONRAPHSON_H
#define NUMERICAL_COMPUTING_NEWTONRAPHSON_H

#include "Function.h"
#include "Point.h"
#include "Timer.h"

namespace Optimization {

    class NewtonRaphson {
        TwoDimensional::Function m_function;
        TwoDimensional::Point m_point;
        Timer m_timer;
        float m_precision;

    public:
        NewtonRaphson(TwoDimensional::Function f, TwoDimensional::Point begin);

        NewtonRaphson(TwoDimensional::Function f, TwoDimensional::Point begin, float precision);

        TwoDimensional::Point findMinimum();
    };
}

#endif //NUMERICAL_COMPUTING_NEWTONRAPHSON_H
