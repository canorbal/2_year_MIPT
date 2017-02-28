#pragma once
#include <iostream>

class Frac
{   
    public:
        int p;
        int q;
        Frac(int p, int q);
        void simplify();
        friend std::ostream & operator << (std::ostream & os, Frac frac); 
        friend Frac operator + (Frac a, Frac b);
        friend Frac operator - (Frac a, Frac b);
        friend Frac operator * (Frac a, Frac b);
        friend Frac operator / (Frac a, Frac b);
};
