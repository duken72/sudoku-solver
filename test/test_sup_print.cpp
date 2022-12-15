#include <string>
#include <vector>
#include <gtest/gtest.h>

#include "sup_print.hpp"


class testSupportPrint : public testing::Test
{
protected:
    std::string s;
    
    void SetUp() {};
    void TearDown() {};
};

TEST_F(testSupportPrint, TestPrint1)
{
    int n = 5;
    std::vector<int> vectI(n, 7);

    testing::internal::CaptureStdout();
    std::cout << vectI;
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Vector: 7 7 7 7 7 ");

    vectI.push_back(5);
    testing::internal::CaptureStdout();
    std::cout << vectI;
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Vector: 7 7 7 7 7 5 ");

    vectI.push_back(9);
    testing::internal::CaptureStdout();
    std::cout << vectI;
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Vector: 7 7 7 7 7 5 9 ");
}

TEST_F(testSupportPrint, TestPrint2)
{
    std::vector<unsigned short> vectS{ 2, 5, 7, 9 };
    testing::internal::CaptureStdout();
    std::cout << vectS;
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Vector: 2 5 7 9 ");
}

TEST_F(testSupportPrint, TestPrint3)
{
    std::vector<unsigned short> vectS{ 72, 79, 92, 97 };
    testing::internal::CaptureStdout();
    std::cout << vectS;
    s = testing::internal::GetCapturedStdout();
    ASSERT_EQ(s, "Vector: 72 79 92 97 ");
}

int main(int argc, char ** argv)
{
    // Start testing
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
