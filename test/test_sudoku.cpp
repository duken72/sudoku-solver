#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

#include "sudoku.hpp"


class testSudoku : public testing::Test
{
protected:
    const size_t npos = std::string::npos;
    std::string s;
    Sudoku game;
    SUDOKU_VAL input1[S_MAP] = {0, 0, 0, 0, 1, 0, 0, 0, 0,
                                0, 9, 0, 0, 0, 0, 6, 4, 7,
                                0, 2, 6, 7, 0, 9, 0, 0, 0,
                                0, 6, 4, 8, 0, 0, 0, 3, 0,
                                0, 0, 3, 0, 5, 0, 9, 0, 0,
                                0, 1, 0, 0, 0, 3, 4, 5, 0,
                                0, 0, 0, 4, 0, 2, 8, 1, 0,
                                4, 3, 2, 0, 0, 0, 0, 6, 0,
                                0, 0, 0, 0, 6, 0, 0, 0, 0};
    SUDOKU_VAL input2[S_MAP] = {8, 0, 0, 1, 0, 0, 0, 0, 0,
                                5, 0, 7, 2, 3, 0, 9, 0, 0,
                                0, 0, 2, 0, 0, 8, 0, 0, 5,
                                0, 0, 0, 5, 0, 0, 2, 1, 0,
                                0, 0, 8, 0, 0, 0, 5, 0, 0,
                                0, 6, 5, 0, 0, 4, 0, 0, 0,
                                7, 0, 0, 8, 0, 0, 4, 0, 0,
                                0, 0, 1, 0, 6, 5, 3, 0, 2,
                                0, 0, 0, 0, 0, 9, 0, 0, 8};
    void SetUp() {};
    void TearDown() {};
};

TEST_F(testSudoku, TestConstructor)
{
    testing::internal::CaptureStdout();
    game.print();
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos != s.find("1 2 3   4 5 6   7 8 9"));
    EXPECT_TRUE(npos != s.find("2|       |       |       |"));
    EXPECT_TRUE(npos != s.find("5|       |       |       |"));
    EXPECT_TRUE(npos != s.find("7|       |       |       |"));
    EXPECT_TRUE(npos != s.find("9|       |       |       |"));
    EXPECT_TRUE(npos != s.find("-------------------------"));
    EXPECT_EQ(game.get_num_found(), 0);
}

TEST_F(testSudoku, TestConvertID2RowID)
{
    EXPECT_EQ(Sudoku::id2row_id(2), 0);
    EXPECT_EQ(Sudoku::id2row_id(14), 1);
    EXPECT_EQ(Sudoku::id2row_id(27), 3);
    EXPECT_EQ(Sudoku::id2row_id(42), 4);
    EXPECT_EQ(Sudoku::id2row_id(47), 5);
    EXPECT_EQ(Sudoku::id2row_id(57), 6);
    EXPECT_EQ(Sudoku::id2row_id(72), 8);
    EXPECT_EQ(Sudoku::id2row_id(79), 8);

    testing::internal::CaptureStdout();
    EXPECT_EQ(Sudoku::id2row_id(92), ERROR);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid value for id (Out of range).\n");

    testing::internal::CaptureStdout();
    EXPECT_EQ(Sudoku::id2row_id(81), ERROR);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid value for id (Out of range).\n");
}

TEST_F(testSudoku, TestConvertID2ColumnID)
{
    EXPECT_EQ(Sudoku::id2column_id(2), 2);
    EXPECT_EQ(Sudoku::id2column_id(14), 5);
    EXPECT_EQ(Sudoku::id2column_id(27), 0);
    EXPECT_EQ(Sudoku::id2column_id(42), 6);
    EXPECT_EQ(Sudoku::id2column_id(47), 2);
    EXPECT_EQ(Sudoku::id2column_id(57), 3);
    EXPECT_EQ(Sudoku::id2column_id(72), 0);
    EXPECT_EQ(Sudoku::id2column_id(79), 7);

    testing::internal::CaptureStdout();
    EXPECT_EQ(Sudoku::id2column_id(92), ERROR);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid value for id (Out of range).\n");

    testing::internal::CaptureStdout();
    EXPECT_EQ(Sudoku::id2column_id(81), ERROR);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid value for id (Out of range).\n");
}

