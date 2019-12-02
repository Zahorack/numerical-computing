//
// Created by zahorack on 10/15/19.
//


#include "examples/include/lecture_1.h"
#include "examples/include/project_1.h"
#include "examples/include/project_2.h"

#include "optimization/include/NewtonRaphson.h"
#include "optimization/include/LevenbergMarquardt.h"
#include "optimization/include/NelderMead.h"
#include "optimization/include/GoldenSectionSearch.h"
#include "optimization/include/DavidonSearch.h"
#include "symbolicc++.h"
#include "Plot.h"

#include "Function.h"




static void project_one()
{
    static const Symbolic x("x"), y("y");
    using namespace TwoDimensional;
    Point StartPoint(1.5, 5.0);
    Function func(((x - 2)*(x - 2) + (y - x*x)*(y - x*x)));
    //Plot::function(func.getSymbolic());

//    Optimization::NewtonRaphson methodOne(func, StartPoint, 0.001);
//    methodOne.findMinimum();

//    Optimization::LevenbergMarquardt methodTwo(func, StartPoint, 0.01);
//    methodTwo.findMinimum();
//
    Optimization::NelderMead methodThree(func, StartPoint, 0.05, 2.5);
    methodThree.findMinimum();

}



int main() {

//    examples::lectureOne::taskOne();
//    examples::lectureOne::taskTwo();
//    examples::lectureOne::taskThree();

//    examples::projectOne::NewtonRaphson();
//    examples::projectOne::LevenbergMarquardt();

//    examples::projectTwo::test();

    project_one();


//    OneDimensional::Function func(x*x*x*x - 3*x*x*x + x +7 );
//
//    Optimization::GoldenSectionSearch zlatyrez(func, 1, 3);
//    zlatyrez.findMinimum();
//
//    Optimization::DavidonSearch davidon(SearchMode::Minimization, func, 1, 3, 0.0001);
//    davidon.findMinimum();

    return 0;
}