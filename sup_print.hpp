#ifndef SUDOKU_SOLVER__SUP_PRINT_HPP_
#define SUDOKU_SOLVER__SUP_PRINT_HPP_

#include <vector>
#include <iostream>

using std::cin, std::cout, std::endl, std::ostream;
using std::vector;

// Supporting function for: printing and logging

template <typename T>
ostream & operator << (ostream& os, const vector<T>& vec)
{
    cout << "Vector: ";
    for(auto elem : vec)
        os << elem << " ";
    return os;
}



#endif  // SUDOKU_SOLVER__SUP_PRINT_HPP_
