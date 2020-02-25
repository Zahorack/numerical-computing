//
// Created by zahorack on 2/24/20.
//

#ifndef NUMERICAL_COMPUTING_LINEAREQUATIONSSYSTEM_H
#define NUMERICAL_COMPUTING_LINEAREQUATIONSSYSTEM_H

#include "symbolicc++.h"



namespace OneDimensional {
    class LinearEquationsSystemResult {
        double root1;
    };

    class LinearEquationsSystem {

        Symbolic m_equation;
        Symbolic m_variable;
    public:
        LinearEquationsSystem(Symbolic);
        ~LinearEquationsSystem();

        LinearEquationsSystemResult solve();
    };
}

namespace TwoDimensional {
    class LinearEquationsSystemResult {
        double root1;
        double root2;
    };

    class LinearEquationsSystem {

        Symbolic m_equations[2];
        Symbolic m_variables[2];
    public:
        LinearEquationsSystem(Symbolic, Symbolic);
        ~LinearEquationsSystem();

        LinearEquationsSystemResult solve();
    };
}

namespace ThreeDimensional {
    class LinearEquationsSystemResult {
    public:
        LinearEquationsSystemResult(double a, double b, double c):
            root1(a), root2(b), root3(c)
        {};
        double root1;
        double root2;
        double root3;
    };

    class LinearEquationsSystem {

        Symbolic m_equations[3];
        Symbolic m_variables[3];

        Symbolic m_leftMatrix, m_rightMatrix;
    public:
        LinearEquationsSystem(Symbolic, Symbolic);
        LinearEquationsSystem(Symbolic, Symbolic, Symbolic, Symbolic, Symbolic, Symbolic);
        ~LinearEquationsSystem();

        Symbolic getRightMatrix(){return m_rightMatrix;}
        Symbolic getLeftMatrix(){return m_leftMatrix;}

        LinearEquationsSystemResult solve();
    };
}

#endif //NUMERICAL_COMPUTING_LINEAREQUATIONSSYSTEM_H
