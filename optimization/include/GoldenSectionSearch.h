//
// Created by zahorack on 12/1/19.
//

#ifndef NUMERICAL_COMPUTING_GOLDENSECTIONSEARCH_H
#define NUMERICAL_COMPUTING_GOLDENSECTIONSEARCH_H

/*
 * Golden selection search is one-dimensional optimization method
 * used for numerical finding locally minimum of given function at given interval.
 *
 *      - it requires to know only function values in all points
 *      - fundamental condition is, function must be convex at given interval
 *
 */


#include "Function.h"
#include "Point.h"
#include "Timer.h"

namespace Optimization {

class GoldenSectionSearch {

    OneDimensional::Function m_function;
    Timer m_timer;
    const double m_begin, m_end;
    const double m_precision;

    double leftOut, rightOut, leftIn, rightIn;

    bool hasMinimumOnInterval();
    double intervalSize();
    bool terminatingCondition();

public:
    ~GoldenSectionSearch();
    GoldenSectionSearch(OneDimensional::Function f, double begin, double end);
    GoldenSectionSearch(OneDimensional::Function f, double begin, double end, double precision);

    double findMinimum();
};

}


#endif //NUMERICAL_COMPUTING_GOLDENSECTIONSEARCH_H
