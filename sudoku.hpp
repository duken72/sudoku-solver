#ifndef SUDOKU_SOLVER__SUDOKU_HPP_
#define SUDOKU_SOLVER__SUDOKU_HPP_

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "sup_print.hpp"
#include "possible_value.hpp"

#define LOGGING true

using std::cin, std::cout, std::endl;
using std::vector, std::array;

using SUDOKU_VAL = unsigned short;
using SUDOKU_ID = unsigned short;

// Size const
static const unsigned char S = 9;
static const SUDOKU_VAL VALID = 10;
static const SUDOKU_VAL ERROR = 20;
const unsigned char S_MAP = S * S;

// IDs of cells in the same row
const SUDOKU_ID ROW_IDS[S][S] =
{
    {0,  1,  2,  3,  4,  5,  6,  7,  8},
    {9,  10, 11, 12, 13, 14, 15, 16, 17},
    {18, 19, 20, 21, 22, 23, 24, 25, 26},
    {27, 28, 29, 30, 31, 32, 33, 34, 35},
    {36, 37, 38, 39, 40, 41, 42, 43, 44},
    {45, 46, 47, 48, 49, 50, 51, 52, 53},
    {54, 55, 56, 57, 58, 59, 60, 61, 62},
    {63, 64, 65, 66, 67, 68, 69, 70, 71},
    {72, 73, 74, 75, 76, 77, 78, 79, 80}
};
// IDs of cells in the same column
const SUDOKU_ID COLUMN_IDS[S][S] =
{
    {0, 9,  18, 27, 36, 45, 54, 63, 72},
    {1, 10, 19, 28, 37, 46, 55, 64, 73},
    {2, 11, 20, 29, 38, 47, 56, 65, 74},
    {3, 12, 21, 30, 39, 48, 57, 66, 75},
    {4, 13, 22, 31, 40, 49, 58, 67, 76},
    {5, 14, 23, 32, 41, 50, 59, 68, 77},
    {6, 15, 24, 33, 42, 51, 60, 69, 78},
    {7, 16, 25, 34, 43, 52, 61, 70, 79},
    {8, 17, 26, 35, 44, 53, 62, 71, 80}
};
// IDs of cells in the same 3x3 block
const SUDOKU_ID BLOCK_IDS[S][S] =
{
    {0, 1, 2, 9, 10, 11, 18, 19, 20},
    {3, 4, 5, 12, 13, 14, 21, 22, 23},
    {6, 7, 8, 15, 16, 17, 24, 25, 26},
    {27, 28, 29, 36, 37, 38, 45, 46, 47},
    {30, 31, 32, 39, 40, 41, 48, 49, 50},
    {33, 34, 35, 42, 43, 44, 51, 52, 53},
    {54, 55, 56, 63, 64, 65, 72, 73, 74},
    {57, 58, 59, 66, 67, 68, 75, 76, 77},
    {60, 61, 62, 69, 70, 71, 78, 79, 80}
};


class Sudoku
{
public:
    Sudoku();
    ~Sudoku();

    static SUDOKU_ID id2row_id(const SUDOKU_ID &id);
    static SUDOKU_ID id2column_id(const SUDOKU_ID &id);
    static SUDOKU_ID id2block_id(const SUDOKU_ID &id);

    void get_map();                     // get map from std::cin
    void get_map(SUDOKU_VAL array[]);   // get map from an array

    int get_num_found() const;          // get number of found cells
    int get_num_unchecked() const;      // get number of checked cells
    int get_num_not_found() const;      // get number of unfound cells

    // Set value to a cell
    void set_cell_value(const SUDOKU_ID &id, const SUDOKU_VAL &val);
    SUDOKU_VAL get_cell_value(const SUDOKU_ID &id) const;

    void print() const;                 // print the map
    void print_possible_values() const; // print cells' possible values

    // Update possible values of other cells based on known cells
    void update_possible_values();
    // Update if in a block, a value lies in specific row/column
    void advanced_update();
    // Fill cells with only 1 possible values
    void fill_certain_values();
    void solve();

private:
    SUDOKU_VAL map_[S_MAP];
    vector<SUDOKU_ID> ids_found_;       // id of known cells
    vector<SUDOKU_ID> ids_not_found_;   // id of unknown cells
    // id of known cells but haven't used for update
    vector<SUDOKU_ID> ids_unchecked_;
    array<possible_value, S_MAP> possible_vals_;
};

