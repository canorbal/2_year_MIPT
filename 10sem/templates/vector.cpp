#include "vector.h"

Vector::Vector(Frac x, Frac y, Frac z)
{
    this->x = x;
    this->y =y;
    this->z = z;
}

Frac Vector::get_x()
{
    return x;
}

Frac Vector::get_y()
{
    return y;
}

Frac Vector::get_z()
{
    return z;
}

void Vector::set_x(Frac x_param)
{
    x = x_param;
}
void Vector::set_y(Frac y_param)
{
    y = y_param;
}
void Vector::set_z(Frac z_param)
{
    z = z_param;
}
 
Vector Vector::plus(Vector A)
{
    return Vector(x+A.get_x(), y+A.get_y(), z+A.get_z());   
}

Vector operator - (Vector A, Vector B)
{
    return Vector(A.x-B.x, A.y-B.y, A.z-B.z);
}

Vector operator + (Vector X, Vector Y)
{
    return X.plus(Y);
}

Frac operator * (Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

Vector operator * (Frac k, Vector A)
{
    return Vector(k*A.x, k*A.y, k*A.z);
}

Vector operator * (Vector A, Frac k)
{
    return k*A;
}

Frac Vector::operator[](int i)
{
    if (i==0)
        return x;
    if (i==1)
        return y;
    if (i==2)
        return z;
}

std::ostream & operator << (std::ostream & os, Vector A)
{
    os << "( " << A.x << " " << A.y << " " << A.z << ")\n";
    return os;
}
