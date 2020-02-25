//
// Created by zahorack on 2/24/20.
//

#include "LinearEquationsSystem.h"

static const Symbolic x("x"), y("y"), z("z");


////////////////////////////////////////////////////////////////////////
namespace ThreeDimensional {
    LinearEquationsSystem::LinearEquationsSystem(Symbolic eq1, Symbolic eq2, Symbolic eq3,
                                                Symbolic var1, Symbolic var2, Symbolic var3) {
        m_equations[0] = eq1;
        m_equations[1] = eq2;
        m_equations[2] = eq3;

        m_variables[0] = var1;
        m_variables[1] = var2;
        m_variables[2] = var3;

        //right side of linear equations system is where all variables x,y,z are equal zero - constants
        Symbolic right = (
                Symbolic((-1)*m_equations[0].subst(var1 == 0).subst(var2 == 0). subst(var3 == 0)),
                Symbolic((-1)*m_equations[1].subst(var1 == 0).subst(var2 == 0). subst(var3 == 0)),
                Symbolic((-1)*m_equations[2].subst(var1 == 0).subst(var2 == 0). subst(var3 == 0))
        );
        //to get constant of left side linear equations system we derivate by variables
        Symbolic left = (
            (df(m_equations[0], m_variables[0]), df(m_equations[0], m_variables[1]), df(m_equations[0], m_variables[2])),
            (df(m_equations[1], m_variables[0]), df(m_equations[1], m_variables[1]), df(m_equations[1], m_variables[2])),
            (df(m_equations[2], m_variables[0]), df(m_equations[2], m_variables[1]), df(m_equations[2], m_variables[2]))
        );

        m_leftMatrix =left;
        m_rightMatrix = right;

        if(m_rightMatrix.columns() > 1) {
            m_rightMatrix = m_rightMatrix.transpose();
        }

    };


    LinearEquationsSystem::LinearEquationsSystem(Symbolic left, Symbolic right):
        m_leftMatrix(left),
        m_rightMatrix(right)
    {
        //make sure matrix is vertical
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
        cout<<"m_rightMatrix:"<<m_rightMatrix<<"\n";
        cout<<"m_leftMatrix:"<<m_leftMatrix<<"\n";
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

        double r1,r2,r3 = 0;

        if(toDouble(D) != 0) {
            r1 = toDouble(D1 / D);
            r2 = toDouble(D2 / D);
            r3 = toDouble(D3 / D);
        }
        return LinearEquationsSystemResult(r1, r2, r3);
    }

}
////////////////////////////////////////////////////////////////////////