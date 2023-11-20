#pragma once

#include <exception>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <limits>

#include <MyVector.hpp>
#include <stdexcept>

// TODO: func multiply as matrix multiplication

namespace MyMatrix
{
    struct Point
    {
        int x, y;
    };

    const double epsilon = std::numeric_limits<double>::epsilon();

    template <typename T = double>
    class Matrix
    {
        MyVector::vector<T> data;

        MyVector::vector<int> string_order;
        MyVector::vector<int> collumn_order;

        struct proxy_matrix
        {
            int curr_str;
            Matrix<T>* M;
            const Matrix<T>* M_const;

            proxy_matrix(Matrix<T>* M_, const int i_) : M(M_), curr_str(i_) {};
            proxy_matrix(const Matrix<T>* M_, int i_) : M_const(M_), curr_str(i_) {};

            proxy_matrix &set_str(int i)
            {
                curr_str = i;
                return *this;
            }

            T &operator[](const int curr_coll)
            {
                return M->access(curr_str, curr_coll);
            }

            const T operator[](const int curr_coll) const
            {
                return M_const->access(curr_str, curr_coll);
            }
        };

        bool compare_size(const Matrix<T> & B) const 
        {
            if((strings_num == B.strings_num) && (collumns_num == B.collumns_num))
                return true;
            else
                return false;
        }
        
        bool multiply_check(const Matrix<T> & B) const //A(m * n) B(n * k)
        {
            if(collumns_num == B.strings_num)
                return true;
            return false;
        }

    public:

        int strings_num;
        int collumns_num;

        Matrix<T> multiply(const Matrix<T> & A) const 
        {
            if(!multiply_check(A))
                throw std::invalid_argument("Matrix::multiply - impossible to multiply, wrong sizes\n");

            Matrix<T> temp(strings_num, A.collumns_num);

            for(int i = 0; i < temp.strings_num; ++i)
                for(int j = 0; j < temp.collumns_num; ++j)
                {
                    T sum{};
                    
                    for (int k = 0; k < collumns_num; ++k)
                    {
                        sum += access(i, k) * A.access(k, j);
                    }

                    temp.access(i, j) = sum;
                }
                
            return temp;
        }

        Matrix<T> & multiply(const T k)
        {
            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    access(i, j) *= k;

            return *this;
        }

        Matrix<T> & operator+=(const Matrix<T> & rhs)
        {
            if(!compare_size(rhs))
                throw std::invalid_argument("Matrix::operator+= : sizes are different\n");

            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    access(i, j) += rhs.access(i, j);

            return *this;
        }

        Matrix<T> operator-() const
        {
            Matrix<T> temp(strings_num, collumns_num);

            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    temp.access(i, j) = -access(i, j);

            return temp;
        }

        Matrix<T> & operator-=(const Matrix<T> & rhs)
        {
            operator+=(-rhs);
            return *this;
        }

        Matrix<T> transpose() const  //better Matrix& transpose() &
        {
            Matrix<T> B(collumns_num, strings_num);

            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    B.access(j, i) = access(i, j);

            return B;
        }

        operator Matrix<double>() const 
        {
            Matrix<double> B(strings_num, collumns_num);

            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    B.access(i, j) = static_cast<double>(access(i, j));

            return B;
        }

        Point get_pivot_of_collumn(const Point & S) const 
        {
            if(S.x >= strings_num)
                throw std::out_of_range("MyMatrix::Matrix::get_pivot_of_collumn - S.x is out of range");
            if (S.y >= collumns_num)
                throw std::out_of_range("MyMatrix::Matrix::get_pivot_of_collumn - S.y is out of range");

            T pivot = 0;
            Point pivot_location = {0, 0};        

            for (int i = S.x; i < strings_num; ++i)
            {
                T temp = std::abs(access(i, S.y));
                if (temp > pivot)
                {
                    pivot = temp;
                    pivot_location = {i, S.y};
                }

            }

            return pivot_location;
        };

        void eliminate(const int x)
        {
            if(x >= strings_num)
                throw std::out_of_range("MyMatrix::Matrix::eliminate - x is out of range of matrix");

            T pivot = access(x, x);

            if(std::abs(pivot) < epsilon)
                throw std::logic_error("Matrix::eliminate - pivot A[x][x] is zero");

            for(int i = x + 1; i < this->strings_num; ++i)
            {
                T koef = access(i, x) / pivot;
                for(int j = 0; j < this->collumns_num; ++j)
                    access(i, j) = access(i, j) - access(x, j) * koef;
            }
        };

