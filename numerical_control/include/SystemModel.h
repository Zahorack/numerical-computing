//
// Created by zahorack on 2/20/20.
//

#ifndef NUMERICAL_COMPUTING_SYSTEMMODEL_H
#define NUMERICAL_COMPUTING_SYSTEMMODEL_H

#include "TransferFunction.h"
#include "QuadraticEquation.h"
#include "LinearEquationsSystem.h"

static const Symbolic s("s");

////////////////////////////////////////////////////////////////////////
namespace FirstOrder {
    class SystemModel {

        TransferFunction m_tf;

        TransferFunction normalForm();
        TransferFunction rootsForm();
        Symbolic partialFractionsSolution(double *, double *);

    public:
        SystemModel(TransferFunction tf);

        ~SystemModel();

        double getGain();
        double getTimeConstant();
        double getRoots();
        double getPoles();
        double getZeros();
        bool isStable();
        TransferFunction transitionForm();

        Symbolic transitionFunction();
        Symbolic impulseFunction();

    };
}

////////////////////////////////////////////////////////////////////////
namespace SecondOrder {
    class SystemModel {

        TransferFunction m_tf;

        TransferFunction normalForm();
        TransferFunction rootsForm();
    public:ThreeDimensional::LinearEquationsSystemResult partialFractionsSolution();

    public:
        SystemModel(TransferFunction tf);

        ~SystemModel();

        double getGain();
        void getTimeConstant(double *, double *);
        QuadraticEquationResult getRoots();
        QuadraticEquationResult getPoles();
        double getZeros();
        bool isStable();
        TransferFunction transitionForm();

        Symbolic transitionFunction();
        Symbolic impulseFunction();

    };
}

#endif //NUMERICAL_COMPUTING_SYSTEMMODEL_H
