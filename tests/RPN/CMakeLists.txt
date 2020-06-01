project(RNP_Converter_Tests LANGUAGES CXX)

include_directories(../../core/include)

add_executable(RPN_Converter_Test RPN_Converter_Test.cpp)
target_link_libraries(RPN_Converter_Test core)

add_test(NAME RPN_Converter_Test_1 COMMAND RPN_Converter_Test "346 + 14 * 2 / (33 - 58)^2" "346 14 2 * 33 58 - 2 ^ / +")
add_test(NAME RPN_Converter_Test_2 COMMAND RPN_Converter_Test "-346 + 14" "346 - 14 +")
add_test(NAME RPN_Converter_Test_3 COMMAND RPN_Converter_Test "2 + 2 * 2" "2 2 2 * +")
add_test(NAME RPN_Converter_Test_4 COMMAND RPN_Converter_Test "(2 + 2) * 2" "2 2 + 2 *")
add_test(NAME RPN_Converter_Test_5 COMMAND RPN_Converter_Test "10 + - 14" "10 + 14 -")
add_test(NAME RPN_Converter_Test_6 COMMAND RPN_Converter_Test "10 + - 14 * 2" "10 + 14 2 * -")
add_test(NAME RPN_Converter_Test_7 COMMAND RPN_Converter_Test "14 * (-2) + 10 - (-5)" "14 2 - * 10 + 5 - -")
