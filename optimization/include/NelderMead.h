//
// Created by zahorack on 11/23/19.
//

#ifndef NUMERICAL_COMPUTING_NELDERMEAD_H
#define NUMERICAL_COMPUTING_NELDERMEAD_H

#include "Function.h"
#include "Point.h"
#include "Simplex.h"

using namespace TwoDimensional;

namespace Optimization {

class NelderMead {
    Function m_function;
    Point m_point;
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
    NelderMead(Function f, Point begin);
    NelderMead(Function f, Point begin, double precision, double initSize);

    Point findMinimum();
};

}


#endif //NUMERICAL_COMPUTING_NELDERMEAD_H
