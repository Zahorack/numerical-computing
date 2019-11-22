//
// Created by zahorack on 10/29/19.
//
#include "project_1.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/tuple/tuple.hpp>

#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"

#include "Point.h"
#include "Function.h"

/*
%   Subject:    Optimalisation of processes in mechatronics
%   Project:    Gradeint optimalisation methods
%   Author:     Bc. Oliver Hollý

%   Task: Find minimum of purpose function: f(x1,x2) = (x1 - 2)^2 + (x2 - x1^2)^2
%       a.) By Nelder and Mead method (length of the edge of the starting complex = 2.5, accuracy = 0.05)
%       b.) By Newton and Raphson method
%       c.) Bz Levenberg Marquardt method
%       Consider following:
%           <> alfa = 8, c = 4
%           <> sarting point [1.5, 5], termination condition in b.), c.)
%           <> accuracy = d = g1^2 + g2^2 <= 0.001, when[g1, g2] = gradient(f).
*/

static double toDouble(Symbolic sym)
{
return static_cast<double>(sym);
}

namespace examples {
    namespace projectOne {

        static void visualisations() {
            std::string funkcia = "((x - 2)*(x - 2) + (y - x*x)*(y - x*x))";
            Gnuplot gp("gnuplot -persist");

            gp<<("set xrange [-5:5]\n");
            gp<<("set yrange [-5:5]\n");
            gp<<("set pm3d at b\n");
            gp<<("set ticslevel 0.8\n");
            gp<<("set isosample 40,40\n");
            gp<<("set cntrparam levels 15\n");
            gp<<("set samples 20\n");
            gp<<("set isosamples 21\n");
            gp<<("set view 60, 30, 0.85, 1.1\n");
            gp<<("set key at screen 1.0, 0.9\n");
            gp<<("set style textbox opaque noborder margins 0.5, 0.5\n");
            gp<<("set cntrparam levels incr -10,1,10\n");
            gp<<("set contour\n");

            gp<<("splot ");
            gp<<((funkcia));
            gp<<("\n");
        }

        static const float Precision   = 0.001;
        static const float MaxCycleIterations = 50;
        static const Symbolic x("x"), y("y");
        static const Symbolic F = (x - 2)*(x - 2) + (y - x*x)*(y - x*x);

        using namespace TwoDimensional;
        Point StartPoint(1.5, 5.0);
        Function func(F);

        void NewtonRaphson() {

            Point point = StartPoint;

            for(int iterator = 0; iterator <= MaxCycleIterations; iterator++) {
                cout<<"Iteration: "<<iterator<<"\n";

                Symbolic f = func.value(point);
                Symbolic g = func.gradient(point);
                Symbolic H = func.hessian(point);

                Point newpoint;
                newpoint = static_cast<Symbolic>(point.matrix.transpose() - (H.inverse()) * g.transpose());

                Symbolic fnew = func.value(newpoint);
                Symbolic gnew = func.gradient(newpoint);

                double dx = toDouble(gnew.column(0)), dy = toDouble(gnew.column(1));

                if((dx*dx + dy*dy) > Precision) {
                    point = newpoint;
                }
                else {
                    cout << "Newton and Raphson method reach solution with accuracy and terminated in " << iterator
                         << ". iteration \n\n";
                    cout << "Locally minimum of function have been found at "<<newpoint.matrix;
                    break;
                }

                visualisations();
            }
        }

        void LevenbergMarquardt()
        {
            float alfa= 8;
            float c   = 4;
            Point point = StartPoint;

            for(int iterator = 0; iterator <= MaxCycleIterations; iterator++) {
                cout<<"Iteration: "<<iterator<<"\n";

                Symbolic f = func.value(point);
                Symbolic g = func.gradient(point);
                Symbolic H = func.hessian(point);

                Symbolic eye = ((static_cast<Symbolic>(alfa),    0),
                                (   0, static_cast<Symbolic>(alfa)));

                Point newpoint;
                newpoint = (point.matrix.transpose() - (H + eye).inverse() * g.transpose());

                Symbolic fnew = func.value(newpoint);
                Symbolic gnew = func.gradient(newpoint);

                if(toDouble(fnew) < toDouble(f)) {
                    alfa = alfa/c;

                    double dx = toDouble(gnew.column(0)), dy = toDouble(gnew.column(1));

                    if((dx*dx + dy*dy) > Precision) {
                        point = newpoint;
                    } else {
                        cout << "Levenberg Marquardt method reach solution with accuracy and terminated in " << iterator
                             << ". iteration \n\n";
                        cout << "Locally minimum of function have been found at [" << newpoint[0] << " " << newpoint[1]
                             << "]\n\n";
                        break;
                    }
                }
                else {
                    alfa = alfa/c;
                }
            }
        }


    }
}

