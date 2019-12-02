//
// Created by zahorack on 12/2/19.
//

#include "DavidonSearch.h"
#include "chrono"

/*
 * Davidon's search is one-dimensional optimization method
 * used for numerical finding locally extreme of given function at given interval.
 *
 *      - it requires to know only function and first derivation value in all points
 *      - fundamental condition is, function must be convex at given interval
 *
 */


namespace Optimization {

    static const float MaxCycleIterations = 50;

    DavidonSearch::DavidonSearch(SearchMode::Enum mode, OneDimensional::Function f, double begin, double end) :
        m_mode(mode),
        m_function(f),
        m_begin(begin),
        m_end(end),
        m_precision(0.01),
        m_timer(Time::Microseconds)
    {
        leftEdge = m_begin;
        rightEdge = m_end;
    }

    DavidonSearch::DavidonSearch(SearchMode::Enum mode, OneDimensional::Function f, double begin, double end, double precision) :
        m_mode(mode),
        m_function(f),
        m_begin(begin),
        m_end(end),
        m_precision(precision),
        m_timer(Time::Microseconds)
    {
        leftEdge = m_begin;
        rightEdge = m_end;
    }

    DavidonSearch::~DavidonSearch()
    {}


    bool DavidonSearch::hasExtremeOnInterval()
    {
        double d_begin = m_function.gradient(m_begin);
        double d_end = m_function.gradient(m_end);

        if(d_begin * d_end < 0) {
            return true;
        }
        return false;
    }

    double DavidonSearch::intervalSize()
    {
        return (rightEdge - leftEdge);
    }

    bool DavidonSearch::terminatingCondition()
    {
        return (intervalSize() <= 2*m_precision);
    }

    double DavidonSearch::findMinimum()
    {
        if(!hasExtremeOnInterval()) {
            cout<<"Invalid parameters -> Function does not have extreme on given interval!\n";
            return -1;
        }

        m_timer.start();
        double z, w, x;

        for(int i = 0; !terminatingCondition() && i < MaxCycleIterations; i++) {

            double dF_left = m_function.gradient(leftEdge);
            double dF_right = m_function.gradient(rightEdge);

            double F_left = m_function.value(leftEdge);
            double F_right = m_function.value(rightEdge);

            z = dF_right + dF_left - 3 * (F_right - F_left) / (rightEdge - leftEdge);
            w = sqrt(pow(z, 2) - dF_left * dF_right);

            if (m_mode == SearchMode::Maximization)
                x = leftEdge + (z - dF_left - w) * (rightEdge - leftEdge) / (dF_right - dF_left - 2 * w);
            else
                x = leftEdge + (z - dF_left + w) * (rightEdge - leftEdge) / (dF_right - dF_left + 2 * w);

            if (m_function.gradient(x) > 0)
                rightEdge = x;
            else
                leftEdge = x;

            cout<<"x: "<<x<<"  fx: "<<m_function.value(x)<<"  interval: "<<intervalSize()<<"\n";
        }

        double minimum = x;
        m_timer.stop();
        cout<<"Extreme of function is f(min) = "<<m_function.value(minimum)<<", at point min = ["<<minimum<<"]\n";
        m_timer.result();

        return minimum;
    }


}
