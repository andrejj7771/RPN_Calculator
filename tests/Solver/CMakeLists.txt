project(Solver_Test LANGUAGES CXX)

include_directories(../../core/include)

add_executable(Solver_Test Solver_Test.cpp)
target_link_libraries(Solver_Test core)

add_test(NAME Solver_Test_1 COMMAND Solver_Test "346 + 14 * 2 / (33 - 58)^2" "346.0448")
add_test(NAME Solver_Test_2 COMMAND Solver_Test "-346 + 14" "-332")
add_test(NAME Solver_Test_3 COMMAND Solver_Test "2 + 2 * 2" "6")
add_test(NAME Solver_Test_4 COMMAND Solver_Test "(2 + 2) * 2" "8" )
add_test(NAME Solver_Test_5 COMMAND Solver_Test "10 + - 14" "-4")
add_test(NAME Solver_Test_6 COMMAND Solver_Test "10.5 + - 14.2 * 2.8" "-29.26")
add_test(NAME Solver_Test_7 COMMAND Solver_Test "-1" "-1")
add_test(NAME Solver_Test_8 COMMAND Solver_Test "--1" "1")
