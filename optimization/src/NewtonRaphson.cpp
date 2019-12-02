//
// Created by zahorack on 11/22/19.
//


#include "NewtonRaphson.h"
#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"
#include "string.h"
#include "Plot.h"


namespace Optimization {

    static const float MaxCycleIterations = 50;

    NewtonRaphson::NewtonRaphson(TwoDimensional::Function f, TwoDimensional::Point begin) :
        m_function(f),
        m_point(begin),
        m_precision(0.001),
        m_timer(Time::Microseconds)
    {}

    NewtonRaphson::NewtonRaphson(TwoDimensional::Function f, TwoDimensional::Point begin, float precision) :
        m_function(f),
        m_point(begin),
        m_precision(precision),
        m_timer(Time::Microseconds)
    {}

    TwoDimensional::Point NewtonRaphson::findMinimum() {
        TwoDimensional::Point point = m_point;
        TwoDimensional::Point newpoint;

        m_timer.start();

        for (int iterator = 0; iterator <= MaxCycleIterations; iterator++) {
            cout << "Iteration: " << iterator << "\n";

            Symbolic f = m_function.value(point);
            Symbolic g = m_function.gradient(point);
            Symbolic H = m_function.hessian(point);

            newpoint = static_cast<Symbolic>(point.matrix.transpose() - (H.inverse()) * g.transpose());

            Symbolic fnew = m_function.value(newpoint);
            Symbolic gnew = m_function.gradient(newpoint);

            double dx = toDouble(gnew.column(0)), dy = toDouble(gnew.column(1));

            if ((dx * dx + dy * dy) > m_precision) {
                point = newpoint;
            } else {
                m_timer.stop();
                cout << "Newton and Raphson method reach solution with accuracy and terminated in " << iterator
                     << ". iteration \n\n";
                cout << "Locally minimum of function have been found at " << newpoint.matrix;
                break;
            }
        }

        m_timer.result();
//        Plot::function(m_function.getSymbolic());

        return newpoint;
    }
}

