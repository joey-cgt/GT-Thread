#include <gtest/gtest.h>

int add(int a, int b){ return a+b;}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}