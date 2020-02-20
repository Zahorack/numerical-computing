//
// Created by zahorack on 2/20/20.
//

#ifndef NUMERICAL_COMPUTING_DIFFERENTIALEQUATION_H
#define NUMERICAL_COMPUTING_DIFFERENTIALEQUATION_H

#include "Function.h"

namespace FirstOrder {
    class DifferentialEquation {

        Symbolic s;
    public:

        DifferentialEquation(Symbolic, Symbolic, Symbolic);
        ~DifferentialEquation();

    };
}

#endif //NUMERICAL_COMPUTING_DIFFERENTIALEQUATION_H
