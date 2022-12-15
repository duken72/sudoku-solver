#!/bin/bash

clear
cmake -S . -B build
cd build && make

GTEST_COLOR=1 ctest
# GTEST_COLOR=1 ctest -V

# ./sudoku_solver < ../test/t2.txt
./sudoku_solver < ../test/t1.txt

cd ..
