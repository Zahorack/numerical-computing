//
// Created by zahorack on 2/22/20.
//

#ifndef NUMERICAL_COMPUTING_QUADRATICEQUATION_H
#define NUMERICAL_COMPUTING_QUADRATICEQUATION_H

#include "symbolicc++.h"
#include "ComplexNumber.h"

class QuadraticEquationResult {
public:
    ComplexNumber root1;
    ComplexNumber root2;

    QuadraticEquationResult(ComplexNumber r1, ComplexNumber r2):
        root1(r1),
        root2(r2)
    {
        root1.isValid = true;
        root2.isValid = true;
    };

    QuadraticEquationResult(ComplexNumber r1):
        root1(r1)
    {
        root1.isValid = true;
        root1.isValid = false;
    };
};

class QuadraticEquation {

    Symbolic m_equation;
    Symbolic m_variable;
public:
    QuadraticEquation(Symbolic, Symbolic);
    ~QuadraticEquation();

    QuadraticEquationResult solve();
};

#endif //NUMERICAL_COMPUTING_QUADRATICEQUATION_H
