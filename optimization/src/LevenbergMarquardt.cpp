//
// Created by zahorack on 11/22/19.
//



#include "LevenbergMarquardt.h"
#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"
#include "string.h"
#include "Plot.h"


namespace Optimization {

    using namespace TwoDimensional;
    static const float MaxCycleIterations = 50;

    static double toDouble(Symbolic sym) {
        return static_cast<double>(sym);
    }

    LevenbergMarquardt::LevenbergMarquardt(Function f, Point begin) :
            m_function(f),
            m_point(begin),
            m_precision(0.001) {}

    LevenbergMarquardt::LevenbergMarquardt(Function f, Point begin, float precision) :
            m_function(f),
            m_point(begin),
            m_precision(precision) {}


    Point LevenbergMarquardt::findMinimum() {
        Point point = m_point;
        Point newpoint;

        float alfa = 8;
        float c = 4;

        for (int iterator = 0; iterator <= MaxCycleIterations; iterator++) {
            cout << "Iteration: " << iterator << "\n";

            Symbolic f = m_function.value(point);
            Symbolic g = m_function.gradient(point);
            Symbolic H = m_function.hessian(point);

            Symbolic eye = ((static_cast<Symbolic>(alfa), 0),
                    (0, static_cast<Symbolic>(alfa)));

            newpoint = (point.matrix.transpose() - (H + eye).inverse() * g.transpose());

            Symbolic fnew = m_function.value(newpoint);
            Symbolic gnew = m_function.gradient(newpoint);

            if (toDouble(fnew) < toDouble(f)) {
                alfa = alfa / c;

                double dx = toDouble(gnew.column(0)), dy = toDouble(gnew.column(1));

                if ((dx * dx + dy * dy) > m_precision) {
                    point = newpoint;
                } else {
                    cout << "Levenberg Marquardt method reach solution with accuracy and terminated in " << iterator
                         << ". iteration \n\n";
                    cout << "Locally minimum of function have been found at [" << newpoint[0] << " " << newpoint[1]
                         << "]\n\n";
                    break;
                }
            } else {
                alfa = alfa / c;
            }
        }
        //        Plot::function(m_function.getSymbolic());

        return newpoint;
    }

}




