# Numerical computing
Open source Interactive numerical computing environment

### Toolbox specification
This repository contains necessary packages to symbolic computation, 
matrix algebra etc., also offer data visualisation - graphs.  

For symbolic computation is used `SymbolicC++` library, for data visualisation and 
plotting is used `Gnuplot-iostream`.


### Area of use

*Matrices algebra*

*Symbolic differential computation*

*Graphical solutions and visualisations*

*Mathematical function properties analysis*

## Numerical computing library
My C++ implementation of utilities based on symbolic computation.



### Point

Object _Point_ represent point in n-dimensional space. 
```
    OneDimensional::Point myPoint(2);
    TwoDimensional::Point myPoint(1.5, 5);
    ThreeDimensional::Point myPoint(1.5, 2, 5);
```

1. **Point value**  
`` myPoint[i];`` return point value in `i` dimension.
By call `` myPoint.matrix;`` are possible matrices operations, return `1 x n` matrix.



### Function

Object _Function_ represent mathematical function by symbolic variables. 
```
    TwoDimensional::Function myFunction((x - 2)*(x + 5) + 3*y);
```

1. **Function value**  
`` myFunction.value(Point);``
return function value of function at given `Point`.

2. **Function gradient**
` myFunction.gradient(); myFunction.gradient(Point);`
return matrix `n x 1` of function's first derivatives - gradient. 

3. **Function hessian**
`myFunction.hessian(); myFunction.hessian(Point);`
return matrix `n x n`  of function's seconds derivatives - hessian. 

4. **Function character of stationary/inflection point**
`myFunction.character(Point);`
return `StationaryPoin::Minimum = 0` if Point is a locally minimum of function, return 
`StationaryPoin::Maximum = 1` if Point is a locally maximum, or `StationaryPoin::Saddle = 2`
if Point is saddle point of function.


### Plot
Object _Plot_ offer graphical visualisation and data plotting. 

```
Plot::function(myFunction.getSymbolic());
```

<p align="center">
<img src="https://github.com/Zahorack/numerical-computing/blob/master/image/plot2.png" width="400" title="hover text">
<img src="https://github.com/Zahorack/numerical-computing/blob/master/image/plot1.png" width="400" title="hover text">
</p>




#### My application
I have develop this platform to implement Numerical Optimization comparative and gradient methods 
used for finding locally extremes of functions. 

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

