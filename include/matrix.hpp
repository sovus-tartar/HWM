#include <iostream>
#include <cassert>
#include <cstdlib>

namespace MyMatrix
{

    template <typename T>
    class Matrix
    {
        T *data;

        int *string_order;
        int *collumn_order;

        struct proxy_matrix
        {
            int curr_str;
            Matrix<T> *M;

            proxy_matrix(Matrix<T> *M_) : M(M_){};

            proxy_matrix &set_str(int i)
            {
                curr_str = i;
                return *this;
            }

            T &operator[](const int curr_coll)
            {
                return M->access(curr_str, curr_coll);
            }

            const T &operator[](const int curr_coll) const
            {
                return M->access(curr_str, curr_coll);
            }
        } proxy_;

    public:

        int strings_num;
        int collumns_num;

        void switch_collumnes(const int i, const int j)
        {
            assert(i < collumns_num);
            assert(j < collumns_num);

            std::swap(collumn_order[i], collumn_order[j]);
        }

        void switch_strings(const int i, const int j)
        {
            assert(i < strings_num);
            assert(j < strings_num);

            std::swap(string_order[i], string_order[j]);
        }

        proxy_matrix &operator[](const int i)
        {
            return proxy_.set_str(i);
        }
        const proxy_matrix &operator[](const int i) const
        {
            return proxy_.set_str(i);
        }

        T &access(int i, int j)
        {
            assert(i < strings_num);
            assert(j < collumns_num);

            return data[string_order[i] * collumns_num + collumn_order[j]];
        };

        Matrix(int a, int b) : proxy_(this)
        {
            assert(a > 0);
            assert(b > 0);

            data = new T[a * b];
            string_order = new int[a];
            collumn_order = new int[b];

            for (int i = 0; i < a; ++i)
                string_order[i] = i;
            for (int i = 0; i < b; ++i)
                collumn_order[i] = i;

            collumns_num = b;
            strings_num = a;
        };

        // copy ctr
        // copy assign
        // move ctr
        // move assign

        ~Matrix()
        {
            delete[] data;
            delete[] collumn_order;
            delete[] string_order;
        };
    };

    struct Point
    {
        int x, y;
    };

    template <typename T>
    class SquareMatrix : public Matrix<T>
    {
    private:

        Point get_pivot_of_submatrix(Point S)
        {
            T pivot = 0;
            Point pivot_location = {0, 0};

            

            for (int i = S.x; i < this->strings_num; ++i)
                for (int j = S.y; j < this->collumns_num; ++j)
                {
                    T temp = abs(this->access(i, j));
                    if (temp > pivot)
                    {
                        pivot = temp;
                        pivot_location = {i, j};
                    }
                }

            return pivot_location;
        };

        void eliminate(int x){

        };

    public:
        friend class SquareMatrixTest;

        SquareMatrix(int a_) : Matrix<T>(a_, a_){};

        double det(){

        };
    };

    class SquareMatrixTest
    {
    public:
        static Point test_pivot(SquareMatrix<double> &A, int i, int j)
        {
            Point temp = {i, j};
            return A.get_pivot_of_submatrix(temp);
        }
    };
}
