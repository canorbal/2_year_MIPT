#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include "frac.h"


int main()
{   
    Vector A(1,1,1);
    A.set_x(10);
    Vector B(2,2,2);
    std::cout << A;
    std::cout << B;
    std::cout << A+B;
    std::cout << A-B;
    std::cout << A*B << "\n";
    std::cout << (1.5*A);

    double* p[3];
    
    for (int i=0; i<3; i++)
    {
        p[i] = new double[3];
        for(int j=0; j<3; j++)
        {
            p[i][j] = 1;
        }
    }

    Matrix matr(p);
    std::cout << (5*matr);
    std::cout << (3*matr);
    Matrix tmp_matr = (5*matr) * (3*matr); 
    std::cout << tmp_matr;
    std::cout << tmp_matr[1];
    std::cout << tmp_matr[0][0] << "\n";
    
    Frac a(-12, 8);
    std::cout << a;
    Frac b(24, 3);
    std::cout << b;
    std::cout << a+b;
    std::cout << a-b;
    std::cout << a * b;
    std::cout << a / b;
    return 0;

}


