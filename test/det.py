import numpy as np;
import random



def print_matrix_cpp_style(n: int, A : list):
    print(n)

    for i in range(n):
        for j in range(n):
            print(round(A[i][j], 6), end = ' ')
        print()


def sum_lines(A : list, n : int, n1 : int, n2 : int):
    for i in range(n):
        A[n1][i] += A[n2][i]
    return A

def sum_collumns(A : list, n : int, n1 : int, n2 : int):
    for i in range(n):
        A[i][n1] += A[i][n2]
    return A

def main():

    n = int(input())

    A = []
    k = 0
    for i in range(n):
        temp = []

        for j in range(n):
            if (j >= i):
                if (j == i):
                    temp.append(int(1))
                else:
                    if (j % 2 == 0):
                        temp.append(int(1))
                    else:
                        temp.append(int(-1))
            else:
                temp.append(int(0))
        A.append(temp)

    m = int(input())

    for i in range(m):
        A[i][i] = float(input())

    k = 3 * n

    for i in range(k):
        n1 = random.randint(0, n - 1)
        n2 = random.randint(0, n - 1)

        while (n1 == n2):
            n1 = random.randint(0, n - 1)
            n2 = random.randint(0, n - 1)

        A = sum_lines(A, n, n1, n2)

        n1 = random.randint(0, n - 1)
        n2 = random.randint(0, n - 1)

        while (n1 == n2):
            n1 = random.randint(0, n - 1)
            n2 = random.randint(0, n - 1)

        A = sum_collumns(A, n, n1, n2)

    print_matrix_cpp_style(n, A)

    print(round(np.linalg.det(A), 6))

main()

