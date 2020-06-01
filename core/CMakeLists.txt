set(PROJECT_NAME core)

project(${PROJECT_NAME} VERSION 0.0.0.1 LANGUAGES CXX)

include_directories(
    include
)

add_library(${PROJECT_NAME} SHARED
    include/define.hpp
    include/RPN/RPN_Converter.hpp
    include/Solver/Solver.hpp
    
    src/RPN/RPN_Converter.cpp
    src/Solver/Solver.cpp
)
