//
// Created by zahorack on 11/5/19.
//

#include "Function.h"

FunctionBase::FunctionBase(const Symbolic f, int dimension):
    m_function(f),
    m_dimension(dimension)
{}

FunctionBase::~FunctionBase() {}


const Symbolic FunctionBase::get()
{
    return m_function;
}


////////////////////////////////////////////////////////////////////////
namespace OneDimensional {
    Function::Function(const Symbolic f) :
            FunctionBase(f, 1),
            x("x")
    {}

    Function::~Function()
    {}

    Symbolic Function::value(Point at)
    {
        Symbolic result = m_function.subst(x == at[0]);
        return result;
    }

    Symbolic Function::value(Symbolic func, Point at)
    {
        Symbolic result = func.subst(x == at[0]);
        return result;
    }

    Symbolic Function::gradient()
    {
        Symbolic dx = df(m_function, x);

        Symbolic gradient = (dx);
        return gradient;
    }

    Symbolic Function::gradient(Point at)
    {
        return value(gradient(), at);
    }

    Symbolic Function::hessian()
    {
        Symbolic dx = gradient();
        Symbolic h = df(dx, x);
        return h;
    }

    Symbolic Function::hessian(Point at)
    {
        return value(hessian(), at);
    }
}


////////////////////////////////////////////////////////////////////////
namespace TwoDimensional {

    Function::Function(const Symbolic f) :
            FunctionBase(f, 2),
            x("x"), y("y")
    {}

    Function::~Function()
    {}

    Symbolic Function::value(Point at)
    {
        Symbolic result = m_function.subst(x == at[0]);
        result = result.subst(y == at[1]);
        return result;
    }

    Symbolic Function::value(Symbolic func, Point at)
    {
        Symbolic result = func.subst(x == at[0]);
        result = result.subst(y == at[1]);
        return result;
    }

    Symbolic Function::gradient()
    {
        Symbolic dx = df(m_function, x);
        Symbolic dy = df(m_function, y);

        Symbolic gradient = (dx, dy);

        return gradient;
    }

    Symbolic Function::gradient(Point at)
    {
        return value(gradient(), at);
    }

    Symbolic Function::hessian()
    {
        Symbolic dx = gradient().column(0);
        Symbolic dy = gradient().column(1);

        Symbolic h =   ((df(dx, x), df(dx, y)),
                        (df(dy, x), df(dy, y)));
        return h;
    }

    Symbolic Function::hessian(Point at)
    {
        return value(hessian(), at);
    }
}


////////////////////////////////////////////////////////////////////////
namespace ThreeDimensional {

    Function::Function(const Symbolic f) :
            FunctionBase(f, 3),
            x("x"), y("y"), z("z")
    {}

    Function::~Function()
    {}

    Symbolic Function::value(Point at)
    {
        Symbolic result = m_function.subst(x == at[0]);
        result = result.subst(y == at[1]);
        result = result.subst(z == at[2]);
        return result;
    }

    Symbolic Function::value(Symbolic func, Point at)
    {
        Symbolic result = func.subst(x == at[0]);
        result = result.subst(y == at[1]);
        result = result.subst(z == at[2]);
        return result;
    }

    Symbolic Function::gradient()
    {
        Symbolic dx = df(m_function, x);
        Symbolic dy = df(m_function, y);
        Symbolic dz = df(m_function, z);

        Symbolic gradient = (dx, dy, dz);

        return gradient;
    }

    Symbolic Function::gradient(Point at)
    {
        return value(gradient(), at);
    }

    Symbolic Function::hessian()
    {
        Symbolic dx = gradient().column(0);
        Symbolic dy = gradient().column(1);
        Symbolic dz = gradient().column(2);

        Symbolic h =  ( (df(dx, x), df(dx, y), df(dx, z)),
                        (df(dy, x), df(dy, y), df(dx, z)),
                        (df(dz, x), df(dz, y), df(dz, y)) );
        return h;
    }

    Symbolic Function::hessian(Point at)
    {
        return value(hessian(), at);
    }
}
