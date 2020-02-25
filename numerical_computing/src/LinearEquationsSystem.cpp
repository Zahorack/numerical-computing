//
// Created by zahorack on 2/24/20.
//

#include "LinearEquationsSystem.h"

static const Symbolic x("x"), y("y"), z("z");

namespace ThreeDimensional {

    LinearEquationsSystem::LinearEquationsSystem(Symbolic eq1, Symbolic eq2, Symbolic eq3) {
        m_equations[0] = eq1;
        m_equations[1] = eq2;
        m_equations[2] = eq3;

        m_variables[0] = x;
        m_variables[1] = y;
        m_variables[2] = z;
    };

    LinearEquationsSystem::LinearEquationsSystem(Symbolic eq1, Symbolic eq2, Symbolic eq3,
                                                Symbolic var1, Symbolic var2, Symbolic var3) {
        m_equations[0] = eq1;
        m_equations[1] = eq2;
        m_equations[2] = eq3;

        m_variables[0] = var1;
        m_variables[1] = var2;
        m_variables[2] = var3;
    };

    LinearEquationsSystem::LinearEquationsSystem(Symbolic left, Symbolic right):
        m_leftMatrix(left),
        m_rightMatrix(right)
    {
        if(m_rightMatrix.columns() > 1) {
            m_rightMatrix = m_rightMatrix.transpose();
        }

    };

    LinearEquationsSystem::~LinearEquationsSystem()
    {};

    /*
     *  @Numerical solution based on Cramer's rule
     */
    LinearEquationsSystemResult LinearEquationsSystem::solve() {

        Symbolic l = m_leftMatrix;
        Symbolic r = m_rightMatrix;

        Symbolic D = det(l);

        Symbolic D1 = det(( (r.row(0).column(0), l.row(0).column(1), l.row(0).column(2)),
                             (r.row(1).column(0), l.row(1).column(1), l.row(1).column(2)),
                             (r.row(2).column(0), l.row(2).column(1), l.row(2).column(2))));

        Symbolic D2 = det(( (l.row(0).column(0), r.row(0).column(0), l.row(0).column(2)),
                             (l.row(1).column(0), r.row(1).column(0), l.row(1).column(2)),
                             (l.row(2).column(0), r.row(2).column(0), l.row(2).column(2))));

        Symbolic D3 = det( ((l.row(0).column(0), l.row(0).column(1), r.row(0).column(0)),
                             (l.row(1).column(0), l.row(1).column(1), r.row(1).column(0)),
                             (l.row(2).column(0), l.row(2).column(1), r.row(2).column(0))));

        return LinearEquationsSystemResult(toDouble(D1/D), toDouble(D2/D), toDouble(D3/D));
    }

}
