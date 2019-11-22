//
// Created by zahorack on 11/22/19.
//

#include "Plot.h"
#include <iostream>

static string StringForGnuplot(string input)
{
    size_t index = 0;
    while (true) {
        /* Locate the substring to replace. */
        index = input.find("^", index);
        if (index == std::string::npos) break;
        /* Make the replacement. */
        input.replace(index, 1, "**");
        /* Advance index forward so the next iteration doesn't pick it up as well. */
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