#include <stdio.h>
#include "vector.h"


int main()
{   
    Vector A(1,1,1);
    A.set_x(10);
    double x = A.get_x();
    printf("%f\n", x);
    Vector B(2,2,2);
    printf("%f %f %f\n", (A+B).get_x(), (A+B).get_y(), (A+B).get_z());
    return 0;
}


