#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include "sudoku.hpp"

int main(int argc, char const *argv[])
{
    Sudoku game;
    game.get_map();
    game.solve();
    return 0;
}
