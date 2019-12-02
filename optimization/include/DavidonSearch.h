//
// Created by zahorack on 12/2/19.
//

#ifndef NUMERICAL_COMPUTING_DAVIDONSEARCH_H
#define NUMERICAL_COMPUTING_DAVIDONSEARCH_H


/*
 * Davidon's search is one-dimensional optimization method
 * used for numerical finding locally extreme of given function at given interval.
 *
 *      - it requires to know only function and first derivation value in all points
 *      - fundamental condition is, function must be convex at given interval
 *
 */

namespace SearchMode {
    enum Enum {
        Minimization = 0,
        Maximization
    };
}

#include "Function.h"
#include "Point.h"
#include "Timer.h"

namespace Optimization {

    class DavidonSearch {

        OneDimensional::Function m_function;
        Timer m_timer;
        const double m_begin, m_end;
        const double m_precision;
        SearchMode::Enum m_mode;

        double leftEdge, rightEdge;

        bool hasExtremeOnInterval();
        double intervalSize();
        bool terminatingCondition();

    public:
        ~DavidonSearch();
        DavidonSearch(SearchMode::Enum, OneDimensional::Function f, double begin, double end);
        DavidonSearch(SearchMode::Enum, OneDimensional::Function f, double begin, double end, double precision);

        double findMinimum();
    };

}


#endif //NUMERICAL_COMPUTING_DAVIDONSEARCH_H
