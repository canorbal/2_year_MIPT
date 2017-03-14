#include "template.h"

using namespace std;

int main()
{
    Frac** p = new Frac*[2];

    for(int i=0; i<2; i++)
    {
        p[i] = new Frac[3];
        for(int j=0; j<3; j++)
        {
            Frac f = Frac(i,2);
            p[i][j] = f;
        }
    }

    Frac** q = new Frac*[3];

    for(int i=0; i<3; i++)
    {
        q[i] = new Frac[2];
        for(int j=0; j<2; j++)
        {
            Frac f = Frac(i,2);
            q[i][j] = f;
        }
    }
    
    Frac* m = new Frac[3];
    for(int i=0; i<3; i++)
    {
        Frac f = Frac(i,3);
        m[i] = f;
    }


    Matrix<Frac, 2, 3> A(p);
    Matrix<Frac, 3, 2> B(q);
    Vector<Frac, 3> V(m);

    cout << "Matrix A is \n" << A << "\n";
    cout << "Matrix B is \n" << B << "\n";
    cout << "Matrix V is \n" << V << "\n";
    cout << "Matrix A*B is \n" << A*B << "\n";   
    cout << "A*V is \n" << A*V << "\n";
    return 0;
}