TEST_F(testSudoku, TestConvertID2BlockID)
{
    EXPECT_EQ(Sudoku::id2block_id(2), 0);
    EXPECT_EQ(Sudoku::id2block_id(14), 1);
    EXPECT_EQ(Sudoku::id2block_id(27), 3);
    EXPECT_EQ(Sudoku::id2block_id(42), 5);
    EXPECT_EQ(Sudoku::id2block_id(47), 3);
    EXPECT_EQ(Sudoku::id2block_id(57), 7);
    EXPECT_EQ(Sudoku::id2block_id(72), 6);
    EXPECT_EQ(Sudoku::id2block_id(79), 8);

    testing::internal::CaptureStdout();
    EXPECT_EQ(Sudoku::id2block_id(92), ERROR);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid value for id (Out of range).\n");

    testing::internal::CaptureStdout();
    EXPECT_EQ(Sudoku::id2block_id(81), ERROR);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid value for id (Out of range).\n");
}

TEST_F(testSudoku, TestGetMap)
{
    game.get_map(input1);
    testing::internal::CaptureStdout();
    game.print();
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos != s.find("1 2 3   4 5 6   7 8 9"));
    EXPECT_TRUE(npos != s.find("2|   9   |       | 6 4 7 |"));
    EXPECT_TRUE(npos != s.find("5|     3 |   5   | 9     |"));
    EXPECT_TRUE(npos != s.find("7|       | 4   2 | 8 1   |"));
    EXPECT_TRUE(npos != s.find("9|       |   6   |       |"));
    EXPECT_TRUE(npos != s.find("-------------------------"));
    EXPECT_EQ(game.get_num_found(), 29);
}

TEST_F(testSudoku, TestGetMapInvalid)
{
    SUDOKU_VAL input[S_MAP] = { 0, 0, 0, 0, 1, 0, 0, 0, 0,
                                0, 9, 0, 0, 0, 0, 6, 4, 7,
                                0, 2, 6, 7, 0, 9, 0, 0, 0,
                                0, 6, 4, 8, 12, 0, 0, 3, 0,
                                0, 0, 3, 0, 5, 0, 9, 0, 0,
                                0, 1, 0, 0, 0, 3, 4, 5, 0,
                                0, 0, 0, 4, 0, 2, 8, 1, 0,
                                4, 3, 2, 0, 0, 0, 0, 6, 0,
                                0, 0, 0, 0, 6, 0, 0, 0, 0};
    testing::internal::CaptureStdout();
    game.get_map(input);
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos != s.find("Invalid value for a cell: 12"));

    testing::internal::CaptureStdout();
    game.print();
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos != s.find("4|   6 4 | 8     |       |"));
    EXPECT_TRUE(npos == s.find("5|     3 |   5   | 9     |"));
    EXPECT_TRUE(npos == s.find("7|       | 4   2 | 8 1   |"));
    EXPECT_TRUE(npos == s.find("9|       |   6   |       |"));
    EXPECT_EQ(game.get_num_found(), 12);
}

TEST_F(testSudoku, TestPrintPossibleValues1)
{
    game.get_map(input1);
    testing::internal::CaptureStdout();
    game.update_group();
    game.print_possible_values();
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos != s.find("Cell 14 with 2 possible values: 5 8"));
    EXPECT_TRUE(npos != s.find("Cell 27 with 4 possible values: 2 5 7 9"));
    EXPECT_TRUE(npos != s.find("Cell 79 with 3 possible values: 2 7 9"));
    EXPECT_TRUE(npos == s.find("Cell 10"));
    EXPECT_TRUE(npos == s.find("Cell 42"));
    EXPECT_TRUE(npos == s.find("Cell 63"));
}

TEST_F(testSudoku, TestPrintPossibleValues2)
{
    game.get_map(input2);
    testing::internal::CaptureStdout();
    game.update_group();
    game.print_possible_values();
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos != s.find("Cell 1 with 3 possible values: 3 4 9"));
    EXPECT_TRUE(npos != s.find("Cell 14 with 1 possible values: 6"));
    EXPECT_TRUE(npos != s.find("Cell 58 with 2 possible values: 1 2"));
    EXPECT_TRUE(npos == s.find("Cell 0"));
    EXPECT_TRUE(npos == s.find("Cell 80"));
    EXPECT_TRUE(npos == s.find("Cell 77"));
}

