#include <stdio.h>
#include "vector.h"
#include "vector_functions.cpp"
#include "matrix.h"
#include "matrix_functions.cpp"
#include "frac.h"
#include "frac_functions.cpp"

// объявление класса в .h файле
// методы класса в .cpp файле
// итого 3 файла: main.cpp, class.cpp, class.h, *other_functions.cpp

int main()
{  
    Frac x(1,2);
    Frac y(3,4);
    Frac z(1,4);

    Vector A(x,y,z);

    Vector B(2*x,2*y,2*z);
    std::cout << A;

    Frac* p[3];
    
    for (int i=0; i<3; i++)
    {
        p[i] = new Frac[3];
        for(int j=0; j<3; j++)
        {
            p[i][j] = Frac(1,2);
        }
    }

    Matrix matrix(p);
    std::cout <<  (matrix) << "\n";
    std::cout << (matrix)*A << "\n";
    return 0;
}


