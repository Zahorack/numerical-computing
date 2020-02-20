file(GLOB_RECURSE files "src/*.cpp")

add_library(numerical_control STATIC ${files} include/SystemModel.h src/SystemModel.cpp)
target_include_directories(numerical_control PUBLIC include)

target_link_libraries(numerical_control PUBLIC numerical_computing)







