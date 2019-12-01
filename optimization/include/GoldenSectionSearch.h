//
// Created by zahorack on 12/1/19.
//

#ifndef NUMERICAL_COMPUTING_GOLDENSECTIONSEARCH_H
#define NUMERICAL_COMPUTING_GOLDENSECTIONSEARCH_H

#include "Function.h"
#include "Point.h"

namespace Optimization {

class GoldenSectionSearch {

    OneDimensional::Function m_function;
    const double m_begin, m_end;
    const double m_precision;

    double leftOut, rightOut, leftIn, rightIn;

    bool hasMinimumOnInterval();
    double intervalSize();
    bool terminatingCondition();

public:
    ~GoldenSectionSearch();
    GoldenSectionSearch(OneDimensional::Function f, double begin, double end);

    double findMinimum();
};

}


#endif //NUMERICAL_COMPUTING_GOLDENSECTIONSEARCH_H
