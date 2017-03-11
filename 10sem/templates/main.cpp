#include "template.h"

using namespace std;

int main()
{
    Frac x(1,3);
    Frac y(2,4);
    Frac z(5,6);
    Vector<Frac> A(1,1,2);
    cout << 2*2*A;
    return 0;
}
