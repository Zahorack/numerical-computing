//
// Created by zahorack on 2/20/20.
//

#ifndef NUMERICAL_COMPUTING_TRANSFERFUNCTION_H
#define NUMERICAL_COMPUTING_TRANSFERFUNCTION_H

#include "symbolicc++.h"

static const Symbolic s("s");

class TransferFunction{
public:
    Symbolic function;
    Symbolic numerator, denominator;

    TransferFunction(Symbolic num, Symbolic den);
    ~TransferFunction();
};

#endif //NUMERICAL_COMPUTING_TRANSFERFUNCTION_H
