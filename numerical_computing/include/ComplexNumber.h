//
// Created by zahorack on 2/22/20.
//

#ifndef NUMERICAL_COMPUTING_COMPLEXNUMBER_H
#define NUMERICAL_COMPUTING_COMPLEXNUMBER_H


class ComplexNumber {
public:
    bool isValid;

    double real;
    double imaginary;

    ComplexNumber(double, double);
    ComplexNumber();
    ~ComplexNumber();
};

#endif //NUMERICAL_COMPUTING_COMPLEXNUMBER_H