TEST_F(testSudoku, TestUpdateGroup1)
{
    SUDOKU_VAL input[S_MAP] = { 8, 9, 3, 1, 5, 7, 6, 2, 4,
                                5, 4, 7, 2, 3, 6, 9, 8, 1,
                                6, 1, 2, 9, 4, 8, 7, 3, 5,
                                4, 7, 9, 8, 5, 3, 2, 1, 6,
                                3, 2, 8, 6, 9, 1, 5, 4, 7,
                                1, 6, 5, 7, 2, 4, 8, 9, 3,
                                7, 3, 6, 8, 1, 2, 4, 5, 9,
                                9, 8, 1, 4, 6, 5, 3, 7, 2,
                                2, 5, 4, 3, 7, 9, 1, 6, 8};
    game.get_map(input);
    testing::internal::CaptureStdout();
    game.update_group();
    game.print_possible_values();
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos == s.find("Cell"));
    EXPECT_TRUE(npos == s.find("with"));
}

TEST_F(testSudoku, TestUpdateGroup2)
{
    SUDOKU_VAL input[S_MAP] = { 8, 9, 3, 1, 5, 7, 6, 0, 4,
                                5, 4, 7, 2, 3, 6, 9, 8, 1,
                                6, 1, 2, 9, 4, 8, 7, 3, 5,
                                4, 7, 9, 8, 5, 3, 2, 1, 6,
                                3, 2, 8, 6, 9, 1, 5, 4, 7,
                                1, 6, 5, 7, 2, 4, 8, 9, 3,
                                7, 3, 6, 8, 1, 2, 4, 5, 9,
                                9, 8, 1, 4, 6, 5, 3, 7, 2,
                                2, 5, 4, 3, 7, 9, 1, 0, 8};
    game.get_map(input);
    testing::internal::CaptureStdout();
    game.update_group();
    game.print_possible_values();
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(npos != s.find("Cell 7 with 1 possible values: 2"));
    EXPECT_TRUE(npos != s.find("Cell 79 with 1 possible values: 6"));
    cout << s << endl;
}

TEST_F(testSudoku, TestGetCellValue)
{
    game.get_map(input1);
    EXPECT_EQ(game.get_cell_value(2), 0);
    EXPECT_EQ(game.get_cell_value(10), 9);
    EXPECT_EQ(game.get_cell_value(63), 4);
    EXPECT_EQ(game.get_cell_value(76), 6);
}

TEST_F(testSudoku, TestSetCellValue)
{
    game.get_map(input1);

    // Invalid value
    testing::internal::CaptureStdout();
    game.set_cell_value(72, 10);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid value for a cell: 10\n");

    // Invalid id
    testing::internal::CaptureStdout();
    game.set_cell_value(92, 9);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Invalid id for a cell: 92\n");

    EXPECT_EQ(game.get_num_found(), 29);

    // Valid setting, unknown to known cell
    EXPECT_EQ(game.get_cell_value(1), 0);
    game.set_cell_value(1, 4);
    EXPECT_EQ(game.get_cell_value(1), 4);
    EXPECT_EQ(game.get_num_found(), 30);

    // Valid setting, no change 1
    EXPECT_EQ(game.get_cell_value(9), 0);
    game.set_cell_value(9, 0);
    EXPECT_EQ(game.get_cell_value(9), 0);
    EXPECT_EQ(game.get_num_found(), 30);

    // Valid setting, no change 2
    EXPECT_EQ(game.get_cell_value(42), 9);
    game.set_cell_value(42, 9);
    EXPECT_EQ(game.get_cell_value(42), 9);
    EXPECT_EQ(game.get_num_found(), 30);

    // Valid setting, known to unknown cell
    EXPECT_EQ(game.get_cell_value(4), 1);
    game.set_cell_value(4, 0);
    EXPECT_EQ(game.get_cell_value(4), 0);
    EXPECT_EQ(game.get_num_found(), 29);
}

TEST_F(testSudoku, TestUniqueUpdate)
{}

TEST_F(testSudoku, TestDuoUpdate)
{}

TEST_F(testSudoku, TestFillValues)
{}

TEST_F(testSudoku, TestSolve)
{}

int main(int argc, char ** argv)
{
    // Start testing
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
