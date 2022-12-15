#ifndef SUDOKU_SOLVER__SUDOKU_HPP_
#define SUDOKU_SOLVER__SUDOKU_HPP_

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>

#include "typedef.hpp"
#include "sup_print.hpp"
#include "possible_value.hpp"

#define LOGGING false

using std::cin, std::cout, std::endl;
using std::vector, std::array, std::pair, std::make_pair;

// TODO: Add namespace to packaging

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

    void set_cell_value(const SUDOKU_ID &id, const SUDOKU_VAL &val);
    SUDOKU_VAL get_cell_value(const SUDOKU_ID &id) const;
    bool is_possible(const SUDOKU_ID &id, const SUDOKU_VAL &val) const;

    void print() const;                 // print the map
    void print_possible_values() const; // print cells' possible values

    void update_group();
    void update_unique();
    void update_duo();
    void update_block();
    // Fill cells with only 1 possible values
    void fill_certain_values();
    bool backtracking(const std::vector<SUDOKU_ID>::iterator &it);
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

// Update possible values of a cell based on found values
// of other cells in the same row, column or block 
void Sudoku::update_group()
{
    if (ids_unchecked_.empty())
        return;

#if LOGGING
    cout << ids_unchecked_.size() << " value(s) is/are used for update." << endl;
#endif

    // Lambda function to remove possible values of unknown cells
    // of the same group
    auto rm_possible_val = [&](
        const SUDOKU_ID group_ids[S][S], SUDOKU_ID id_g, SUDOKU_VAL val)
    {
        for (SUDOKU_ID id : group_ids[id_g]) {
            if (map_[id] == 0)
                possible_vals_[id].remove_val(val);
        }
    };

    for (SUDOKU_ID id_unchecked : ids_unchecked_) {
        possible_vals_[id_unchecked].clear();
        SUDOKU_VAL val = map_[id_unchecked];
        SUDOKU_ID id_row = id2row_id(id_unchecked);
        SUDOKU_ID id_column = id2column_id(id_unchecked);
        SUDOKU_ID id_block = id2block_id(id_unchecked);

        rm_possible_val(ROW_IDS, id_row, val);
        rm_possible_val(COLUMN_IDS, id_column, val);
        rm_possible_val(BLOCK_IDS, id_block, val);
    }
    ids_unchecked_.clear();
}

/**
 * If in a group (row, column, block), there is only one cell
 * can take a missing value, then the only possible value for
 * that cell is that missing value.
 */
void Sudoku::update_unique()
{
    auto keep_unique_val = [&](const SUDOKU_ID group_ids[S][S])
    {
        for (int id_g = 0; id_g < S; id_g++) {  // id of group in groups
            SUDOKU_VAL num_cells[S] = { 0 };
            SUDOKU_ID id_cells[S] = { 0 };
            for (SUDOKU_VAL val = 1; val <= S; val++) {
                for (SUDOKU_ID id : group_ids[id_g]) {
                    if (map_[id])               // only unknown cells
                        continue;
                    if (!possible_vals_[id].check_val(val))
                        continue;
                    num_cells[val-1]++;
                    id_cells[val-1] = id;
                }
            }
            for (SUDOKU_VAL val = 1; val <= S; val++) {
                if (num_cells[val-1] == 1) {
                    SUDOKU_ID id = id_cells[val-1];
                    possible_vals_[id].keep_only_val(val);
                }
            }
        }
    };
    keep_unique_val(ROW_IDS);
    keep_unique_val(COLUMN_IDS);
    keep_unique_val(BLOCK_IDS);
}

/**
 * If in a group (row, column, block), there are two cells with
 * the same two possible values, then other cells in that group
 * can not have these two values.
 */
void Sudoku::update_duo()
{
    auto find_duo = [&](const SUDOKU_ID group_ids[S][S])
    {
        // vector of cell ids with exactly two possible values
        vector<SUDOKU_ID> id_duos;
        vector<pair<SUDOKU_ID, SUDOKU_ID>> id_duo_pair;

        for (int id_g = 0; id_g < S; id_g++) {
            id_duos.clear();
            id_duo_pair.clear();
            for (SUDOKU_ID id : group_ids[id_g]) {
                if (map_[id])       // only unknown cells
                    continue;
                if (possible_vals_[id].get_N() == 2)
                    id_duos.push_back(id);
            }
            int N = id_duos.size();
            if (N < 2)
                continue;
            for (int i = 0; i < N - 1; i++) {
                for (int j = i+1; j < N; j++) {
                    if (!(possible_vals_[id_duos[i]] == possible_vals_[id_duos[j]]))
                        continue;
                    id_duo_pair.push_back(make_pair(id_duos[i], id_duos[j]));
                }
            }
            if (id_duo_pair.empty())
                continue;
            for (auto [id1, id2] : id_duo_pair) {
                SUDOKU_VAL val1 = possible_vals_[id1].get_val()[0];
                SUDOKU_VAL val2 = possible_vals_[id1].get_val()[1];
#if LOGGING
                cout << "Pair " << id1 << " " << id2 << " " << id_g
                        << " " << val1 << " " << val2 << endl;
#endif
                for (SUDOKU_ID id : group_ids[id_g]) {
                    if (map_[id] || (id == id1) || (id == id2))
                        continue;
                    possible_vals_[id].remove_val(val1);
                    possible_vals_[id].remove_val(val2);
                }
            }
        }
    };

    find_duo(ROW_IDS);
    find_duo(COLUMN_IDS);
    find_duo(BLOCK_IDS);
}

