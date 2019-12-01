//
// Created by zahorack on 11/22/19.
//

#ifndef NUMERICAL_COMPUTING_LEVENBERGMARQUARDT_H
#define NUMERICAL_COMPUTING_LEVENBERGMARQUARDT_H

#include "Function.h"
#include "Point.h"

namespace Optimization {

    class LevenbergMarquardt {
        TwoDimensional::Function m_function;
        TwoDimensional::Point m_point;
        float m_precision;

    public:
        LevenbergMarquardt(TwoDimensional::Function f, TwoDimensional::Point begin);
        LevenbergMarquardt(TwoDimensional::Function f, TwoDimensional::Point begin, float precision);
        ~LevenbergMarquardt();

        TwoDimensional::Point findMinimum();
    };

}


#endif //NUMERICAL_COMPUTING_LEVENBERGMARQUARDT_H
