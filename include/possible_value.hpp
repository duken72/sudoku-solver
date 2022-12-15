#ifndef SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_
#define SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_

#include <array>
#include <vector>
#include <iostream>

#include "typedef.hpp"

using std::array, std::vector;
using std::cout, std::endl;

class possible_value
{
private:
    int N_;
    array<bool, S + 1> possibilities_;

public:
    possible_value();
    ~possible_value();

    // Get the number of possible values
    SUDOKU_VAL get_N() const;

    // Get a vector of possible values
    vector<SUDOKU_VAL> get_val() const;

    void print() const;

    // Check if a value is valid for this cell
    bool check_val(const SUDOKU_VAL &val) const;

    // Set a value to invalid
    void remove_val(const SUDOKU_VAL &val);

    // Set a value to be the only one that is valid
    void keep_only_val(const SUDOKU_VAL &val);

    // Clear all valid values
    void clear();
};

possible_value::possible_value()
{
    N_ = S;
    possibilities_.fill(true);
}

possible_value::~possible_value() {}

void possible_value::remove_val(const SUDOKU_VAL &val) {
    if (val < 1 || val > S) {
        cout << "Error: Invalid value (not in range 1 to 9)." << endl;
        return;
    }
    if (possibilities_[val]) {
        N_--;
        possibilities_[val] = false;
    }
}

void possible_value::keep_only_val(const SUDOKU_VAL &val) {
    if (val < 1 || val > S) {
        cout << "Error: Invalid value (not in range 1 to 9)." << endl;
        return;
    }
    clear();
    N_ = 1;
    possibilities_[val] = true;
}

void possible_value::clear() {
    N_ = 0;
    possibilities_.fill(false);
}

void possible_value::print() const {
    cout << N_ << " possible values:";
    for (int i = 1; i <= S; i++) {
        if (possibilities_[i])        
            cout << " " << i;
    }
    cout << endl;
}

vector<SUDOKU_VAL> possible_value::get_val() const {
    vector<SUDOKU_VAL> output;
    for (int i = 1; i <= S; i++) {
        if (possibilities_[i])
            output.push_back(i);
    }
    return output;
}

bool possible_value::check_val(const SUDOKU_VAL &val) const
{
    return possibilities_[val];
}

SUDOKU_VAL possible_value::get_N() const { return N_; }

bool operator== (const possible_value &pv1, const possible_value &pv2)
{
    if (pv1.get_N() != pv2.get_N())
        return false;
    for (int val = 1; val <= S; val++) {
        if (pv1.check_val(val) != pv2.check_val(val))
            return false;
    }
    return true;
}

#endif  // SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_
