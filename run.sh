#!/bin/bash

# g++ -O2 -std=c++17 -Wall sudoku_backtracking.cpp -o cpp_pure_btk
clear
cmake -S . -B build
cd build && make
GTEST_COLOR=1 ctest #-V

cd ..
echo "Try ./sudoku_solver < ../test/t1.txt"
