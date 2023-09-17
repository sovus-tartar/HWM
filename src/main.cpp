#include <iostream>
#include "../include/matrix.hpp"

int main(int argc, char **argv)
{
    MyMatrix::SquareMatrix A(3);
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;

    A.print();

    MyMatrix::SquareMatrixTest::test_eliminate(A, 1);
    
    A.print();

    return 0;
}
