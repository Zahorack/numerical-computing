//
// Created by zahorack on 2/22/20.
//

#include "ComplexNumber.h"


ComplexNumber::ComplexNumber(double re, double im):
    real(re),
    imaginary(im),
    isValid(true)
{}

ComplexNumber::ComplexNumber():
    real(0),
    imaginary(0),
    isValid(false)
{}

ComplexNumber::~ComplexNumber()
{}