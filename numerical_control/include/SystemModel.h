//
// Created by zahorack on 2/20/20.
//

#ifndef NUMERICAL_COMPUTING_SYSTEMMODEL_H
#define NUMERICAL_COMPUTING_SYSTEMMODEL_H

#include "TransferFunction.h"

namespace FirstOrder {
    class SystemModel {

        TransferFunction m_tf;
        double m_gain;

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
#endif //NUMERICAL_COMPUTING_SYSTEMMODEL_H