Sudoku::Sudoku() {
    for (int i = 0; i < S_MAP; i++)
        map_[i] = 0;
    ids_found_.clear();
    ids_unchecked_.clear();
    ids_not_found_.clear();
    for (SUDOKU_ID id = 0; id < S_MAP; id++)
        ids_not_found_.push_back(id);
}

Sudoku::~Sudoku() {}

void Sudoku::get_map() {
    ids_found_.clear();
    ids_not_found_.clear();
    ids_unchecked_.clear();
    for (int i = 0; i < S_MAP; i++) {
        cin >> map_[i];
        if (map_[i] < 0 || map_[i] > 9) {
            cout << "Invalid value for a cell: " << map_[i] << endl;
            break;
        }
        if (map_[i] == 0)
            ids_not_found_.emplace_back(i);
        else {
            ids_found_.emplace_back(i);
            ids_unchecked_.emplace_back(i);
        }
    }
}

void Sudoku::get_map(SUDOKU_VAL array[]) {
    ids_found_.clear();
    ids_not_found_.clear();
    ids_unchecked_.clear();
    for (int i = 0; i < S_MAP; i++) {
        map_[i] = array[i];
        if (map_[i] < 0 || map_[i] > 9) {
            cout << "Invalid value for a cell: " << map_[i] << endl;
            break;
        }
        if (map_[i] == 0)
            ids_not_found_.emplace_back(i);
        else {
            ids_found_.emplace_back(i);
            ids_unchecked_.emplace_back(i);
        }
    }
}

void Sudoku::print() const {
    cout << "   1 2 3   4 5 6   7 8 9" << endl;
    cout << " -------------------------" << endl;
    for (int i = 0; i < S_MAP; i++) {
        if (i % 9 == 0)
            cout << i/9 + 1;
        if (i % 3 == 0)
            cout << "| ";
        if (map_[i] == 0)
            cout << "  ";
        else
            cout << map_[i] << " ";
        if (i % 9 == 8)
            cout << "|" << endl;
        if (i % 27 == 26)
            cout << " -------------------------" << endl;
    }
}

void Sudoku::print_possible_values() const {
    for (auto id_not_found : ids_not_found_) {
        cout << "Cell " << id_not_found << " with ";
        possible_vals_[id_not_found].print();
    }
}

SUDOKU_ID Sudoku::id2row_id(const SUDOKU_ID &id) {
    if (id < 0 || id > 80) {
        cout << "Invalid value for id (Out of range)." << endl;
        return ERROR;
    }
    return id / S;
}

SUDOKU_ID Sudoku::id2column_id(const SUDOKU_ID &id) {
    if (id < 0 || id > 80) {
        cout << "Invalid value for id (Out of range)." << endl;
        return ERROR;
    }
    return id % S;
}

SUDOKU_ID Sudoku::id2block_id(const SUDOKU_ID &id) {
    if (id < 0 || id > 80) {
        cout << "Invalid value for id (Out of range)." << endl;
        return ERROR;
    }
    return (id / 27) * 3 + (id % 9) / 3;
}

/**
 * @brief Update possible values of a cell based on found values
 * of other cells in the same row, column or block 
 */
void Sudoku::update_possible_values() {
#if LOGGING
    cout << "Update possible values ..." << endl;
#endif
    for (SUDOKU_ID id_unchecked : ids_unchecked_) {
        possible_vals_[id_unchecked].clear();
        SUDOKU_VAL val = map_[id_unchecked];
        SUDOKU_ID id_row = id2row_id(id_unchecked);
        SUDOKU_ID id_column = id2column_id(id_unchecked);
        SUDOKU_ID id_block = id2block_id(id_unchecked);
        for (SUDOKU_ID id : ROW_IDS[id_row]) {
            if (id == id_unchecked)
                continue;
            possible_vals_[id].remove_val(val);
        }
        for (SUDOKU_ID id : COLUMN_IDS[id_column]) {
            if (id == id_unchecked)
                continue;
            possible_vals_[id].remove_val(val);
        }
        for (SUDOKU_ID id : BLOCK_IDS[id_block]) {
            if (id == id_unchecked)
                continue;
            possible_vals_[id].remove_val(val);
        }
    }
#if LOGGING
    cout << ids_found_.size() << " value(s) is/are used for update." << endl;
#endif
    if (ids_found_.size())
        ids_found_.clear();
}

