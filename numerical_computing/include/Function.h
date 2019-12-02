//
// Created by zahorack on 11/5/19.
//

#ifndef NUMERICAL_COMPUTING_FUNCTION_H
#define NUMERICAL_COMPUTING_FUNCTION_H

#include "Point.h"
#include "symbolicc++.h"

static const Symbolic x("x"), y("y"), z("z");

namespace StationaryPoint {
enum Enum {
    Minimum = 0,
    Maximum,
    Saddle,
    Invalid,

    Size
};
}



class FunctionBase {

public:
    Symbolic m_symbolic;
    int m_dimension;

    FunctionBase(const Symbolic f, int dimension);
    ~FunctionBase();

    const Symbolic getSymbolic();
};

////////////////////////////////////////////////////////////////////////
namespace OneDimensional {

    class Function: public FunctionBase  {

        const Symbolic x;
    public:
        Function(const Symbolic f);
        ~Function();

        Symbolic value(Point);
        double value(double);
        Symbolic value(Symbolic, double);
        Symbolic value(Symbolic, Point);

        Symbolic gradient();
        Symbolic gradient(Point);
        double gradient(double);

        Symbolic hessian();
        Symbolic hessian(Point);

        StationaryPoint::Enum character(Point);
        bool isRising(Point);
        bool isFalling(Point);

    };
}

////////////////////////////////////////////////////////////////////////
namespace TwoDimensional {

    class Function: public FunctionBase  {

        const Symbolic x, y;
    public:
        Function(const Symbolic f);
        ~Function();

        Symbolic value(Point);
        Symbolic value(Symbolic, Point);

        Symbolic gradient();
        Symbolic gradient(Point);

        Symbolic hessian();
        Symbolic hessian(Point);

        StationaryPoint::Enum character(Point);

    };
}


////////////////////////////////////////////////////////////////////////
namespace ThreeDimensional {

    class Function: public FunctionBase  {

        const Symbolic x, y, z;
    public:
        Function(const Symbolic f);
        ~Function();

        Symbolic value(Point);
        Symbolic value(Symbolic, Point);

        Symbolic gradient();
        Symbolic gradient(Point);

        Symbolic hessian();
        Symbolic hessian(Point);

        StationaryPoint::Enum character(Point);
    };
}


#endif //NUMERICAL_COMPUTING_FUNCTION_H
