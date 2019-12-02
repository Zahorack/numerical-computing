file(GLOB_RECURSE files "src/*.cpp")

add_library(optimization STATIC ${files} include/LevenbergMarquardt.h src/LevenbergMarquardt.cpp include/NelderMead.h src/NelderMead.cpp include/Simplex.h src/Simplex.cpp include/GoldenSectionSearch.h src/GoldenSectionSearch.cpp include/DavidonSearch.h src/DavidonSearch.cpp)
target_include_directories(optimization PUBLIC include)

target_link_libraries(optimization PUBLIC numerical_computing)







