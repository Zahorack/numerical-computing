//
// Created by zahorack on 11/23/19.
//

#ifndef NUMERICAL_COMPUTING_SIMPLEX_H
#define NUMERICAL_COMPUTING_SIMPLEX_H

#include "Point.h"
#include "Function.h"


namespace Optimization {

class Vertex {
public:
    Vertex() {}
    ~Vertex() {}
    Vertex(TwoDimensional::Point p, double v);

    TwoDimensional::Point point;
    double value;
};


class TriangleSimplex {

public:
    TriangleSimplex(){}
    TriangleSimplex(Vertex, Vertex, Vertex);

    Vertex bestVertex;
    Vertex worstVertex;
    Vertex neutralVertex;

    void sortSimplex();

    void replaceWorstBy(Vertex);
    void replaceNeutralBy(Vertex);
};
}
#endif //NUMERICAL_COMPUTING_SIMPLEX_H
