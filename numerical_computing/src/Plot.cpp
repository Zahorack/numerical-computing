//
// Created by zahorack on 11/22/19.
//

#include "Plot.h"
#include <iostream>

static string StringForGnuplot(string input)
{
    //fix exp format from symbolic c++
    size_t index = 0;
    while (true) {
        /* Locate the substring to replace. */
        index = input.find("e^", index);
        if (index == std::string::npos) break;
        /* Make the replacement. */
        input.replace(index, 2, "exp");
        /* Advance index forward so the next iteration doesn't pick it up as well. */
        index += 1;
    }

    //fix exponent format from symbolic c++
    index = 0;
    while (true) {
        index = input.find("^", index);
        if (index == std::string::npos) break;
        input.replace(index, 1, "**");
        index += 1;
    }
    //fix time based functions
    index = 0;
    while (true) {
        index = input.find("t", index);
        if (index == std::string::npos) break;
        input.replace(index, 1, "x");
        index += 1;
    }

    return input;
}


Plot::Plot(Symbolic input):
    gp("gnuplot -persist"),
    m_input(input)
{}

Plot::~Plot()
{}

string Plot::SymbolicToString(Symbolic input)
{
    std::ostringstream stream;
    stream<<input;
    std::string str =  stream.str();
//    const char* chr = str.c_str();

    return str;
}

void Plot::function(Symbolic input)
{
    string str = SymbolicToString(input);
    cout<<"Plotting: "<<StringForGnuplot(str)<<"\n";

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
    gp<<(StringForGnuplot(str));
    gp<<("\n");
}

void Plot::function(TwoDimensional::Function input)
{
    string str = SymbolicToString(input.getSymbolic());
    cout<<"Plotting: "<<str<<"\n";

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
    gp<<(StringForGnuplot(str));
    gp<<("\n");
}

void Plot::systemModel(FirstOrder::SystemModel system)
{
    string str = SymbolicToString(system.transitionFunction());
    cout<<"Plotting: "<<StringForGnuplot(str)<<"\n";

    Gnuplot gp("gnuplot -persist");
    gp<<("set xrange [0:");
    gp<<(system.getTimeConstant()*6);
    gp<<("]\n");

    gp<<("set yrange [0:");
    gp<<(system.getGain()*(5/3));
    gp<<("]\n");

    //gp<<("set pm3d at b\n");
//    gp<<("set ticslevel 0.8\n");
//    gp<<("set isosample 40,40\n");
//    gp<<("set cntrparam levels 15\n");
//    gp<<("set samples 20\n");
//    gp<<("set isosamples 21\n");
   // gp<<("set view 60, 30, 0.85, 1.1\n");
   // gp<<("set key at screen 1.0, 0.9\n");
   // gp<<("set style textbox opaque noborder margins 0.5, 0.5\n");
   // gp<<("set cntrparam levels incr -10,1,10\n");
   // gp<<("set contour\n");

    gp<<("plot ");
    gp<<(StringForGnuplot(str));
    gp<<("\n");
}