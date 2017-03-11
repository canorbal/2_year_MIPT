#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include "frac.h"

class Vector
{
    Frac x,y,z; 

    public:
        Frac get_x();
        Frac get_y();
        Frac get_z();
        void set_x(Frac x);
        void set_y(Frac y);
        void set_z(Frac z);
        Vector plus(Vector A);
        Vector(Frac x, Frac y, Frac z);
        Frac operator[](int i);
        friend Vector operator + (Vector A, Vector B);
        friend Vector operator - (Vector A, Vector B);
        friend Vector operator * (Frac k, Vector A);
        friend Vector operator * (Vector A, Frac k);
        friend Frac operator * (Vector A, Vector B);
        friend std::ostream & operator << (std::ostream & os, Vector A);
    private:

};

#endif
