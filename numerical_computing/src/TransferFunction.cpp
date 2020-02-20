//
// Created by zahorack on 2/20/20.
//

#include "TransferFunction.h"

TransferFunction::TransferFunction(Symbolic num, Symbolic den):
    numerator(num),
    denominator(den),
    function(num/den)
{
    //cout<<function;
}

TransferFunction::~TransferFunction()
{};
