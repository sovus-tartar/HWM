#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

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

TEST(Matrix, get_pivot1)
{
    MyMatrix::Matrix<double> A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 4;
    A[1][1] = 5;
    A[1][2] = 6;
    A[2][0] = 7;
    A[2][1] = 8;
    A[2][2] = 9;

    MyMatrix::Point p = {0, 0};

    MyMatrix::Point t = A.get_pivot_of_submatrix(p);

    EXPECT_EQ(t.x, 2);
    EXPECT_EQ(t.y, 2);
}

TEST(Matrix, get_pivot2)
{
    MyMatrix::Matrix<double> A(3);
    A[0][0] = 4;
    A[0][1] = 8;
    A[0][2] = 16;
    A[1][0] = 3;
    A[1][1] = 6;
    A[1][2] = 9;
    A[2][0] = 1;
    A[2][1] = 4;
    A[2][2] = 13;

    MyMatrix::Point p = {0, 0};

    MyMatrix::Point t = A.get_pivot_of_submatrix(p);

    EXPECT_EQ(t.x, 0);
    EXPECT_EQ(t.y, 2);
}

TEST(Matrix, eliminate)
{
    MyMatrix::Matrix<double> A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    A.eliminate(0);

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

TEST(matrix_base, operator_equal1)
{
    MyMatrix::Matrix A(3);
    MyMatrix::Matrix B(3);
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

TEST(matrix_base, operator_equal2)
{
    MyMatrix::Matrix A(3);
    MyMatrix::Matrix B(3);
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

TEST(matrix_base, operator_equal3)
{
    MyMatrix::Matrix A(3);
    MyMatrix::Matrix B(2);
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
    B[1][0] = 2;
    B[1][1] = 4;

    EXPECT_FALSE(A == B);
}

TEST(matrix_base, copy_ctr)
{
    MyMatrix::Matrix A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    MyMatrix::Matrix B(A);

    EXPECT_TRUE(A == B);
}

TEST(matrix_base, copy_assign1)
{
    MyMatrix::Matrix A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    MyMatrix::Matrix B(2);
    B = A;

    EXPECT_TRUE(A == B);
}

TEST(matrix_base, copy_assign2)
{
    MyMatrix::Matrix A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    MyMatrix::Matrix B(3);
    B = A;

    EXPECT_TRUE(A == B);
}

TEST(Matrix, det1)
{
    MyMatrix::Matrix A(2);
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = -4;

    EXPECT_EQ(MyMatrix::Matrix<double>::det(A), -10.0);
}

TEST(Matrix, det2)
{

    MyMatrix::Matrix A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 0;
    A[1][1] = 4; // 1 * 4 * 9
    A[1][2] = 6;
    A[2][0] = 0;
    A[2][1] = 0;
    A[2][2] = 9;

    EXPECT_EQ(MyMatrix::Matrix<double>::det(A), 36.0);
}

TEST(Matrix, det3)
{
    std::ifstream file;

    file.open("../test/111.in");

    int N;
    file >> N;

    MyMatrix::Matrix A(N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> A[i][j];

    double expected_det;

    file >> expected_det;

    file.close();

    EXPECT_NEAR(MyMatrix::Matrix<double>::det(A), expected_det, 1);
}

TEST(Matrix, det4)
{
    std::ifstream file;

    file.open("../test/222.in");

    int N;
    file >> N;

    MyMatrix::Matrix A(N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> A[i][j];

    double expected_det;

    file >> expected_det;

    file.close();

    

    EXPECT_NEAR(MyMatrix::Matrix<double>::det(A), expected_det, 0.000000001);
}

TEST(Matrix, det5)
{
    std::ifstream file;

    file.open("../test/333.in");

    int N;
    file >> N;

    MyMatrix::Matrix A(N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> A[i][j];

    double expected_det;

    file >> expected_det;

    file.close();

    EXPECT_NEAR(MyMatrix::Matrix<double>::det(A), expected_det, 0.00000001);
}

TEST(Matrix, det6)
{
    std::ifstream file;

    file.open("../test/444.in");

    int N;
    file >> N;

    MyMatrix::Matrix A(N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> A[i][j];

    double expected_det;

    file >> expected_det;

    file.close();

    EXPECT_NEAR(MyMatrix::Matrix<double>::det(A), expected_det, 0.00000001);
}

TEST(Matrix, det_int)
{
    std::ifstream file;

    file.open("../test/555_int.in");

    int N;
    file >> N;

    MyMatrix::Matrix<int> A(N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> A[i][j];

    double expected_det;

    file >> expected_det;

    file.close();

    EXPECT_NEAR(expected_det, MyMatrix::Matrix<int>::det(A), 0.000000000001);
}

TEST(Matrix, cast_to_double_and_move_assign)
{
    MyMatrix::Matrix<int> A(2);

    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 2;
    A[1][1] = 3;

    MyMatrix::Matrix<double> B = static_cast<MyMatrix::Matrix<double>>(A);

    EXPECT_DOUBLE_EQ(B[0][0], 0);
    EXPECT_DOUBLE_EQ(B[0][1], 1);
    EXPECT_DOUBLE_EQ(B[1][0], 2);
    EXPECT_DOUBLE_EQ(B[1][1], 3);

}

TEST(Matrix, cast_to_double_and_move_ctr)
{
    MyMatrix::Matrix<int> A(2);

    A[0][0] = 0;
    A[0][1] = 1;
    A[1][0] = 2;
    A[1][1] = 3;

    MyMatrix::Matrix<double> B(static_cast<MyMatrix::Matrix<double>>(A));

    EXPECT_DOUBLE_EQ(B[0][0], 0);
    EXPECT_DOUBLE_EQ(B[0][1], 1);
    EXPECT_DOUBLE_EQ(B[1][0], 2);
    EXPECT_DOUBLE_EQ(B[1][1], 3);

}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}