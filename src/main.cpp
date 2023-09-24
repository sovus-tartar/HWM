#include <iostream>
#include "../include/matrix.hpp"

// TODO: better tests for ctors

int main(int argc, char **argv)
{
    int N;

    std::cin >> N;

    class MyMatrix::Matrix<double> A(N);

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            std::cin >> A[i][j];


    std::cout << MyMatrix::det(A) << std::endl;
    return 0;
}
