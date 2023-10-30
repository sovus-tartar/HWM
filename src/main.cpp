#include <iostream>
#include <matrix.hpp>

// TODO: better tests for ctors

int main(int argc, char **argv)
{
    /*
    try
    {
        int N;
        std::cin.exceptions(std::istream::badbit | std::istream::failbit);
        std::cin >> N;
        
        class MyMatrix::Matrix<double> A(N);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                std::cin >> A[i][j];

        std::cout << MyMatrix::det(A) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
    */

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
    std::cout << "Here" << std::endl;
    A = A;
}
