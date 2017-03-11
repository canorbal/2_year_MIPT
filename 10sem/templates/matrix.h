#ifndef MATRIX_H_
#define MATRIX_H_

#include "vector.h"
#include "frac.h"

class Matrix
{
    public:
        Frac matrix[3][3];
        Matrix();
        Matrix(Frac** p);
        Vector operator[](int i);
        friend Matrix operator + (Matrix A, Matrix B);
        friend Matrix operator * (Frac k, Matrix A);
        friend Matrix operator * (Matrix A, Matrix B);
        friend Vector operator * (Matrix A, Vector B);
        friend std::ostream & operator << (std::ostream & os, Matrix A);
};

#endif
