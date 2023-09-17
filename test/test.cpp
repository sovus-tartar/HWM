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



}

TEST(SquareMatrix, get_pivot1)
{
    MyMatrix::SquareMatrix<double> A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 4;
    A[1][1] = 5;
    A[1][2] = 6;
    A[2][0] = 7;
    A[2][1] = 8;
    A[2][2] = 9;

    MyMatrix::Point t = MyMatrix::SquareMatrixTest::test_pivot(A, 0, 0);

    EXPECT_EQ(t.x, 2);
    EXPECT_EQ(t.y, 2);
    
}

TEST(SquareMatrix, get_pivot2)
{
    MyMatrix::SquareMatrix<double> A(3);
    A[0][0] = 4;
    A[0][1] = 8;
    A[0][2] = 16;
    A[1][0] = 3;
    A[1][1] = 6;
    A[1][2] = 9;
    A[2][0] = 1;
    A[2][1] = 4;
    A[2][2] = 13;

    MyMatrix::Point t = MyMatrix::SquareMatrixTest::test_pivot(A, 0, 0);

    EXPECT_EQ(t.x, 0);
    EXPECT_EQ(t.y, 2);
    
}

TEST(SquareMatrix, eliminate)
{
    MyMatrix::SquareMatrix<double> A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    MyMatrix::SquareMatrixTest::test_eliminate(A, 0);

    EXPECT_DOUBLE_EQ(A[0][0], 1);    
    EXPECT_DOUBLE_EQ(A[0][1], 2);
    EXPECT_DOUBLE_EQ(A[0][2], 3);
    EXPECT_DOUBLE_EQ(A[1][0], 0);
    EXPECT_DOUBLE_EQ(A[1][1], 0);
    EXPECT_DOUBLE_EQ(A[1][2], 0);
    EXPECT_DOUBLE_EQ(A[2][0], 0);
    EXPECT_DOUBLE_EQ(A[2][1], 0);
    EXPECT_DOUBLE_EQ(A[2][2], 0);
}

TEST(Matrix, operator_equal1)
{
    MyMatrix::SquareMatrix A(3);
    MyMatrix::SquareMatrix B(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    B[0][0] = 1;
    B[0][1] = 2;
    B[0][2] = 3;
    B[1][0] = 2;
    B[1][1] = 4;
    B[1][2] = 6;
    B[2][0] = 3;
    B[2][1] = 6;
    B[2][2] = 9;

    EXPECT_TRUE(A == B);
}
TEST(Matrix, operator_equal2)
{
    MyMatrix::SquareMatrix A(3);
    MyMatrix::SquareMatrix B(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    B[0][0] = 1;
    B[0][1] = 2;
    B[0][2] = 3;
    B[1][0] = 2;
    B[1][1] = 4;
    B[1][2] = 6;
    B[2][0] = 3;
    B[2][1] = 6;
    B[2][2] = 8;

    EXPECT_FALSE(A == B);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}