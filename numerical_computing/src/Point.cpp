//
// Created by zahorack on 11/5/19.
//

#include "Point.h"

PointBase::PointBase(int dimension):
    m_dimension(dimension)
{}

PointBase::PointBase():
    m_dimension(0)
{}

PointBase::~PointBase() {}


Symbolic PointBase::operator[](int at)
{
    return matrix.column(at);
}

Symbolic PointBase::operator+(Symbolic a)
{
    Symbolic sum;
    sum = matrix + a;

    return sum;
}


////////////////////////////////////////////////////////////////////////
namespace OneDimensional {

    Point::Point():
            PointBase(1)
    {
        matrix = (static_cast<Symbolic>(0));
    }

    Point::Point(double x):
        PointBase(1)
    {
        matrix = (static_cast<Symbolic>(x));
    }

    Point::~Point() {}


    void Point::operator=(Point point)
    {
        matrix = point.matrix;
    }

    void Point::operator=(Symbolic sym)
    {
        matrix = sym;
    }

}

////////////////////////////////////////////////////////////////////////
namespace TwoDimensional {

    Point::Point():
            PointBase(2)
    {
        matrix = (static_cast<Symbolic>(0), static_cast<Symbolic>(0));
    }

    Point::Point(double x, double y):
            PointBase(2)
    {
        matrix = (static_cast<Symbolic>(x), static_cast<Symbolic>(y));
    }

    Point::~Point() {}


    void Point::operator=(Point point)
    {
        if(point.matrix.columns() != m_dimension) {
            if(point.matrix.rows() == m_dimension) {
                matrix = point.matrix.transpose();
                cout<<"!! Warning !! - implicit Point matrix transpose\n";
            }
            else
                cout<<"!!! Error !!! - Point matrix out of dimension\n";
        }
        else
            matrix = point.matrix;
    }

    void Point::operator=(Symbolic sym)
    {
        if(sym.columns() != m_dimension) {
            if(sym.rows() == m_dimension) {
                matrix = sym.transpose();
                cout<<"!! Warning !! - implicit Point matrix transpose\n";
            }
            else
                cout<<"!!! Error !!! - Point matrix out of dimension\n";
        }
        else
            matrix = sym;
    }

}

////////////////////////////////////////////////////////////////////////
namespace ThreeDimensional {

    Point::Point():
            PointBase(3)
    {
        matrix = (static_cast<Symbolic>(0), static_cast<Symbolic>(0), static_cast<Symbolic>(0));
    }


    Point::Point(double x, double y, double z):
            PointBase(3)
    {
        matrix = (static_cast<Symbolic>(x), static_cast<Symbolic>(y), static_cast<Symbolic>(z));
    }

    Point::~Point() {}


    void Point::operator=(Point point) {
        if(point.matrix.columns() != m_dimension) {
            if(point.matrix.rows() == m_dimension) {
                matrix = point.matrix.transpose();
                cout<<"!! Warning !! - implicit Point matrix transpose\n";
            }
            else
                cout<<"!!! Error !!! - Point matrix out of dimension\n";
        }
        else
            matrix = point.matrix;
    }

    void Point::operator=(Symbolic sym)
    {
        if(sym.columns() != m_dimension) {
            if(sym.rows() == m_dimension) {
                matrix = sym.transpose();
                cout<<"!! Warning !! - implicit Point matrix transpose\n";
            }
            else
                cout<<"!!! Error !!! - Point matrix out of dimension\n";
        }
        else
            matrix = sym;
    }

}