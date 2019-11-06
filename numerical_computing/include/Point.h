//
// Created by zahorack on 11/5/19.
//

#ifndef NUMERICAL_COMPUTING_POINT_H
#define NUMERICAL_COMPUTING_POINT_H

#include "symbolicc++.h"


class PointBase {

public:
    int m_dimension;
    Symbolic matrix;
    PointBase(int dimension);
    PointBase();

    ~PointBase();

    Symbolic operator[](int);
};

////////////////////////////////////////////////////////////////////////
namespace OneDimensional {
    class Point: public PointBase {
    public:
        Point();
        Point(double);
        ~Point();

        void operator=(Symbolic);
        void operator=(Point);
    };
}

////////////////////////////////////////////////////////////////////////
namespace TwoDimensional {
    class Point: public PointBase  {

    public:
        Point();
        Point(double, double);
        ~Point();

        void operator=(Symbolic);
        void operator=(Point);
    };
}

////////////////////////////////////////////////////////////////////////
namespace ThreeDimensional {
    class Point: public PointBase  {

    public:
        Point();
        Point(double, double, double);
        ~Point();

        void operator=(Symbolic);
        void operator=(Point);
    };
}

////////////////////////////////////////////////////////////////////////
union PointList {
    OneDimensional::Point OneDimensionalPoint;
    TwoDimensional::Point TwoDimensionalPoint;


};

#endif //NUMERICAL_COMPUTING_POINT_H
