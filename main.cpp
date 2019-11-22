//
// Created by zahorack on 10/15/19.
//


#include "examples/include/lecture_1.h"
#include "examples/include/project_1.h"
#include "examples/include/project_2.h"

#include "optimization/include/NewtonRaphson.h"
#include "optimization/include/LevenbergMarquardt.h"
#include "symbolicc++.h"
#include "Plot.h"



static void project_one()
{
    static const Symbolic x("x"), y("y");
    using namespace TwoDimensional;
    Point StartPoint(1.5, 5.0);
    Function func(((x - 2)*(x - 2) + (y - x*x)*(y - x*x)));
    Plot::function(func.getSymbolic());

    Optimization::NewtonRaphson methodOne(func, StartPoint, 0.0001);
    methodOne.findMinimum();

    Optimization::LevenbergMarquardt methodTwo(func, StartPoint, 0.0001);
    methodTwo.findMinimum();

}

int main() {

//    examples::lectureOne::taskOne();
//    examples::lectureOne::taskTwo();
//    examples::lectureOne::taskThree();

//    examples::projectOne::NewtonRaphson();
//    examples::projectOne::LevenbergMarquardt();

//    examples::projectTwo::test();

    project_one();

    return 0;
}