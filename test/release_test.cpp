#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include <matrix.hpp>


TEST(Matrix, det7_release)
{
    std::ifstream file;

    file.open("../../test/777.in");

    int N;
    file >> N;

    MyMatrix::Matrix A(N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> A[i][j];

    double expected_det;

    file >> expected_det;

    file.close();

    double ttl_det = MyMatrix::det(A);
    EXPECT_NEAR(ttl_det, expected_det, 0.00000001);

}