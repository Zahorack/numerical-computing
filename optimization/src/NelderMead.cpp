//
// Created by zahorack on 11/23/19.
//



#include "NelderMead.h"
#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"
#include "string.h"
#include "Plot.h"
#include <math.h>

namespace Optimization {

    static const int MaxCycleIterations = 50;
    static const float ExpansionCoefficient = 2.0;
    static const float ContractionCoefficient = 0.5;
    static const float ReductionCoefficient = 0.5;

    static double symbolicToDouble(Symbolic sym) {
        return static_cast<double>(sym);
    }

    NelderMead::NelderMead(TwoDimensional::Function f, TwoDimensional::Point begin) :
        m_function(f),
        m_point(begin),
        m_precision(0.001),
        m_initialSize(2),
        m_timer(Time::Microseconds)
    {}

    NelderMead::NelderMead(TwoDimensional::Function f, TwoDimensional::Point begin, double precision, double initSize) :
        m_function(f),
        m_point(begin),
        m_precision(precision),
        m_initialSize(initSize),
        m_timer(Time::Microseconds)
    {}

    TriangleSimplex NelderMead::createInitialSimplex() {
        // Starting point is in the center of initial simplex
        // When simplex is Triangle - orthocentrum

        double height = sqrt(pow(m_initialSize, 2) - pow((m_initialSize/2),2));

        TwoDimensional::Point a = TwoDimensional::Point(m_point[0] - m_initialSize/2, m_point[1] - height/3);
        TwoDimensional::Point b = TwoDimensional::Point(m_point[0] + m_initialSize/2, m_point[1] - height/3);
        TwoDimensional::Point c = TwoDimensional::Point(m_point[0], m_point[1] + 2*height/3);

        Vertex A = Vertex(a, m_function.value(a));
        Vertex B = Vertex(b, m_function.value(b));
        Vertex C = Vertex(c, m_function.value(c));

        return TriangleSimplex(A, B, C);
    }

    Vertex NelderMead::center() {
        Vertex center;

        center.point.matrix = (simplex.bestVertex.point.matrix + simplex.neutralVertex.point.matrix)/2;
        center.value = m_function.value(center.point);

        return center;
    }

    Vertex NelderMead::reflection() {
        Vertex reflect;

        reflect.point.matrix = 2*center().point.matrix - simplex.worstVertex.point.matrix;
        reflect.value = m_function.value(reflect.point);

        return reflect;
    }

    Vertex NelderMead::expansion() {
        Vertex expansion;

        TwoDimensional::Point reflected = reflection().point;
        TwoDimensional::Point cent = center().point;

        expansion.point.matrix = cent.matrix + (reflected.matrix - cent.matrix)* Symbolic(ExpansionCoefficient);
        expansion.value = m_function.value(expansion.point);

        return expansion;
    }

    Vertex NelderMead::contraction() {
        Vertex contraction;
        TwoDimensional::Point cent = center().point;

        contraction.point.matrix = cent.matrix + (simplex.worstVertex.point.matrix - cent.matrix)* Symbolic(ContractionCoefficient);
        contraction.value = m_function.value(contraction.point);

        return contraction;
    }

    Vertex NelderMead::reduction(Vertex vert) {
        Vertex reduction;
        TwoDimensional::Point best = simplex.bestVertex.point;

        reduction.point.matrix = best.matrix + (vert.point.matrix - best.matrix)*Symbolic(ReductionCoefficient);
        reduction.value = m_function.value(reduction.point);

        return reduction;
    }

    bool NelderMead::terminatingCondition() {

        double values[3] = {simplex.bestVertex.value, simplex.neutralVertex.value, simplex.worstVertex.value};
        double average = (values[0] + values[1] + values[2])/3;
        double sigma = 0.5*(pow((values[0]-average),2) + pow((values[1]-average),2) + pow((values[2]-average),2));

        if(sqrt(sigma) < m_precision) {
            return true;
        }
        return false;
    }

    TwoDimensional::Point NelderMead::findMinimum() {
        TwoDimensional::Point point = m_point;
        int iterator = 0;
        simplex = createInitialSimplex();

        m_timer.start();

        while(!terminatingCondition() && iterator < MaxCycleIterations) {
            iterator++;

            if (reflection().value < simplex.bestVertex.value) {
                if (expansion().value < reflection().value) {
                    /* Expansion */
                    simplex.replaceWorstBy(expansion());
                } else {
                    /* Reflection */
                    simplex.replaceWorstBy(reflection());
                }
            } else {
                if (reflection().value < simplex.neutralVertex.value) {
                    /* Reflection */
                    simplex.replaceWorstBy(reflection());

                } else {
                    if (reflection().value < simplex.worstVertex.value) {
                        /* Reflection */
                        simplex.replaceWorstBy(reflection());
                    }

                    if (contraction().value < simplex.worstVertex.value) {
                        /* Contraction */
                        simplex.replaceWorstBy(contraction());
                    } else {
                        /* Reduction */
                        simplex.replaceWorstBy(reduction(simplex.worstVertex));
                        simplex.replaceNeutralBy(reduction(simplex.neutralVertex));
                    }
                }
            }
            simplex.sortSimplex();

        } /* End of while */

        m_timer.stop();
        cout << "Nelder and Mead method reach solution with accuracy and terminated in " << iterator
             << ". iteration \n";
        cout << "Locally minimum of function have been found at " <<simplex.bestVertex.point.matrix;
        m_timer.result();

        return simplex.bestVertex.point;
    }

}