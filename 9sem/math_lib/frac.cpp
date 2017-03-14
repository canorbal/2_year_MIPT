#include "frac.h"

Frac::Frac()
{
    this->p=0;
    this->q=1;
}


Frac::Frac(int p)
{
    this->p = p;
    this->q = 1;
}


Frac::Frac(int p, int q)
{
    if (q==0)
    {
        std::cout << "Wrong arguements in fract, q=0\n";
    }

    this->p = p;
    this->q = q;
}

std::ostream & operator << (std::ostream & os, Frac frac)
{
    frac.simplify();
    if (frac.q==1)
    {
        os << frac.p;
    }
    else
    {
        os << frac.p << "/" << frac.q;
    }
    return os;
}

void Frac::simplify()
{
    int max;
    if (abs(p) > abs(q))
    {  
        max = abs(p);
    }
    else
    {
        max = abs(q);
    }
    for(int i=max; i>0; i--)
    {
        if ((abs(p)%i==0) & (abs(q)%i==0))
        {
            p = p/i;
            q = q/i;
            break;
        }
    }
}

Frac operator + (Frac a, Frac b)
{
    Frac new_frac(0,1);
    new_frac.p = a.p*b.q + b.p*a.q;
    new_frac.q = a.q*b.q;
    new_frac.simplify();
    return new_frac;
}

Frac operator - (Frac a, Frac b)
{
    b.p = -b.p;
    Frac c = a+b;
    c.simplify();
    return c;
}

Frac operator * (Frac a, Frac b)
{
    Frac new_frac(0,1);
    new_frac.p = a.p*b.p;
    new_frac.q = a.q*b.q;
    new_frac.simplify();
    new_frac.simplify();
    return new_frac;
}

Frac operator / (Frac a, Frac b)
{
    Frac new_frac(b.q, b.p);
    new_frac = a * new_frac;
    new_frac.simplify();
    return new_frac;
}

