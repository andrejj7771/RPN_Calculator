cmake_minimum_required(VERSION 3.0)
project(RPN_Calculator)

option(BUILD_TESTS "Build core tests" ON)
option(BUILD_GUI "Build GUI Application" OFF)

add_subdirectory(core)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_GUI)
    add_subdirectory(GUI)
else()
    add_subdirectory(app)
endif()
