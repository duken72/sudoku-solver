#include <string>
#include <gtest/gtest.h>

#include "../possible_value.hpp"

using std::string;

class testPossibleValue : public testing::Test
{
protected:
    possible_value p;
    string s;
    void SetUp() {};
    void TearDown() {};
};
// std::string output = testing::internal::GetCapturedStdout();

TEST_F(testPossibleValue, TestConstructor)
{
    EXPECT_EQ(p._N, 9);
    ASSERT_EQ(p._possibilities.size(), 10);
    EXPECT_EQ(p._possibilities[0], 1);
    EXPECT_EQ(p._possibilities[1], 1);
    EXPECT_EQ(p._possibilities[2], 1);
    EXPECT_EQ(p._possibilities[3], 1);
    EXPECT_EQ(p._possibilities[4], 1);
    EXPECT_EQ(p._possibilities[5], 1);
    EXPECT_EQ(p._possibilities[6], 1);
    EXPECT_EQ(p._possibilities[7], 1);
    EXPECT_EQ(p._possibilities[8], 1);
    EXPECT_EQ(p._possibilities[9], 1);
}

TEST_F(testPossibleValue, TestRemoveValue)
{
    testing::internal::CaptureStdout();
    p.remove_val(0);
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");

    p.remove_val(1);
    EXPECT_EQ(p._N, 8);
    ASSERT_EQ(p._possibilities[1], 0);

    testing::internal::CaptureStdout();
    p.remove_val(10);
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");
    EXPECT_EQ(p._N, 8);

    p.remove_val(1);
    EXPECT_EQ(p._N, 8);
    ASSERT_EQ(p._possibilities[1], 0);

    testing::internal::CaptureStdout();
    p.remove_val(20);
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");

    p.remove_val(2);
    p.remove_val(4);
    p.remove_val(9);
    EXPECT_EQ(p._N, 5);
    ASSERT_EQ(p._possibilities[2], 0);
    ASSERT_EQ(p._possibilities[4], 0);
    ASSERT_EQ(p._possibilities[9], 0);
}

TEST_F(testPossibleValue, TestClear)
{
    EXPECT_EQ(p._N, 9);
    ASSERT_EQ(p._possibilities.size(), 10);
    EXPECT_EQ(p._possibilities[0], 1);
    EXPECT_EQ(p._possibilities[1], 1);

    p.clear();

    EXPECT_EQ(p._N, 0);
    ASSERT_EQ(p._possibilities.size(), 10);
    EXPECT_EQ(p._possibilities[0], 0);
    EXPECT_EQ(p._possibilities[1], 0);
    EXPECT_EQ(p._possibilities[2], 0);
    EXPECT_EQ(p._possibilities[3], 0);
    EXPECT_EQ(p._possibilities[4], 0);
    EXPECT_EQ(p._possibilities[5], 0);
    EXPECT_EQ(p._possibilities[6], 0);
    EXPECT_EQ(p._possibilities[7], 0);
    EXPECT_EQ(p._possibilities[8], 0);
    EXPECT_EQ(p._possibilities[9], 0);
}

TEST_F(testPossibleValue, TestPrint)
{
    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "9 possible values: 1 2 3 4 5 6 7 8 9\n");

    EXPECT_EQ(p._N, 9);
    ASSERT_EQ(p._possibilities.size(), 10);
    EXPECT_EQ(p._possibilities[1], 1);
    EXPECT_EQ(p._possibilities[2], 1);
    EXPECT_EQ(p._possibilities[9], 1);

    testing::internal::CaptureStdout();
    p.remove_val(0);
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");

    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "9 possible values: 1 2 3 4 5 6 7 8 9\n");

    p.remove_val(1);
    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "8 possible values: 2 3 4 5 6 7 8 9\n");

    p.remove_val(1);
    p.remove_val(3);
    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "7 possible values: 2 4 5 6 7 8 9\n");

    p.remove_val(8);
    p.remove_val(6);
    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "5 possible values: 2 4 5 7 9\n");
}

// TEST(TestPossibleValue, TestConstructor2)
// {
//     possible_value p;
//     EXPECT_EQ(p._N, 9);
//     ASSERT_EQ(p._possibilities.size(), 10);
//     EXPECT_EQ(p._possibilities[9], 1);
// }

int main(int argc, char ** argv)
{
    // Start testing
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
