project(utils_tests LANGUAGES CXX)

include_directories(../../core/include)

set(TARGETS
    is_digit_test
    is_not_digit_test
    is_number_test
    is_not_number_test
    is_operation_test
    is_not_operation_test
    validate_expr_test
    priority_test
    token_type_test
)

foreach(TARGET ${TARGETS})
    add_executable(${TARGET} ${TARGET}.cpp)
    target_link_libraries(${TARGET} core)
endforeach(TARGET)

add_test(
    NAME is_digit_test
    COMMAND is_digit_test
    "10" "0" "1" "2" "3" "4" "5" "6" "7" "8" "9"
)

add_test(
    NAME is_not_digit_test
    COMMAND is_not_digit_test
    "5" "a" "h" "+" "^" ")"
)

add_test(
    NAME is_number_test
    COMMAND is_number_test
    "5" "15" "5" "510" "53.63" "6547.30034"
)

add_test(
    NAME is_not_number_test
    COMMAND is_not_number_test
    "3", "x", "235.346.2" "-45.45"
)

add_test(
    NAME is_operation_test
    COMMAND is_operation_test
    "5" "+" "-" "*" "/" "^"
)

add_test(
    NAME is_not_operation_test
    COMMAND is_not_operation_test
    "2" "|" "\\"
)

add_test(
    NAME validate_expr_test_1
    COMMAND validate_expr_test
    ")((2(4.4)5,64.5+.2^2)*()-2))(" "((2*(4.4)*5.645+0.2^2)*-2)"
)

add_test(
    NAME validate_expr_test_2
    COMMAND validate_expr_test
    "4(5.5 + 5)(.4 - 3.)" "4*(5.5+5)*(0.4-3)"
)

add_test(
    NAME validate_expr_test_3
    COMMAND validate_expr_test
    "**//--*4(5.5 + 5)(.4 - 3.)*/-" "-4*(5.5+5)*(0.4-3)"
)

add_test(
    NAME validate_expr_test_4
    COMMAND validate_expr_test
    "3+4*2/(1-5)^2" "3+4*2/(1-5)^2"
)

add_test(
    NAME priority_test_1
    COMMAND priority_test "+" "1"
)

add_test(
    NAME priority_test_2
    COMMAND priority_test "*" "2"
)

add_test(
    NAME priority_test_3
    COMMAND priority_test "^" "3"
)

add_test(
    NAME priority_test_4
    COMMAND priority_test "$" "-1"
)

add_test(
    NAME priority_test_5
    COMMAND priority_test "(" "0"
)

add_test(
    NAME token_type_test_1
    COMMAND token_type_test "534.4" "0"
)

add_test(
    NAME token_type_test_2
    COMMAND token_type_test "+" "1"
)

add_test(
    NAME token_type_test_3
    COMMAND token_type_test "(" "2"
)

add_test(
    NAME token_type_test_4
    COMMAND token_type_test ")" "2"
)

add_test(
    NAME token_type_test_5
    COMMAND token_type_test "&" "-1"
)

add_test(
    NAME token_type_test_6
    COMMAND token_type_test "x" "-1"
)
