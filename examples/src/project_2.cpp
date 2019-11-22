//
// Created by zahorack on 11/5/19.
//

#include "project_2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <boost/tuple/tuple.hpp>

#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"

#include "Function.h"

namespace examples {
    namespace projectTwo {
        void test()
        {
            cout<<"projectTwo";

            static const Symbolic x("x"), y("y");
            static const Symbolic F = x*x*x + 2*y*y;

            TwoDimensional::Point point(2.0, 3.0);
            TwoDimensional::Function func(F);

            cout <<func.getSymbolic()<<"\n";
            cout <<func.value(point) << "\n";
            cout <<func.gradient()<<"\n";
            cout <<"Gradient at "<<func.gradient(point)<<"\n";
            cout <<"Hessian "<<func.hessian()<<"\n";
            cout <<"Hessian at"<<func.hessian(point)<<"\n";
        }
    }
}
