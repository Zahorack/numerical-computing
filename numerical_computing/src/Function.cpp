//
// Created by zahorack on 11/5/19.
//

#include <iostream>
#include "Function.h"
#include "string.h"

FunctionBase::FunctionBase(const Symbolic f, int dimension):
    m_symbolic(f),
    m_dimension(dimension)
{}

FunctionBase::~FunctionBase()
{}


const Symbolic FunctionBase::getSymbolic()
{
    return m_symbolic;
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
        Symbolic result = m_symbolic.subst(x == at[0]);
        return result;
    }

    double Function::value(double at)
    {
        Symbolic result = m_symbolic.subst(x == at);
        return result;
    }

    Symbolic Function::value(Symbolic func, Point at)
    {
        Symbolic result = func.subst(x == at[0]);
        return result;
    }

    Symbolic Function::gradient()
    {
        Symbolic dx = df(m_symbolic, x);

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

    StationaryPoint::Enum Function::character(Point stationaryPoint)
    {
        double determinant = toDouble(det(hessian(stationaryPoint)));

        if(determinant > 0) /* Kladne definitny hessian */
            return StationaryPoint::Minimum;
        else if(determinant < 0) /* Zaporne definitny hessian */
            return StationaryPoint::Maximum;

        /* Nedefinitny hessian */
        return StationaryPoint::Saddle;
    }

    bool Function::isRising(Point at)
    {
        if(toDouble(gradient(at)) > 0) {
            return true;
        }
        return false;
    }

    bool Function::isFalling(Point at)
    {
        if(toDouble(gradient(at)) < 0) {
            return true;
        }
        return false;
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
        Symbolic result = m_symbolic.subst(x == at[0]);
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
        Symbolic dx = df(m_symbolic, x);
        Symbolic dy = df(m_symbolic, y);

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

    StationaryPoint::Enum Function::character(Point stationaryPoint)
    {
        double determinant = toDouble(det(hessian(stationaryPoint)));
        double subDeterminant = toDouble((hessian(stationaryPoint).row(0).column(0)));

        if(determinant > 0 && subDeterminant > 0) { /* Kladne definitny hessian */
            cout<<"Stationary point "<<stationaryPoint.matrix<< "is a Locally minimum of function";
            return StationaryPoint::Minimum;
        }
        else if(determinant > 0 && subDeterminant < 0) { /* Zaporne definitny hessian */
            cout<<"Stationary point "<<stationaryPoint.matrix<< "is a Locally maximum of function";
            return StationaryPoint::Maximum;
        }

        /* Nedefinitny hessian */
        cout<<"Stationary point "<<stationaryPoint.matrix<< "is a Saddle point of function";
        return StationaryPoint::Saddle;
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
        Symbolic result = m_symbolic.subst(x == at[0]);
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
        Symbolic dx = df(m_symbolic, x);
        Symbolic dy = df(m_symbolic, y);
        Symbolic dz = df(m_symbolic, z);

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

    StationaryPoint::Enum Function::character(Point stationaryPoint)
    {
        Symbolic hess = hessian(stationaryPoint);

        cout<<"Hessian\n"<<hessian();
        cout<<"Hessian at point\n"<<hessian(stationaryPoint);

        double determinant = toDouble(det(hess));

        Symbolic subHessian =   ((hess.row(0).column(0), hess.row(0).column(1)),
                                (hess.row(1).column(0), hess.row(1).column(1)));

        double subDeterminant = toDouble(det(subHessian));
        double terDeterminant = toDouble((hess.row(0).column(0)));

        if(determinant > 0 && subDeterminant > 0 && terDeterminant > 0) { /* Kladne definitny hessian */
            cout<<"Stationary point "<<stationaryPoint.matrix<< "is a Locally minimum of function";
            return StationaryPoint::Minimum;
        }
        else if(determinant < 0 && subDeterminant > 0 && terDeterminant < 0) {/* Zaporne definitny hessian */
            cout<<"Stationary point "<<stationaryPoint.matrix<< "is a Locally maximum of function";
            return StationaryPoint::Maximum;
        }

        /* Nedefinitny hessian */
        cout<<"Stationary point "<<stationaryPoint.matrix<< "is a Saddle point of function";
        return StationaryPoint::Saddle;

    }
}
