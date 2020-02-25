//
// Created by zahorack on 10/15/19.
//


#include "examples/include/lecture_1.h"
#include "examples/include/project_1.h"
#include "examples/include/project_2.h"

#include "symbolicc++.h"
#include "optimization/include/NewtonRaphson.h"
#include "optimization/include/LevenbergMarquardt.h"
#include "optimization/include/NelderMead.h"
#include "optimization/include/GoldenSectionSearch.h"
#include "optimization/include/DavidonSearch.h"
#include "numerical_computing/include/Plot.h"
#include "numerical_computing/include/Function.h"
#include "numerical_computing/include/TransferFunction.h"
#include "numerical_control/include/SystemModel.h"
#include "QuadraticEquation.h"
#include "LinearEquationsSystem.h"



static void optimization_example()
{
   // static const Symbolic x("x"), y("y");
    using namespace TwoDimensional;
    Point StartPoint(1.5, 5.0);
    Function func(((x - 2)*(x - 2) + (y - x*x)*(y - x*x)));
    Plot::function(func.getSymbolic());

    Optimization::NewtonRaphson methodOne(func, StartPoint, 0.001);
    methodOne.findMinimum();

    Optimization::LevenbergMarquardt methodTwo(func, StartPoint, 0.01);
    methodTwo.findMinimum();

    Optimization::NelderMead methodThree(func, StartPoint, 0.05, 2.5);
    methodThree.findMinimum();
}

static void one_dimensional_problem()
{
    OneDimensional::Function func(x*x*x*x - 3*x*x*x + x +7 );

    Optimization::GoldenSectionSearch goldSel(func, 1, 3);
    goldSel.findMinimum();

    Optimization::DavidonSearch davidon(SearchMode::Minimization, func, 1, 3, 0.0001);
    davidon.findMinimum();
}


static void control_system_example()
{
    FirstOrder::SystemModel system(TransferFunction(1.5, (28*s + 0.3)));
    cout<<"Gain:"<<system.getGain()<<"\n";
    cout<<"Time:"<<system.getTimeConstant()<<"\n";
    cout<<"Roots:"<<system.getRoots()<<"\n";

    cout<<"transition func:"<<system.transitionFunction()<<"\n";
    cout<<"impulse func:"<<system.impulseFunction()<<"\n";

    Plot::systemModel(system);
}

static void quadratic_equations_example()
{
    QuadraticEquation equation(50*s*s -20*s + 100, Symbolic(s));
    QuadraticEquationResult result = equation.solve();

    if(result.root1.isValid) {
        cout << "root1: " << result.root1.real << " + " <<result.root1.imaginary << "i\n";
    }
    if(result.root2.isValid) {
        cout << "root2: " << result.root2.real << " + " <<result.root2.imaginary << "i\n";
    }
}

int main() {

//    examples::lectureOne::taskOne();
//    examples::lectureOne::taskTwo();
//    examples::lectureOne::taskThree();

//    optimization_example();
//    one_dimensional_problem();

//    TwoDimensional::Function myFunction((x - 2)*(x + 5) + y*y);
//    Plot::function(myFunction.getSymbolic());

//    control_system_example();


    SecondOrder::SystemModel system(TransferFunction(1, (0.1*s*s + 2.4*s + 8.0)));


//    cout<<"\n Gain:"<<system.getGain()<<"\n";

//    Symbolic left  = ((Symbolic(1),Symbolic(2),Symbolic(3)),
//                     (Symbolic(4),Symbolic(5),Symbolic(6)),
//                     (Symbolic(7),Symbolic(8),Symbolic(9)));
//
//    Symbolic right = (  (Symbolic(1)),
//                        (Symbolic(2)),
//                        (Symbolic(3)));
//
//    ThreeDimensional::LinearEquationsSystem system(left, right);
//    system.solve();

    return 0;
}