        void print() const
        {
            for(int i =  0; i < strings_num; ++i)
            {
                for(int j = 0; j < collumns_num; ++j)
                    std::cout << access(i, j) << " ";
                
                std::cout << std::endl;
            }
        }

        void switch_collumnes(const int i, const int j)
        {
            if(i >= collumns_num)
                throw std::out_of_range("MyMatrix::Matrix::switch_collumnes - i argument is out of range");
            if (j >= collumns_num)
                throw std::out_of_range("MyMatrix::Matrix::switch_collumnes - j argument is out of range");

            if(i != j)
                std::swap(collumn_order[i], collumn_order[j]);
        }

        void switch_strings(const int i, const int j)
        {
            if(i >= strings_num)
                throw std::out_of_range("MyMatrix::Matrix::switch_strings - i argument is out of range");
            if (j >= collumns_num)
                throw std::out_of_range("MyMatrix::Matrix::switch_strings - j argument is out of range");

            if(i != j)
                std::swap(string_order[i], string_order[j]);
        }

        proxy_matrix operator[](const int i)
        {
            return proxy_matrix(this, i);
        }

        const proxy_matrix operator[](const int i) const
        {
            return proxy_matrix(this, i);
        }

        T &access(int i, int j)
        {
            if(i >= strings_num)
                throw std::invalid_argument("MyMatrix::Matrix::access - i argument is out of range");
            if (j >= collumns_num)
                throw std::invalid_argument("MyMatrix::Matrix::access - j argument is out of range");

            return data[string_order[i] * collumns_num + collumn_order[j]];
        };

        const T access(int i, int j) const
        {
            if(i >= strings_num)
                throw std::invalid_argument("MyMatrix::Matrix::access - i argument is out of range");
            if (j >= collumns_num)
                throw std::invalid_argument("MyMatrix::Matrix::access - j argument is out of range");

            return data[string_order[i] * collumns_num + collumn_order[j]];
        };

        Matrix(int a): Matrix(a, a) {};

        Matrix(int a, int b): data(a * b),string_order(a), collumn_order(b)
        {
            if ((a <= 0) || (b <= 0))
                throw std::invalid_argument("Matrix::ctr - size is less then 0");

            for (int i = 0; i < a; ++i)
                string_order[i] = i;
            for (int i = 0; i < b; ++i)
                collumn_order[i] = i;

            collumns_num = b;
            strings_num = a;
        };

        bool operator==(const Matrix<T>& rhs) const  
        {
            if(compare_size(rhs))
            {
                for(int i = 0; i < strings_num; ++i)
                    for(int j = 0; j < collumns_num; ++j)
                        if(access(i, j) - rhs.access(i, j) >= epsilon)
                            return false;
            }
            else
                return false;

            return true;
        };
    };

    template<typename T>
    Matrix<T> operator*(const T & k, const Matrix<T> & A)
    {
        Matrix<T> temp(A);
        temp.multiply(k);
        return temp;
    }

    template<typename T>
    Matrix<T> operator*(const Matrix<T> & A, const T & k)
    {
        Matrix<T> temp(A);
        temp.multiply(k);
        return temp;
    }

    template <typename T>
    Matrix<T> operator+(const Matrix<T> & lhs, const Matrix<T> & rhs)
    {
        Matrix<T> temp(lhs);
        temp += rhs;
        return temp;
    }

    template <typename T>
    Matrix<T> operator-(const Matrix<T> & lhs, const Matrix<T> & rhs)
    {
        Matrix<T> temp(lhs);
        temp -= rhs;
        return temp;
    }

    template <typename T>
    double det(const Matrix<T> & A)
        {
            if(A.strings_num != A.collumns_num)
                throw std::invalid_argument("MyMatrix::det - matrix is not n * n");

            Matrix<double> B(A);
            int change_sign = 0;

            for(int i = 0; i < B.strings_num; ++i)
            {   
                Point pos = {i, i};
                Point pivot_location = B.get_pivot_of_collumn(pos);

                if (std::abs(B[pivot_location.x][pivot_location.y]) < epsilon)
                    break;

                B.switch_collumnes(pivot_location.y, pos.y);
                B.switch_strings(pivot_location.x, pos.x);
                change_sign += (pivot_location.y != pos.y) + (pivot_location.x != pos.x);
                B.eliminate(i);
            }

            double val = 1.0;
            for(int i = 0; i < B.strings_num; ++i)
            {
                val = val * B.access(i, i);
            }
            

            if(change_sign % 2 == 1)
                val = -val;

            return val;
        };
}
