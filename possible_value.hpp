#include <array>
#include <iostream>

using std::array;
using std::cout, std::endl;

static const unsigned char SIZE = 9;
using P_VAL = unsigned short;

struct possible_value
{
    int _N;
    array<P_VAL, SIZE + 1> _possibilities;

    possible_value();
    ~possible_value();

    void remove_val(const P_VAL &val);
    void clear();
    void print() const;
    P_VAL get_val() const;
};

possible_value::possible_value() {
    _N = SIZE;
    _possibilities.fill(1);
}

possible_value::~possible_value() {}

void possible_value::remove_val(const P_VAL &val) {
    if (val <= 0 || val >= 10) {
        cout << "Error: Invalid value (not in range 1 to 9)." << endl;
        return;
    }
    if (_possibilities[val] == 0)
        return;
    if (_possibilities[val] == 1) {
        _N--;
        _possibilities[val] = 0;
    }
}

void possible_value::clear() {
    _N = 0;
    _possibilities.fill(0);
}

void possible_value::print() const {
    cout << _N << " possible values:";
    for (int i = 1; i <= SIZE; i++) {
        if (_possibilities[i])        
            cout << " " << i;
    }
    cout << endl;    
}

P_VAL possible_value::get_val() const {
    if (_N > 1)
        return 0;
    for (int i = 1; i <= SIZE; i++) {
        if (_possibilities[i])
            return i;
    }
    return 0;    
}
