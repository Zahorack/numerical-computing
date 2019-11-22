//
// Created by zahorack on 11/5/19.
//

#ifndef NUMERICAL_COMPUTING_FUNCTION_H
#define NUMERICAL_COMPUTING_FUNCTION_H

#include "Point.h"
#include "symbolicc++.h"

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
        Symbolic value(Symbolic, Point);

        Symbolic gradient();
        Symbolic gradient(Point);

        Symbolic hessian();
        Symbolic hessian(Point);
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
    };
}


#endif //NUMERICAL_COMPUTING_FUNCTION_H
