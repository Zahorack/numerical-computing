//
// Created by zahorack on 12/1/19.
//

#include "GoldenSectionSearch.h"


/*
 * Golden selection search is one-dimensional optimization method
 * used for numerical finding locally minimum of given function at given interval.
 *
 *      - it requires to know only function values in all points
 *      - fundamental condition is, function must be convex at given interval
 *
 */


namespace Optimization {

static const double GoldenRatio = 0.618;
static const float MaxCycleIterations = 50;

GoldenSectionSearch::GoldenSectionSearch(OneDimensional::Function f, double begin, double end) :
     m_function(f),
     m_begin(begin),
     m_end(end),
     m_precision(0.01),
     m_timer(Time::Microseconds)
{
    leftOut = m_begin;
    rightOut = m_end;
}

GoldenSectionSearch::GoldenSectionSearch(OneDimensional::Function f, double begin, double end, double precision) :
        m_function(f),
        m_begin(begin),
        m_end(end),
        m_precision(precision),
        m_timer(Time::Microseconds)
{
    leftOut = m_begin;
    rightOut = m_end;
}

GoldenSectionSearch::~GoldenSectionSearch()
{}


bool GoldenSectionSearch::hasMinimumOnInterval()
{
    if(m_function.isFalling(m_begin) && m_function.isRising(m_end)) {
        return true;
    }
    return false;
}

double GoldenSectionSearch::intervalSize()
{
    return (rightOut - leftOut);
}

bool GoldenSectionSearch::terminatingCondition()
{
    return (intervalSize() <= 2*m_precision);
}

double GoldenSectionSearch::findMinimum()
{
    if(!hasMinimumOnInterval()) {
        cout<<"Invalid parameters -> Function does not have minimum on given interval - is not convex\n";
        return -1;
    }

    m_timer.start();

    leftIn = rightOut - GoldenRatio*intervalSize();
    rightIn = leftOut + GoldenRatio*intervalSize();

    for(int i = 0; !terminatingCondition() && i < MaxCycleIterations; i++) {

        cout<<"LK "<<leftOut<<"  LV "<<leftIn<<"  PV "<<rightIn<< "  PK "<<rightOut<<"\n";
        if(m_function.value(leftIn) > m_function.value(rightIn)) {
            leftOut = leftIn;
            leftIn = rightIn;
            rightIn = leftOut + GoldenRatio*intervalSize();
        }
        else {
            rightOut = rightIn;
            rightIn = leftIn;
            leftIn = rightOut - GoldenRatio*intervalSize();
        }
    }

    m_timer.stop();

    double minimum = (rightIn + leftIn)/2;
    cout<<"Minimum of function is f(min) = "<<m_function.value(minimum)<<", at point min = ["<<minimum<<"]\n";
    m_timer.result();

    return minimum;
}


}