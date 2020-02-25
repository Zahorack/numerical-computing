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
//TODO:
// Complex number roots / poles ??

namespace SecondOrder {
    SystemModel::SystemModel(TransferFunction tf) :
            m_tf(tf)
    {
        //initial correction
        double a = toDouble(df(df(m_tf.denominator, s), s)/Symbolic(2));
        if(a != 0) {
            m_tf.numerator /= a;
            m_tf.denominator /= a;
        }
    }

    SystemModel::~SystemModel() {};

/*
 *     @Normal form for Second order systems looks like
 *     ________K________
 *     (T1s + 1)(T2s + 1)
 */
    TransferFunction SystemModel::normalForm() {

    }

    double SystemModel::getGain() {
        double divider1 = 1, divider2 = 1;

        QuadraticEquationResult roots = getRoots();

        if(roots.root1.isValid && roots.root1.real != 0)
            divider1 = roots.root1.real;

        if(roots.root2.isValid && roots.root2.real != 0)
            divider2 = roots.root2.real;

        return double(toDouble(m_tf.numerator)/(divider1*divider2));
    }

    void SystemModel::getTimeConstant(double *T1, double *T2) {

        QuadraticEquationResult poles = getPoles();

        if(poles.root1.isValid && poles.root1.real != 0)
            *T1 = 1/getPoles().root1.real;
        if(poles.root2.isValid && poles.root2.real != 0)
            *T2 = 1/getPoles().root2.real;
    }

/*
 *  @Root "s" of denominator normal form First order
 *
 */
    QuadraticEquationResult SystemModel::getRoots() {

        QuadraticEquation equation(m_tf.denominator, Symbolic(s));

        return QuadraticEquationResult(equation.solve());
    }

    QuadraticEquationResult SystemModel::getPoles() {
        return QuadraticEquationResult(getRoots());
    }

    bool SystemModel::isStable() {

        QuadraticEquationResult poles = getPoles();

        if(poles.root1.real < 0 && poles.root2.real < 0) {
            return true;
        }
        return false;
    }

    TransferFunction SystemModel::rootsForm() {

        QuadraticEquationResult roots = getRoots();


        double a = toDouble(df(df(m_tf.denominator, s), s)/Symbolic(2));

        return TransferFunction(m_tf.numerator, Symbolic(a*(s - (roots.root1.real + roots.root1.imaginary*i))*
                                                                 (s - (roots.root2.real + roots.root2.imaginary*i))));
    }

    TransferFunction SystemModel::transitionForm() {
        return TransferFunction(rootsForm().numerator, rootsForm().denominator * s);
    }

    /*
     *  @Second order partial fractions problem
     *
     *  numa*^2 + numb*s + numc         A      B     C
     *  ________________________    =  ___  + ___ + ___
     *  dena*s^2 + denb*s + denc       denA   denB  denC
     *
     *  @task: To find coefficients A, B, C
     */
    //TODO:
    //Maybe matrix implemented solution
    ThreeDimensional::LinearEquationsSystemResult SystemModel::partialFractionsSolution() {

        QuadraticEquationResult roots = getRoots();
        Symbolic denA = Symbolic(s);
        Symbolic denB = (s - (roots.root1.real + roots.root1.imaginary*i));
        Symbolic denC = (s - (roots.root2.real + roots.root2.imaginary*i));
        Symbolic num = m_tf.numerator;
        Symbolic den = m_tf.denominator;

        Symbolic numa = toDouble(df(df(num, s), s)/Symbolic(2));
        Symbolic numb = toDouble(Symbolic(df(num, s).subst(s == 1)) - Symbolic(numa*2));
        Symbolic numc = toDouble(num.subst(s == 0));


        Symbolic x("x"), y("y"), z("z");
        Symbolic leftEquation = x*denB*denC + y*denA*denC + z*denA*denB;
        cout<<leftEquation;

        Symbolic a = (df(df(leftEquation, s), s)/Symbolic(2));
        Symbolic b = (Symbolic(df(leftEquation, s).subst(s == 1)) - Symbolic(a*2));
        Symbolic c = (leftEquation.subst(s == 0));

        Symbolic leftMatrix = ( (df(a, x), df(a, y), df(a, z)),
                                (df(b, x), df(b, y), df(b, z)),
                                (df(c, x), df(c, y), df(c, z))
                             );
        Symbolic rightMatrix = (numa, numb, numc);

        ThreeDimensional::LinearEquationsSystem system(leftMatrix, rightMatrix);
        ThreeDimensional::LinearEquationsSystemResult result(system.solve());

        cout<<"\nx: "<<result.root1<<"\n";
        cout<<"y: "<<result.root2<<"\n";
        cout<<"z: "<<result.root3<<"\n";

        return result;

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