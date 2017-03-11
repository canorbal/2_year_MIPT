#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include "frac.h"

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


