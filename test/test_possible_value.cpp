#include <string>
#include <gtest/gtest.h>

#include "../possible_value.hpp"


class testPossibleValue : public testing::Test
{
protected:
    possible_value p;
    std::string s;
    void SetUp() {};
    void TearDown() {};
};

TEST_F(testPossibleValue, TestConstructor)
{
    EXPECT_EQ(p.get_N(), 9);
    EXPECT_TRUE(p.check_val(0));
    EXPECT_TRUE(p.check_val(1));
    EXPECT_TRUE(p.check_val(2));
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(4));
    EXPECT_TRUE(p.check_val(5));
    EXPECT_TRUE(p.check_val(6));
    EXPECT_TRUE(p.check_val(7));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_TRUE(p.check_val(9));
}

TEST_F(testPossibleValue, TestGetN)
{
    EXPECT_EQ(p.get_N(), 9);

    testing::internal::CaptureStdout();
    p.remove_val(0);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(p.get_N(), 9);

    p.remove_val(2);
    EXPECT_EQ(p.get_N(), 8);

    p.remove_val(2);
    EXPECT_EQ(p.get_N(), 8);
    p.remove_val(7);
    EXPECT_EQ(p.get_N(), 7);

    testing::internal::CaptureStdout();
    p.remove_val(10);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(p.get_N(), 7);

    testing::internal::CaptureStdout();
    p.remove_val(0);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(p.get_N(), 7);

    p.remove_val(9);
    p.remove_val(5);
    EXPECT_EQ(p.get_N(), 5);
}

TEST_F(testPossibleValue, TestCheckVal)
{
    testing::internal::CaptureStdout();
    p.remove_val(0);
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(p.check_val(0));
    EXPECT_TRUE(p.check_val(1));
    EXPECT_TRUE(p.check_val(2));
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(4));
    EXPECT_TRUE(p.check_val(5));
    EXPECT_TRUE(p.check_val(6));
    EXPECT_TRUE(p.check_val(7));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_TRUE(p.check_val(9));

    testing::internal::CaptureStdout();
    p.remove_val(12);
    s = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(p.check_val(0));
    EXPECT_TRUE(p.check_val(1));
    EXPECT_TRUE(p.check_val(2));
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(4));
    EXPECT_TRUE(p.check_val(5));
    EXPECT_TRUE(p.check_val(6));
    EXPECT_TRUE(p.check_val(7));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_TRUE(p.check_val(9));

    p.remove_val(2);
    EXPECT_TRUE(p.check_val(0));
    EXPECT_TRUE(p.check_val(1));
    EXPECT_FALSE(p.check_val(2));
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(4));
    EXPECT_TRUE(p.check_val(5));
    EXPECT_TRUE(p.check_val(6));
    EXPECT_TRUE(p.check_val(7));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_TRUE(p.check_val(9));

    p.remove_val(9);
    EXPECT_TRUE(p.check_val(0));
    EXPECT_TRUE(p.check_val(1));
    EXPECT_FALSE(p.check_val(2));
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(4));
    EXPECT_TRUE(p.check_val(5));
    EXPECT_TRUE(p.check_val(6));
    EXPECT_TRUE(p.check_val(7));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_FALSE(p.check_val(9));

    p.remove_val(5);
    EXPECT_TRUE(p.check_val(0));
    EXPECT_TRUE(p.check_val(1));
    EXPECT_FALSE(p.check_val(2));
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(4));
    EXPECT_FALSE(p.check_val(5));
    EXPECT_TRUE(p.check_val(6));
    EXPECT_TRUE(p.check_val(7));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_FALSE(p.check_val(9));

    p.remove_val(7);
    EXPECT_TRUE(p.check_val(0));
    EXPECT_TRUE(p.check_val(1));
    EXPECT_FALSE(p.check_val(2));
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(4));
    EXPECT_FALSE(p.check_val(5));
    EXPECT_TRUE(p.check_val(6));
    EXPECT_FALSE(p.check_val(7));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_FALSE(p.check_val(9));

    p.remove_val(1);
    p.remove_val(2);
    p.remove_val(3);
    p.remove_val(4);
    p.remove_val(5);
    p.remove_val(6);
    p.remove_val(7);
    p.remove_val(8);
    p.remove_val(9);
    EXPECT_TRUE(p.check_val(0));
    EXPECT_FALSE(p.check_val(1));
    EXPECT_FALSE(p.check_val(2));
    EXPECT_FALSE(p.check_val(3));
    EXPECT_FALSE(p.check_val(4));
    EXPECT_FALSE(p.check_val(5));
    EXPECT_FALSE(p.check_val(6));
    EXPECT_FALSE(p.check_val(7));
    EXPECT_FALSE(p.check_val(8));
    EXPECT_FALSE(p.check_val(9));
}

