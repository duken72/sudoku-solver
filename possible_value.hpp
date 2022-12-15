#ifndef SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_
#define SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_

#include <array>
#include <iostream>

using std::array;
using std::cout, std::endl;

static const unsigned char SIZE = 9;
using P_VAL = unsigned short;


class possible_value
{
private:
    int N_;
    array<P_VAL, SIZE + 1> possibilities_;

public:
    possible_value();
    ~possible_value();

    P_VAL get_N() const;
    P_VAL get_val() const;
    void print() const;
    bool check_val(const P_VAL &val) const;

    void remove_val(const P_VAL &val);
    void clear();
};

possible_value::possible_value() {
    N_ = SIZE;
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

void possible_value::clear() {
    N_ = 0;
    possibilities_.fill(0);
}

void possible_value::print() const {
    cout << N_ << " possible values:";
    for (int i = 1; i <= SIZE; i++) {
        if (possibilities_[i])        
            cout << " " << i;
    }
    cout << endl;
}

P_VAL possible_value::get_val() const {
    if (N_ > 1)
        return 0;
    for (int i = 1; i <= SIZE; i++) {
        if (possibilities_[i])
            return i;
    }
    return 0;    
}

bool possible_value::check_val(const P_VAL &val) const
{
    return possibilities_[val] == 1;
}

P_VAL possible_value::get_N() const { return N_; }

#endif  // SUDOKU_SOLVER__POSSIBLE_VALUE_HPP_
