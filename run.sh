#!/bin/bash

clear
cmake -S . -B build
cd build && make

# ctest -V
./test_possible_value
./test_sup_print
./test_sudoku

cd ..
# ./build/sudoku_solver < test/t2.txt
# ./build/sudoku_solver < test/t1.txt
