#include <iostream>
#include "../include/matrix.hpp"

int main(int argc, char **argv)
{

    MyMatrix::Matrix<double> A(2, 3);

    A[0][0] = 1.0;
    A[0][1] = 2.0;
    A[0][2] = 3.0;
    A[1][0] = 4.0;
    A[1][1] = 5.0;
    A[1][2] = 6.0;

    std::cout << "LOL\n";

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
            std::cout << A.access(i, j) << " ";

        std::cout << std::endl;
    }

    A.switch_collumnes(0, 2);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
            std::cout << A.access(i, j) << " ";

        std::cout << std::endl;
    }
    A.switch_strings(0, 1);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
            std::cout << A.access(i, j) << " ";

        std::cout << std::endl;
    }
}
