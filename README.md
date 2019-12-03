# Numerical computing
Open source Interactive numerical computing environment

## Toolbox specification
This repository contains necessary packages to symbolic computation, 
matrix algebra etc., also offer data visualisation - graphs.  

For symbolic computation is used `SymbolicC++` library, for data visualisation and 
plotting is used `Gnuplot-iostream`.

### Numerical computing library
My C++ implementation of utilities based on symbolic computation.

####Function

Object _Function_ represent mathematical function by symbolic variables. 

```
    TwoDimensional::Function myFunction((x - 2)*(x + 5) + 3*y);
```

1. **Function value**
```
myFunction.value(Point);
```
return function value of function at given `Point`.

2. **Function gradient**
```
myFunction.gradient();
myFunction.gradient(Point);
```
return matrix `n x 1` of function's first derivatives - gradient. 

3. **Function hessian**
```
myFunction.hessian();
myFunction.hessian(Point);
```
return matrix `n x n`  of function's seconds derivatives - hessian. 

4. **Function character of stationary/inflection point**
```
myFunction.character(Point);
```
return `StationaryPoin::Minimum = 0` if Point is a locally minimum of function, return 
`StationaryPoin::Maximum = 1` if Point is a locally maximum, or `StationaryPoin::Saddle = 2`
if Point is saddle point of function.




```
Linux

C++

custom IDE (Jetbrains CLion)

SymbolicC++ lib

GnuPlot-iostream
```

## Area of use

> Symbolic intergation and derivation

> Graphical solutions and visualisations

> Process optimalisation

#### My application
I have develop this platform to implement Numerical Optimization methods used for
finding locally extremes of functions. 

## Numerical optimization
#### One dimensional optimization problem
- Davidon's search
- Golden selection search

#### Two dimensional optimization problem
- Nelder & Mead method
- Newton & Raphson method
- Levenberg & Marquardt method

## Usage example
```
    TwoDimensional::Function myFunction((x - 2)*(x + 5) + y*y);
    TwoDimensional::Point startPoint(1.5, 5);
    
    Optimization::NelderMead myMethod(myFunction, startPoint);
    myMethod.findMinimum();
```