// TODO
// void Sudoku::update_trio() {}

/**
 * For each block, check for each value whether that value
 * can lie only in specific row/column. If yes, unknown cells in
 * other block (of that same row/column), and other unknown cells
 * in the same block also can not have that value.
 */
void Sudoku::update_block()
{
    // id of current block, row and column of unknown value.
    SUDOKU_ID id_b, id_r, id_c;
    for (id_b = 0; id_b < S; id_b++) {
        for (SUDOKU_VAL val = 1; val <= S; val++) {
            id_r = VALID;
            id_c = VALID;
            // Check whether the value lies in one specific row/col
            for (SUDOKU_ID id : BLOCK_IDS[id_b]) {
                if (map_[id])   // Consider only unknown cells
                    continue;
                if (possible_vals_[id].check_val(val)) {
                    if (id_r == VALID)
                        id_r = id2row_id(id);
                    else if (id_r < VALID) {
                        if (id_r != id2row_id(id))
                            id_r = ERROR;
                    }
                    if (id_c == VALID)
                        id_c = id2column_id(id);
                    else if (id_c < VALID) {
                        if (id_c != id2column_id(id))
                            id_c = ERROR;
                    }
                }
            }
            // Unknown cells (same row/column/block) can't have that value
            // id_r, ROW_IDS, id2row_id
            if (id_r < VALID) {
                // cout << "Value " << val
                //      << " block " << id_b
                //      << " row " << id_r << endl;
                for (SUDOKU_ID id : ROW_IDS[id_r]) {
                    // Consider only unknown cells of other block
                    if (map_[id] || id2block_id(id) == id_b)
                        continue;
                    possible_vals_[id].remove_val(val);
                }
                for (SUDOKU_ID id : BLOCK_IDS[id_b]) {
                    // Consider only unknown cells of other row
                    if (map_[id] || id2row_id(id) == id_r)
                        continue;
                    possible_vals_[id].remove_val(val);
                }
            }
            if (id_c < VALID) {
                // cout << "Value " << val
                //      << " block " << id_b
                //      << " col " << id_c << endl;
                for (SUDOKU_ID id : COLUMN_IDS[id_c]) {
                    // Consider only unknown cells of other block
                    if (map_[id] || id2block_id(id) == id_b)
                        continue;
                    possible_vals_[id].remove_val(val);
                }
                for (SUDOKU_ID id : BLOCK_IDS[id_b]) {
                    // Consider only unknown cells of other row
                    if (map_[id] || id2column_id(id) == id_c)
                        continue;
                    possible_vals_[id].remove_val(val);
                }
            }
            // Unknown cells of the same block can't have that value??
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
             << " with " << possible_vals_[id].get_val()[0] << endl;
#endif
        map_[id] = possible_vals_[id].get_val()[0];
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

bool Sudoku::is_possible(
    const SUDOKU_ID &idIn, const SUDOKU_VAL &val) const
{
    // cout << "Checking " << val << " at " << idIn << endl;
    // Lambda function checking other any other cells has that value
    auto check_collision = [&](
        const SUDOKU_ID group_ids[S][S], SUDOKU_ID id_g)
    {
        for (SUDOKU_ID id : group_ids[id_g]) {
            if (id == idIn)
                continue;
            if (map_[id] == val)
                return true;
        }
        return false;
    };
    if (check_collision(ROW_IDS, id2row_id(idIn)))
        return false;
    if (check_collision(COLUMN_IDS, id2column_id(idIn)))
        return false;
    if (check_collision(BLOCK_IDS, id2block_id(idIn)))
        return false;
    return true;
}

SUDOKU_VAL Sudoku::get_cell_value(const SUDOKU_ID &id) const {
    return map_[id];
}

bool Sudoku::backtracking(const std::vector<SUDOKU_ID>::iterator &it)
{
    if (it == ids_not_found_.end())
        return true;
    SUDOKU_ID id = *it;
    if (map_[id])
        return backtracking(it + 1);
    for (SUDOKU_VAL val = 1; val <= S; val++) {
        if (is_possible(id, val)) {
            map_[id] = val;
            if (backtracking(it + 1))
                return true;
        }
        map_[id] = 0;
    }
    return false;   
}

void Sudoku::solve()
{
    while (ids_unchecked_.size()) {
        update_group();
        update_unique();
        update_block();
        update_duo();
        fill_certain_values();
    }
    backtracking(ids_not_found_.begin());
    print();
}

#endif  // SUDOKU_SOLVER__SUDOKU_HPP_
