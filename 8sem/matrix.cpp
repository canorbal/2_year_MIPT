#include "matrix.h"

Matrix::Matrix()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            matrix[i][j]=0;
        }
    }
}

Matrix::Matrix(double** p)
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            matrix[i][j] = p[i][j];
        }
    }
}

Matrix operator + (Matrix A, Matrix B)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            A.matrix[i][j] += B.matrix[i][j];
    
        }
    }
    return A;
}

Matrix operator * (double k, Matrix A)
{

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            A.matrix[i][j] = k*A.matrix[i][j];
    
        }
    }
    return A;
}

Matrix operator * (Matrix A, double k)
{
    return k*A;
}


Matrix operator * (Matrix A, Matrix B)
{
    Matrix C = Matrix();
    for (int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            for (int ind = 0; ind < 3; ind++)
            {
                C.matrix[i][j] += A.matrix[i][ind] * B.matrix[j][ind];
            }
        }
    }
    return C;
}


Vector operator * (Matrix A, Vector B)
{
    Vector C = Vector(0,0,0);
    C.set_x(A.matrix[0][0] * B.get_x() + A.matrix[0][1] * B.get_y() + A.matrix[0][2] * B.get_z());
    
    C.set_y(A.matrix[1][0] * B.get_x() + A.matrix[1][1] * B.get_y() + A.matrix[1][2] * B.get_z());

    C.set_z(A.matrix[2][0] * B.get_x() + A.matrix[2][1] * B.get_y() + A.matrix[2][2] * B.get_z());

    return C;
}


Vector Matrix::operator [] (int i)
{
    Vector C = Vector(matrix[i][0], matrix[i][1], matrix[i][1]);
    return C;
}


std::ostream & operator << (std::ostream & os, Matrix A)
{
    for (int i = 0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if (j==2)
            {
                os << A.matrix[i][j];
            }
            else 
            {
                os << A.matrix[i][j] << " ";
            }
        }
        os << "\n";
    }
    return os;
}

