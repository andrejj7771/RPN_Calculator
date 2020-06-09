set(PROJECT_NAME calculator)

project(${PROJECT_NAME} LANGUAGES CXX)

include_directories(../core/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} core)
