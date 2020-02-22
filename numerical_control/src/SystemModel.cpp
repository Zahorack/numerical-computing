//
// Created by zahorack on 2/20/20.
//

#include "../include/SystemModel.h"
#include "QuadraticEquation.h"

////////////////////////////////////////////////////////////////////////
namespace FirstOrder {
    SystemModel::SystemModel(TransferFunction tf) :
            m_tf(tf) {}

    SystemModel::~SystemModel() {};

/*
 *     @Normal form for First order system looks like
 *     ___K__
 *     Ts + 1
 */
    TransferFunction SystemModel::normalForm() {
        Symbolic divider = m_tf.denominator.subst(s == 0);

        if (toDouble(divider) != 0) {
            return TransferFunction(m_tf.numerator / divider, m_tf.denominator / divider);
        } else
            return m_tf;
    }

    double SystemModel::getGain() {
        return toDouble(normalForm().numerator);
    }

    double SystemModel::getTimeConstant() {
        return toDouble(normalForm().denominator.subst(s == 1) - Symbolic(1));
    }

/*
 *  @Root "s" of denominator normal form First order
 *  Ts + 1 = 0
 *  s = -1/T
 */

    double SystemModel::getRoots() {
        return toDouble(-1 / getTimeConstant());
    }

    double SystemModel::getPoles() {
        return getRoots();
    }

    bool SystemModel::isStable() {
        return (getRoots() < 0);
    }

    TransferFunction SystemModel::rootsForm() {
        Symbolic divider = df(m_tf.denominator, s);

        return TransferFunction(m_tf.numerator / divider, Symbolic(s - Symbolic(getRoots())));
    }

    TransferFunction SystemModel::transitionForm() {
        return TransferFunction(rootsForm().numerator, rootsForm().denominator * s);
    }

    Symbolic SystemModel::partialFractionsSolution(double *A, double *B) {
        Symbolic denA = Symbolic(s);
        Symbolic denB = rootsForm().denominator;
        Symbolic num = rootsForm().numerator;
        Symbolic a, b;

        a = num.subst(s == 0) / denB.subst(s == 0);
        b = df(num, s) - a;

        *A = toDouble(a);
        *B = toDouble(b);

        return (a / denA + b / denB);
    }

/*
 *  @Using Inverse Laplace transform L^(-1)
 *
 *  1.) L^(-1){x/s} = x
 *  2.) L^(-1){x/(s + y)} = x*e^(-y*t)
 */
    Symbolic SystemModel::transitionFunction() {
        double A, B;
        partialFractionsSolution(&A, &B);

        return Symbolic(A + B * exp(getRoots() * Symbolic("t")));
    }

    Symbolic SystemModel::impulseFunction() {
        return Symbolic(rootsForm().numerator * exp(getRoots() * Symbolic("t")));
    }

}

////////////////////////////////////////////////////////////////////////
/*Not implemented yet*/

namespace SecondOrder {
    SystemModel::SystemModel(TransferFunction tf) :
            m_tf(tf) {}

    SystemModel::~SystemModel() {};

/*
 *     @Normal form for Second order systems looks like
 *     ________K________
 *     (T1s + 1)(T2s + 1)
 */
    TransferFunction SystemModel::normalForm() {

    }

    double SystemModel::getGain() {

    }

    double SystemModel::getTimeConstant() {

    }

/*
 *  @Root "s" of denominator normal form First order
 *
 */

    void SystemModel::getRoots(double *x1, double *x2) {

        QuadraticEquation equation(m_tf.denominator, Symbolic(s));

        QuadraticEquationResult result = equation.solve();

    }

    double SystemModel::getPoles() {

    }

    bool SystemModel::isStable() {

    }

    TransferFunction SystemModel::rootsForm() {
        double x1, x2;
        getRoots(&x1, &x2);

        double a = toDouble(df(df(m_tf.denominator, s), s)/Symbolic(2));

        return TransferFunction(m_tf.numerator, Symbolic(a*(s - x2)*(s - x1)));
    }

    TransferFunction SystemModel::transitionForm() {

    }

    Symbolic SystemModel::partialFractionsSolution(double *A, double *B) {

    }

/*
 *  @Using Inverse Laplace transform L^(-1)
 *
 *  1.) L^(-1){x/s} = x
 *  2.) L^(-1){x/(s + y)} = x*e^(-y*t)
 */
    Symbolic SystemModel::transitionFunction() {

    }

    Symbolic SystemModel::impulseFunction() {

    }

}