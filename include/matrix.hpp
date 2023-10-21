#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>

namespace MyMatrix
{
    struct Point
    {
        int x, y;
    };

    const double epsilon = 0.00000001;

    template <typename T = double>
    class Matrix
    {
        T *data;

        int *string_order;
        int *collumn_order;

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

    public:

        int strings_num;
        int collumns_num;

        Matrix<T> transpose() const  //better Matrix& transpose() &
        {
            Matrix<T> B(collumns_num, strings_num);

            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    B[j][i] = access(i, j);

            return B;
        }

        operator Matrix<double>() const 
        {
            Matrix<double> B(strings_num, collumns_num);

            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    B[i][j] = static_cast<double>(access(i, j));

            return B;
        }

        Point get_pivot_of_submatrix(const Point S)
        {
            if(S.x >= strings_num)
                throw std::invalid_argument("MyMatrix::Matrix::get_pivot_of_submatrix - S.x is out of range");
            if (S.y >= collumns_num)
                throw std::invalid_argument("MyMatrix::Matrix::get_pivot_of_submatrix - S.y is out of range");

            T pivot = 0;
            Point pivot_location = {0, 0};        

            for (int i = S.x; i < Matrix<T>::strings_num; ++i)
                for (int j = S.y; j < Matrix<T>::collumns_num; ++j)
                {
                    T temp = std::abs(Matrix<T>::access(i, j));
                    if (temp > pivot)
                    {
                        pivot = temp;
                        pivot_location = {i, j};
                    }
                }

            return pivot_location;
        };

        void eliminate(int x)
        {
            if(x >= strings_num)
                throw std::invalid_argument("MyMatrix::Matrix::eliminate - x is out of range of matrix");

            T pivot = (*this)[x][x];

            for(int i = x + 1; i < this->strings_num; ++i)
            {
                
                T koef = (*this)[i][x] / pivot;

                for(int j = x; j < this->collumns_num; ++j)
                    (*this)[i][j] = (*this)[i][j] - (*this)[x][j] * koef;
            }
        };

        void print()
        {
            for(int i =  0; i < strings_num; ++i)
            {
                for(int j = 0; j < collumns_num; ++j)
                    std::cout << (*this)[i][j] << " ";
                
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

        const T &access(int i, int j) const
        {
            if(i >= strings_num)
                throw std::invalid_argument("MyMatrix::Matrix::access - i argument is out of range");
            if (j >= collumns_num)
                throw std::invalid_argument("MyMatrix::Matrix::access - j argument is out of range");

            return data[string_order[i] * collumns_num + collumn_order[j]];
        };

        Matrix(int a): Matrix(a, a) {};

        Matrix(int a, int b)
        {
            if(a <= 0)
                throw std::invalid_argument("MyMatrix::Matrix::Matrix - a is less than 0");
            if (a <= 0)
                throw std::invalid_argument("MyMatrix::Matrix::Matrix - b is less than 0");

            try
            {
                data = new T[a * b];
                string_order = new int[a];
                collumn_order = new int[b];
            }
            catch(std::bad_alloc& exc)
            {   
                std::cerr << exc.what() << std::endl << "Initializing Matrix object failed, exiting..." << std::endl;
                std::terminate();
            }


            for (int i = 0; i < a; ++i)
                string_order[i] = i;
            for (int i = 0; i < b; ++i)
                collumn_order[i] = i;

            collumns_num = b;
            strings_num = a;
        };

        bool operator==(Matrix<T>& rhs) const  
        {
            if((strings_num == rhs.strings_num) && (collumns_num == rhs.collumns_num))
            {
                for(int i = 0; i < strings_num; ++i)
                    for(int j = 0; j < collumns_num; ++j)
                        if((*this)[i][j] - rhs[i][j] >= epsilon)
                            return false;
            }
            else
                return false;

            return true;
        }

        Matrix(const Matrix<T> & src) : Matrix<T>(src.strings_num, src.collumns_num)
        {
            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    (*this)[i][j] = src[i][j];
        }

        Matrix(Matrix<T> && src) noexcept
        {
            data = nullptr;
            std::swap(data, src.data);
            string_order = nullptr;
            std::swap(string_order, src.string_order);
            collumn_order = nullptr;
            std::swap(collumn_order, src.collumn_order);

            strings_num = src.strings_num;
            collumns_num = src.collumns_num;
        }

        Matrix<T>& operator=(const Matrix<T> & src)
        {
            T * data_temp;
            int * collumn_order_temp;
            int  * string_order_temp;

            if(this == &src)
                return *this;

            try
            {
                data_temp = new T[src.strings_num * src.collumns_num];
                collumn_order_temp = new int[src.collumns_num];
                string_order_temp = new int[src.strings_num];
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << std::endl << "Copy assign failed, exiting..." << std::endl;
                return *this;
            }
            
            delete[] data;
            delete[] collumn_order;
            delete[] string_order;

            data = data_temp;
            collumn_order = collumn_order_temp;
            string_order = string_order_temp;

            strings_num = src.strings_num;
            collumns_num = src.collumns_num;

            for(int i = 0; i < strings_num; ++i)
                string_order[i] = i;
            for(int i = 0; i < collumns_num; ++i)
                collumn_order[i] = i;

            for(int i = 0; i < strings_num; ++i)
                for(int j = 0; j < collumns_num; ++j)
                    (*this)[i][j] = src[i][j];
            
            return *this;
        }

        Matrix<T>& operator=(Matrix<T> && src) noexcept
        {
            if(this == &src)
                return *this;

            std::swap(data, src.data);
            std::swap(string_order, src.string_order);
            std::swap(collumn_order, src.collumn_order);

            strings_num = src.strings_num;
            collumns_num = src.collumns_num;

            return *this;
        }

        ~Matrix()
        {
            delete[] data;
            delete[] collumn_order;
            delete[] string_order;
        };
    };


    template <typename T>
    double det(const Matrix<T> A)
        {
            if(A.strings_num != A.collumns_num)
                throw std::invalid_argument("MyMatrix::det - matrix is not n*n");

            Matrix<double> B(A);
            int change_sign = 0;

            for(int i = 0; i < B.strings_num; ++i)
            {   
                Point pos = {i, i};
                Point pivot_location = B.get_pivot_of_submatrix(pos); //add find max

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
                val = val * B[i][i];
            }
            

            if(change_sign % 2 == 1)
                val = -val;

            return val;
        };
}
