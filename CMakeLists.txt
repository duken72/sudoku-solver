cmake_minimum_required(VERSION 3.22.1)

project(sudoku_solver)

add_executable(${PROJECT_NAME} sudoku.cpp)

# Linking
    
# Testing
find_package(GTest REQUIRED)
enable_testing()
add_executable(test_typedef test/test_typedef.cpp)
target_link_libraries(test_typedef
    ${GTEST_LIBRARIES}
)
add_executable(test_sup_print test/test_sup_print.cpp)
target_link_libraries(test_sup_print
    ${GTEST_LIBRARIES}
)
add_executable(test_possible_value test/test_possible_value.cpp)
target_link_libraries(test_possible_value
    ${GTEST_LIBRARIES}
)
add_executable(test_sudoku test/test_sudoku.cpp)
target_link_libraries(test_sudoku
    ${GTEST_LIBRARIES}
)

include(GoogleTest)
gtest_discover_tests(test_typedef)
gtest_discover_tests(test_sup_print)
gtest_discover_tests(test_possible_value)
gtest_discover_tests(test_sudoku)
