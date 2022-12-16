// https://www.geeksforgeeks.org/sudoku-backtracking-7/

#include <iostream>

using std::cout, std::cin, std::endl;
using SV = unsigned short;
const SV S = 9;

void print(SV grid[S][S])
{
    for (SV i = 0; i < S; i++) {
        for (SV j = 0; j < S; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

bool isSafe(SV grid[S][S], SV row, SV col, SV val)
{
    for (SV x = 0; x < S; x++)
        if (grid[row][x] == val)
            return false;
    for (SV x = 0; x < S; x++)
        if (grid[x][col] == val)
            return false;
    SV startRow = row - row % 3,
        startCol = col - col % 3;
    for (SV i = 0; i < 3; i++)
        for (SV j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == val)
                return false;
    return true;
}
 
bool solveSudoku(SV grid[S][S], SV row, SV col)
{
    if (row == (S - 1) && col == S)
        return true;
 
    if (col == S) {
        row++;
        col = 0;
    }
   
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);
 
    for (SV val = 1; val <= S; val++)
    {
        if (isSafe(grid, row, col, val)) {
            grid[row][col] = val;
            if (solveSudoku(grid, row, col + 1))
                return true;
        }
        grid[row][col] = 0;
    }
    return false;
}

void read_grid(SV grid[S][S])
{
    for (SV i = 0; i < S; i++) {
        for (SV j = 0; j < S; j++) {
            cin >> grid[i][j];
        }
    }
}

int main(int argc, char const *argv[])
{
    SV grid[S][S];
    read_grid(grid);
    solveSudoku(grid, 0, 0);
    print(grid);
    return 0;
}
