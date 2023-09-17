#include <iostream>
#include "../include/matrix.hpp"

int main(int argc, char **argv)
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

    if (A == B)
        std::cout << "SUCCESS!\n";

    

    return 0;
}