/**
 * @brief For each block, check for each value whether that value
 * can lie only in specific row/column. If yes, unknown cells in
 * other block (of that same row/column) can not have that value
 */
void Sudoku::advanced_update() {
#if LOGGING
    cout << "Advanced update ..." << endl;
#endif
    // id of block, row and column: id_b, id_r, id_c
    for (SUDOKU_ID id_b = 0, id_r, id_c; id_b < S; id_b++) {
        for (SUDOKU_VAL val = 1; val <= S; val++) {
            id_r = 10;
            id_c = 10;
            // Check whether the value lies in one specific row/col
            for (SUDOKU_ID id : BLOCK_IDS[id_b]) {
                if (map_[id])   // Consider only unknown cells
                    continue;
                if (possible_vals_[id].check_val(val)) {
                    if (id_r == 10)
                        id_r = id2row_id(id);
                    else if (id_r < 10) {
                        if (id_r != id2row_id(id))
                            id_r = 20;
                    }
                    if (id_c == 10)
                        id_c = id2column_id(id);
                    else if (id_c < 10) {
                        if (id_c != id2column_id(id))
                            id_c = 20;
                    }
                }
            }
            // If yes, unknown cells of the same row/col can't have it
            if (id_r < 10) {
                for (SUDOKU_ID id : ROW_IDS[id_r]) {
                    if (map_[id])   // Consider only unknown cells
                        continue;
                    // Consider only cells of other block
                    if (id2block_id(id) == id_b)
                        continue;
                    possible_vals_[id].remove_val(val);
                }
            }
            if (id_c < 10) {
                for (SUDOKU_ID id : COLUMN_IDS[id_c]) {
                    if (map_[id])   // Consider only unknown cells
                        continue;
                    // Consider only cells of other block
                    if (id2block_id(id) == id_b)
                        continue;
                    possible_vals_[id].remove_val(val);
                }
            }
        }
    }
}

void Sudoku::fill_certain_values() {
    vector<std::vector<SUDOKU_ID>::iterator> to_delete;
    for (SUDOKU_ID id : ids_not_found_) {
        if (possible_vals_[id].get_N() != 1)
            continue;
#if LOGGING
        cout << "Fill cell " << id
             << " with " << possible_vals_[id].get_val() << endl;
#endif
        map_[id] = possible_vals_[id].get_val();
        ids_found_.push_back(id);
        ids_unchecked_.push_back(id);
        to_delete.push_back(find(begin(ids_not_found_), end(ids_not_found_), id));
    }

    reverse(to_delete.begin(), to_delete.end());
    for (auto it : to_delete)
        ids_not_found_.erase(it);
}

int Sudoku::get_num_found() const { return ids_found_.size(); }

int Sudoku::get_num_not_found() const { return ids_not_found_.size(); }

int Sudoku::get_num_unchecked() const { return ids_unchecked_.size(); }

void Sudoku::set_cell_value(
    const SUDOKU_ID &id, const SUDOKU_VAL &val)
{
    if (val < 0 || val > S) {
        cout << "Invalid value for a cell: " << val << endl;
        return;
    }
    if (id < 0 || id >= S_MAP) {
        cout << "Invalid id for a cell: " << id << endl;
        return;
    }
    
    if (map_[id] != 0 && val == 0) {
        ids_found_.erase(find(begin(ids_found_), end(ids_found_), id));
        ids_not_found_.push_back(id);
        auto it = find(begin(ids_unchecked_), end(ids_unchecked_), id);
        if (it != ids_unchecked_.end())
            ids_unchecked_.erase(it);
    } else if (map_[id] == 0 && val != 0) {
        ids_not_found_.erase(find(begin(ids_not_found_), end(ids_not_found_), id));
        ids_found_.push_back(id);
        ids_unchecked_.push_back(id);
    }
    map_[id] = val;
}

SUDOKU_VAL Sudoku::get_cell_value(const SUDOKU_ID &id) const {
    return map_[id];
}

void Sudoku::solve() {

    while (ids_found_.size()) {
        update_possible_values();
        advanced_update();
        fill_certain_values();
    }
    print();

    if (!ids_not_found_.empty())
        print_possible_values();

    // while (advanced_update) {
    //     while (update_possible_values)
    //         fill_certain_values();
    // }

#if LOGGING
    // print_possible_values();
#endif
}

#endif  // SUDOKU_SOLVER__SUDOKU_HPP_