TEST_F(testPossibleValue, TestRemoveValue)
{
    testing::internal::CaptureStdout();
    p.remove_val(0);
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");

    p.remove_val(1);
    EXPECT_EQ(p.get_N(), 8);
    EXPECT_FALSE(p.check_val(1));

    testing::internal::CaptureStdout();
    p.remove_val(10);
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");
    EXPECT_EQ(p.get_N(), 8);

    p.remove_val(1);
    EXPECT_EQ(p.get_N(), 8);
    EXPECT_FALSE(p.check_val(1));

    testing::internal::CaptureStdout();
    p.remove_val(20);
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");

    p.remove_val(2);
    p.remove_val(4);
    p.remove_val(9);
    EXPECT_EQ(p.get_N(), 5);
    EXPECT_TRUE(p.check_val(3));
    EXPECT_TRUE(p.check_val(8));
    EXPECT_FALSE(p.check_val(1));
    EXPECT_FALSE(p.check_val(2));
    EXPECT_FALSE(p.check_val(4));
    EXPECT_FALSE(p.check_val(9));
}

TEST_F(testPossibleValue, TestKeepOnlyValue)
{
    testing::internal::CaptureStdout();
    p.keep_only_val(0);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");

    p.keep_only_val(1);
    EXPECT_EQ(p.get_N(), 1);
    EXPECT_TRUE(p.check_val(1));

    testing::internal::CaptureStdout();
    p.keep_only_val(10);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");
    EXPECT_EQ(p.get_N(), 1);

    p.keep_only_val(1);
    EXPECT_EQ(p.get_N(), 1);
    EXPECT_TRUE(p.check_val(1));

    testing::internal::CaptureStdout();
    p.keep_only_val(20);
    s = testing::internal::GetCapturedStdout();
    EXPECT_EQ(s, "Error: Invalid value (not in range 1 to 9).\n");
    EXPECT_EQ(p.get_N(), 1);

    p.keep_only_val(2);
    EXPECT_TRUE(p.check_val(2));
    p.keep_only_val(4);
    EXPECT_TRUE(p.check_val(4));
    p.keep_only_val(9);
    EXPECT_TRUE(p.check_val(9));
    p.keep_only_val(2);
    p.keep_only_val(5);
    p.keep_only_val(7);
    p.keep_only_val(9);
    p.keep_only_val(2);
    EXPECT_TRUE(p.check_val(2));
    EXPECT_FALSE(p.check_val(0));
    EXPECT_FALSE(p.check_val(1));
    EXPECT_FALSE(p.check_val(3));
    EXPECT_FALSE(p.check_val(4));
    EXPECT_FALSE(p.check_val(5));
    EXPECT_FALSE(p.check_val(6));
    EXPECT_FALSE(p.check_val(7));
    EXPECT_FALSE(p.check_val(8));
    EXPECT_FALSE(p.check_val(9));
}

