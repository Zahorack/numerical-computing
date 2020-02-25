file(GLOB_RECURSE files "src/*.cpp")

add_library(numerical_computing STATIC ${files} include/Plot.h src/Plot.cpp include/Timer.h src/Timer.cpp src/TransferFunction.cpp include/TransferFunction.h src/QuadraticEquation.cpp include/QuadraticEquation.h src/ComplexNumber.cpp include/ComplexNumber.h src/LinearEquationsSystem.cpp include/LinearEquationsSystem.h)
target_include_directories(numerical_computing PUBLIC include ${Boost_INCLUDE_DIR})

target_link_libraries(numerical_computing PUBLIC ${Boost_LIBRARIES} gnuplot_iostream symbolic_cpp)
