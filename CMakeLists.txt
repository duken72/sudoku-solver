cmake_minimum_required(VERSION 3.22.1)

project(sudoku_solver)

add_executable(${PROJECT_NAME} sudoku.cpp)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Linking
add_executable(test_possible_value test/test_possible_value.cpp)
target_link_libraries(test_possible_value
    ${GTEST_LIBRARIES}
    pthread
)