TEST_F(testPossibleValue, TestClear)
{
    p.clear();
    EXPECT_EQ(p.get_N(), 0);
    EXPECT_FALSE(p.check_val(9));
    EXPECT_FALSE(p.check_val(0));
    EXPECT_FALSE(p.check_val(1));
    EXPECT_FALSE(p.check_val(2));
    EXPECT_FALSE(p.check_val(3));
    EXPECT_FALSE(p.check_val(4));
    EXPECT_FALSE(p.check_val(5));
    EXPECT_FALSE(p.check_val(6));
    EXPECT_FALSE(p.check_val(7));
    EXPECT_FALSE(p.check_val(8));
    EXPECT_FALSE(p.check_val(9));
}

TEST_F(testPossibleValue, TestPrint)
{
    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "9 possible values: 1 2 3 4 5 6 7 8 9\n");

    testing::internal::CaptureStdout();
    p.remove_val(0);
    s = testing::internal::GetCapturedStdout();
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

    p.remove_val(4);
    p.remove_val(5);
    p.remove_val(7);
    p.remove_val(9);
    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "1 possible values: 2\n");

    p.remove_val(2);
    testing::internal::CaptureStdout();
    p.print();
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "0 possible values:\n");
}

TEST_F(testPossibleValue, TestGetVal1)
{
    p.remove_val(1);
    EXPECT_EQ(p.get_val().size(), 8);
    p.remove_val(2);
    EXPECT_EQ(p.get_val().size(), 7);
    p.remove_val(3);
    EXPECT_EQ(p.get_val().size(), 6);
    p.remove_val(4);
    EXPECT_EQ(p.get_val().size(), 5);
    p.remove_val(5);
    EXPECT_EQ(p.get_val().size(), 4);
    p.remove_val(6);
    EXPECT_EQ(p.get_val().size(), 3);
    p.remove_val(7);
    EXPECT_EQ(p.get_val().size(), 2);
    p.remove_val(8);
    EXPECT_EQ(p.get_val().size(), 1);
    EXPECT_EQ(p.get_val()[0], 9);
    p.remove_val(9);
    EXPECT_TRUE(p.get_val().empty());
}

TEST_F(testPossibleValue, TestGetVal2)
{
    p.remove_val(1);
    EXPECT_EQ(p.get_val().size(), 8);
    p.remove_val(3);
    EXPECT_EQ(p.get_val().size(), 7);
    p.remove_val(4);
    EXPECT_EQ(p.get_val().size(), 6);
    p.remove_val(5);
    EXPECT_EQ(p.get_val().size(), 5);
    p.remove_val(6);
    EXPECT_EQ(p.get_val().size(), 4);
    p.remove_val(7);
    EXPECT_EQ(p.get_val().size(), 3);
    p.remove_val(8);
    EXPECT_EQ(p.get_val().size(), 2);
    p.remove_val(9);
    EXPECT_EQ(p.get_val().size(), 1);
    EXPECT_EQ(p.get_val()[0], 2);
    p.remove_val(2);
    EXPECT_TRUE(p.get_val().empty());
}

TEST_F(testPossibleValue, TestGetVal3)
{
    p.remove_val(1);
    p.remove_val(3);
    p.remove_val(4);
    p.remove_val(5);
    p.remove_val(6);
    p.remove_val(7);
    p.remove_val(8);
    EXPECT_EQ(p.get_val().size(), 2);
    EXPECT_EQ(p.get_val()[0], 2);
    EXPECT_EQ(p.get_val()[1], 9);
}

TEST_F(testPossibleValue, TestGetVal4)
{
    p.remove_val(1);
    p.remove_val(2);
    p.remove_val(3);
    p.remove_val(4);
    p.remove_val(6);
    p.remove_val(8);
    p.remove_val(9);
    EXPECT_EQ(p.get_val().size(), 2);
    EXPECT_EQ(p.get_val()[0], 5);
    EXPECT_EQ(p.get_val()[1], 7);
}

int main(int argc, char ** argv)
{
    // Start testing
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
