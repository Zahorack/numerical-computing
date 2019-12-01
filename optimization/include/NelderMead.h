//
// Created by zahorack on 11/23/19.
//

#ifndef NUMERICAL_COMPUTING_NELDERMEAD_H
#define NUMERICAL_COMPUTING_NELDERMEAD_H

#include "Function.h"
#include "Point.h"
#include "Simplex.h"

namespace Optimization {

class NelderMead {
    TwoDimensional::Function m_function;
    TwoDimensional::Point m_point;
    double m_precision;
    double m_initialSize;

    Vertex center();
    Vertex reflection();
    Vertex expansion();
    Vertex contraction();
    Vertex reduction(Vertex);

    TriangleSimplex createInitialSimplex();
    bool terminatingCondition();

    TriangleSimplex simplex;

public:
    NelderMead(TwoDimensional::Function f, TwoDimensional::Point begin);
    NelderMead(TwoDimensional::Function f, TwoDimensional::Point begin, double precision, double initSize);

    TwoDimensional::Point findMinimum();
};

}


#endif //NUMERICAL_COMPUTING_NELDERMEAD_H
