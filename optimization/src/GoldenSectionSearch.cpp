//
// Created by zahorack on 12/1/19.
//

#include "GoldenSectionSearch.h"

namespace Optimization {

static const double GoldenRatio = 0.618;
static const float MaxCycleIterations = 50;

GoldenSectionSearch::GoldenSectionSearch(OneDimensional::Function f, double begin, double end) :
                                         m_function(f),
                                         m_begin(begin),
                                         m_end(end),
                                         m_precision(0.01)
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
        cout<<"Function does not have minimum on given interval\n";
        return -1;
    }

    leftIn = rightOut - GoldenRatio*intervalSize();
    rightIn = leftOut + GoldenRatio*intervalSize();

    for(int i = 0; !terminatingCondition() && i < MaxCycleIterations; i++) {

        cout<<"LK "<<leftOut<<"LV "<<leftIn<<"PV "<<rightIn<< "PK "<<rightOut<<"\n";
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


}


}