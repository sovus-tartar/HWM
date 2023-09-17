#include <gtest/gtest.h>
#include <iostream>

#include "../include/matrix.hpp"

TEST(matrix_base, init_test)
{
    MyMatrix::Matrix<double> A(2, 3);

    A[0][0] = 1.0;
    A[0][1] = 2.0;
    A[0][2] = 3.0;
    A[1][0] = 4.0;
    A[1][1] = 5.0;
    A[1][2] = 6.0;

    EXPECT_DOUBLE_EQ(A[0][0], 1.0);
    EXPECT_DOUBLE_EQ(A[0][1], 2.0);
    EXPECT_DOUBLE_EQ(A[0][2], 3.0);
    EXPECT_DOUBLE_EQ(A[1][0], 4.0);
    EXPECT_DOUBLE_EQ(A[1][1], 5.0);
    EXPECT_DOUBLE_EQ(A[1][2], 6.0);


}

TEST(matrix_base, switch_collumnes)
{

    MyMatrix::Matrix<double> A(2, 3);

    A[0][0] = 1.0; // 1 2 3
    A[0][1] = 2.0; // 4 5 6
    A[0][2] = 3.0;
    A[1][0] = 4.0;
    A[1][1] = 5.0;
    A[1][2] = 6.0;

    A.switch_collumnes(0, 2);
    // 3 2 1
    // 6 5 4

    EXPECT_DOUBLE_EQ(A[0][0], 3.0);
    EXPECT_DOUBLE_EQ(A[0][1], 2.0);
    EXPECT_DOUBLE_EQ(A[0][2], 1.0);
    EXPECT_DOUBLE_EQ(A[1][0], 6.0);
    EXPECT_DOUBLE_EQ(A[1][1], 5.0);
    EXPECT_DOUBLE_EQ(A[1][2], 4.0);
    
}

TEST(matrix_base, switch_lines)
{
    MyMatrix::Matrix<double> A(2, 3);

    A[0][0] = 1.0; // 1 2 3
    A[0][1] = 2.0; // 4 5 6
    A[0][2] = 3.0;
    A[1][0] = 4.0;
    A[1][1] = 5.0;
    A[1][2] = 6.0;

    A.switch_strings(0, 1);
    // 4 5 6
    // 1 2 3

    EXPECT_DOUBLE_EQ(A[0][0], 4.0);
    EXPECT_DOUBLE_EQ(A[0][1], 5.0);
    EXPECT_DOUBLE_EQ(A[0][2], 6.0);
    EXPECT_DOUBLE_EQ(A[1][0], 1.0);
    EXPECT_DOUBLE_EQ(A[1][1], 2.0);
    EXPECT_DOUBLE_EQ(A[1][2], 3.0);


   // EXPECT_EQ(1, 1);
}
