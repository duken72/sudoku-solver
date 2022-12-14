#!/bin/bash

clear
cmake -S . -B build
cd build && make

./test_possible_value

cd ..
# ./build/sudoku_solver < test/t2.txt
# ./build/sudoku_solver < test/t1.txt
