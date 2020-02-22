//
// Created by zahorack on 2/22/20.
//

#include "QuadraticEquation.h"


QuadraticEquation::QuadraticEquation(Symbolic eq, Symbolic var):
    m_equation(eq),
    m_variable(var)
{
}

QuadraticEquation::~QuadraticEquation()
{}

QuadraticEquationResult QuadraticEquation::solve()
{
    double a = toDouble(df(df(m_equation, m_variable), m_variable)/Symbolic(2));
    double b = toDouble(Symbolic(df(m_equation, m_variable).subst(m_variable == 1)) - Symbolic(a*2));
    double c = toDouble(m_equation.subst(m_variable == 0));

//    cout<<"a:"<<a<<"\n";
//    cout<<"b:"<<b<<"\n";
//    cout<<"c:"<<c<<"\n";

    double D = b*b - 4*a*c;

    if(D > 0) {
        ComplexNumber root1, root2;
        root1.real = (-b + sqrt(D)) / (2 * a);
        root2.real = (-b - sqrt(D)) / (2 * a);

        return QuadraticEquationResult(root1, root2);
    }
    else if (D == 0) {
        ComplexNumber root1;
        root1.real = (-b)/(2*a);

        return QuadraticEquationResult(root1);
    }
    else {
        ComplexNumber temp;
        temp.real = (-b)/(2 * a);
        temp.imaginary = sqrt(-D)/(2 * a);

        return QuadraticEquationResult(ComplexNumber(temp.real, temp.imaginary), ComplexNumber(temp.real, -temp.imaginary));
    }
}