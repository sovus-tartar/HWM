#include <iostream>
#include <matrix.hpp>

// TODO: better tests for ctors

int main(int argc, char **argv)
{
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
}
