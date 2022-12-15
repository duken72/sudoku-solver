#include <gtest/gtest.h>

#include "typedef.hpp"

class testTypeDef : public testing::Test
{
protected:
    const size_t npos = std::string::npos;
    SUDOKU_VAL sum = 0;

    void SetUp() {};
    void TearDown() {};
};

TEST_F(testTypeDef, TestConst) {
    EXPECT_EQ(S, 9);
    EXPECT_EQ(S_MAP, 81);
    EXPECT_EQ(VALID, 10);
    EXPECT_EQ(ERROR, 20);
}

TEST_F(testTypeDef, TestROW_IDS)
{
    EXPECT_EQ(ROW_IDS[0][2], 2);
    EXPECT_EQ(ROW_IDS[5][7], 52);
    for (int r = 0; r < S; r++) {
        sum = 0;
        for (int i = 0; i < S; i++)
            sum += ROW_IDS[r][i];
        EXPECT_EQ(sum, (ROW_IDS[r][0] + ROW_IDS[r][8]) * S / 2);
    }
}

TEST_F(testTypeDef, TestCOLUMN_IDS)
{
    EXPECT_EQ(COLUMN_IDS[0][2], 18);
    EXPECT_EQ(COLUMN_IDS[5][7], 68);

    for (int c = 0; c < S; c++) {
        sum = 0;
        for (int i = 0; i < S; i++)
            sum += ROW_IDS[c][i];
        EXPECT_EQ(sum, (ROW_IDS[c][0] + ROW_IDS[c][8]) * S / 2);
    }
}

TEST_F(testTypeDef, TestBLOCK_IDS)
{
    EXPECT_EQ(BLOCK_IDS[0][2], 2);
    EXPECT_EQ(BLOCK_IDS[5][7], 52);

    for (int b = 0; b < S; b++) {
        sum = 0;
        for (int i = 0; i < S; i++)
            sum += ROW_IDS[b][i];
        EXPECT_EQ(sum, (ROW_IDS[b][1] + ROW_IDS[b][4] + ROW_IDS[b][7]) * 3);
    }
}

int main(int argc, char ** argv)
{
    // Start testing
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
