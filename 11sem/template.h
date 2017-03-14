#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include <iostream>
#include "frac.h"

using namespace std;

template <typename Type, int n>

class Vector
{
    private:
        Type elements[n]; 
        
    public:
        Vector<Type, n>(Type* array)
        {
            for(int i = 0; i<n; i++)
            {
                elements[i] = array[i];
            }
        }


        Type operator[](int n_element)
        {
            if (n_element >= n)
            {
                std::cout << "index is out of range\n";
                return -1;
            }
            return elements[n_element]; 
        }


        Vector<Type, n> plus(Vector<Type, n> A)
        {
            Type p[n];
            for(int i=0; i<n; i++)
            {
                p[i] = A[i] + elements[i];
            }
            return Vector<Type, n>(p);   
        }

        friend Vector<Type, n> operator + (Vector<Type, n> A, Vector<Type, n> B)
        {
            return A.plus(B);
        }
        
        friend Vector<Type, n> operator * (Type k, Vector<Type, n> A)
        {
            Type p[n];
            for(int i=0; i<n; i++)
            {
                p[i] = k * A[i];
            }
            return Vector<Type, n>(p);
        }

        friend Vector<Type, n> operator - (Vector A, Vector B)
        {
            return A + (-1)*B;
        }   

        friend Vector<Type, n> operator * (Vector<Type, n> A, Type k)
        {
            return k*A;
        }

        friend Type operator * (Vector<Type, n> A, Vector<Type, n> B)
        {
            Type sum = 0;
            for(int i=0; i<n; i++)
            {
                sum += (A[i] * B[i]);
            }
            return sum;
        }

        friend std::ostream & operator << (std::ostream & os, Vector<Type, n> A)
        {
            os << "( ";
            for(int i=0; i<n; i++)
            {
                os << A[i] << " ";
            }
            os << ") \n";
            return os;
        }
};

template <typename Type, int n, int m> 

class Matrix
{
    private:
        Type elements[n][m];
    
    public:
        Matrix(Type** p)
        {
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<m; j++)
                {
                    this->elements[i][j] = p[i][j];
                }
            }
        }

        Vector<Type, m> operator[](int n_row)
        {
            Type* p = new Type[m];
            for(int i=0; i<m; i++)
            {
                p[i] = elements[n_row][i];
            }
            return Vector<Type, m>(p);
        }

        friend Matrix<Type, n, m> operator + (Matrix<Type, n, m> A, Matrix<Type, n, m> B)
        {
            Type** p = new Type*[n];
            for(int i=0; i<n; i++)
            {
                p[i] = new Type[m];
                for(int j=0; j<m; j++)
                {
                    p[i][j] = A[i][j] + B[i][j];
                }
            }
            return Matrix<Type, n, m>(p);
        }

        friend Matrix<Type, n, m> operator * (Type k, Matrix<Type, n, m> A)
        {
            Type** p = new Type*[n];
            for(int i=0; i<n; i++)
            {
                p[i] = new Type[m];
                for(int j=0; j<m; j++)
                {
                    p[i][j] = k * A[i][j];
                }
            }
            return Matrix<Type, n, m>(p);
        }

        friend Matrix<Type, n, m> operator - (Matrix<Type, n, m> A, Matrix<Type, n, m> B)
        {
            return A+(-1)*B;
        }

        template<typename Type1, int n1, int m1, int l1, int k1> friend Matrix<Type, n1, k1> operator * (Matrix<Type, n1, m1> A, Matrix<Type, l1, k1> B);

        friend Vector<Type, n> operator * (Matrix<Type, n, m> A, Vector<Type, m> B)
        {
            Type p[n];
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<m; j++)
                {
                    p[i] = p[i] + A[i][j]*B[j];
                }
            }
            return Vector<Type, n>(p);
        }                
        
        friend std::ostream & operator << (std::ostream & os, Matrix<Type, n, m> A)
        {
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<m; j++)
                {
                    os << A[i][j] << " ";
                }
                os << "\n";
            }
            return os;
        };
};

template<typename Type, int n1, int m1, int l1, int k1> Matrix<Type, n1, k1> operator * (Matrix<Type, n1, m1> A, Matrix<Type, l1, k1> B)
{
    try
    {
        Type** p = new Type*[n1];
        if (m1 != l1)
            throw 1;

        for (int i=0; i<n1; i++)
        {
            p[i] = new Type[k1];
            for(int j=0; j<k1; j++)
            {   
                for (int ind = 0; ind < m1; ind++)
                {
                    p[i][j] = p[i][j] +  A[i][ind] * B[ind][j];
                }
            }
        }

        return Matrix<Type, n1, k1>(p);
    }
    catch(...)
    {
        std::cout << "ndim are different\n";
    }
}

#endif
