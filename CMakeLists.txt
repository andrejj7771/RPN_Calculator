cmake_minimum_required(VERSION 3.0)
project(RPN_Calculator)

option(BUILD_TESTS "Build core tests" ON)

add_subdirectory(core)
add_subdirectory(app)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
