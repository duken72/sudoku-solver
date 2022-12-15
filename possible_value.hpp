// TODO: rename to typedef.hpp

#ifndef SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_
#define SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_

#include <array>
#include <vector>
#include <iostream>

#include "typedef.hpp"

using std::array, std::vector;
using std::cout, std::endl;

using P_VAL = unsigned short;

class possible_value
{
private:
    int N_;
    array<P_VAL, S + 1> possibilities_;

public:
    possible_value();
    ~possible_value();

    P_VAL get_N() const;
    vector<P_VAL> get_val() const;
    // P_VAL get_val() const;
    // pair<P_VAL, P_VAL> get_vals() const;
    void print() const;
    bool check_val(const P_VAL &val) const;

    void remove_val(const P_VAL &val);
    void keep_only_val(const P_VAL &val);
    void clear();
};

possible_value::possible_value() {
    N_ = S;
    possibilities_.fill(1);
}

possible_value::~possible_value() {}

void possible_value::remove_val(const P_VAL &val) {
    if (val <= 0 || val >= 10) {
        cout << "Error: Invalid value (not in range 1 to 9)." << endl;
        return;
    }
    if (possibilities_[val] == 0)
        return;
    if (possibilities_[val] == 1) {
        N_--;
        possibilities_[val] = 0;
    }
}

void possible_value::keep_only_val(const P_VAL &val) {
    if (val < 1 || val > S) {
        cout << "Error: Invalid value (not in range 1 to 9)." << endl;
        return;
    }
    clear();
    N_ = 1;
    possibilities_[val] = 1;
}

void possible_value::clear() {
    N_ = 0;
    possibilities_.fill(0);
}

void possible_value::print() const {
    cout << N_ << " possible values:";
    for (int i = 1; i <= S; i++) {
        if (possibilities_[i])        
            cout << " " << i;
    }
    cout << endl;
}

vector<P_VAL> possible_value::get_val() const {
    vector<P_VAL> output;
    for (int i = 1; i <= S; i++) {
        if (possibilities_[i])
            output.push_back(i);
    }
    return output;
}

// P_VAL possible_value::get_val() const {
//     if (N_ > 1)
//         return 0;
//     for (int i = 1; i <= S; i++) {
//         if (possibilities_[i])
//             return i;
//     }
//     return 0;    
// }

// pair<P_VAL, P_VAL> possible_value::get_vals() const {
//     P_VAL v1 = 0, v2 = 0;
//     for (int i = 1; i <= S; i++) {
//         if (!possibilities_[i])
//             continue;
//         if (!v1) {
//             v1 = i;
//             continue;
//         }
//         v2 = i;
//         break;
//     }
//     return make_pair(v1, v2);
// }

bool possible_value::check_val(const P_VAL &val) const
{
    return possibilities_[val] == 1;
}

P_VAL possible_value::get_N() const { return N_; }

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
