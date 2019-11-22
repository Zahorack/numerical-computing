//
// Created by zahorack on 11/22/19.
//

#ifndef NUMERICAL_COMPUTING_PLOT_H
#define NUMERICAL_COMPUTING_PLOT_H

#include "Function.h"
#include "symbolicc++.h"
#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"

#include <string.h>

class Plot {

    Gnuplot gp;
    Symbolic m_input;
public:
    Plot(Symbolic);
    ~Plot();

    static string SymbolicToString(Symbolic);
    static void function(Symbolic);

    static void function(OneDimensional::Function);
    static void function(TwoDimensional::Function);
    static void function(ThreeDimensional::Function);


};
#endif //NUMERICAL_COMPUTING_PLOT_H
