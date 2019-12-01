//
// Created by zahorack on 11/23/19.
//

#include <iostream>
#include "Simplex.h"

namespace Optimization {

Vertex::Vertex(TwoDimensional::Point p, double v):
    point(p),
    value(v)
{}

bool operator<(Vertex const & a, Vertex const & b)
{
    return a.value < b.value;
}


////////////////////////////////////////////////////////////////////////
TriangleSimplex::TriangleSimplex(Vertex a, Vertex b, Vertex c):
    bestVertex(a),
    neutralVertex(b),
    worstVertex(c)
{
    sortSimplex();
}

void TriangleSimplex::sortSimplex()
{
    Vertex vertices[3] = {bestVertex, worstVertex, neutralVertex};
    sort(vertices, vertices +3);

    bestVertex = vertices[0];
    neutralVertex = vertices[1];
    worstVertex = vertices[2];
}

void TriangleSimplex::replaceWorstBy(Vertex better)
{
    worstVertex = better;
}

void TriangleSimplex::replaceNeutralBy(Vertex better)
{
    neutralVertex = better;
}



}