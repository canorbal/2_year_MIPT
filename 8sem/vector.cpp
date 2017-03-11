#include "vector.h"

Vector::Vector(double x, double y, double z)
{
    this->x = x;
    this->y =y;
    this->z = z;
}

double Vector::get_x()
{
    return x;
}

double Vector::get_y()
{
    return y;
}

double Vector::get_z()
{
    return z;
}

void Vector::set_x(double x_param)
{
    x = x_param;
}
void Vector::set_y(double y_param)
{
    y = y_param;
}
void Vector::set_z(double z_param)
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

double operator * (Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

Vector operator * (double k, Vector A)
{
    return Vector(k*A.x, k*A.y, k*A.z);
}

Vector operator * (Vector A, double k)
{
    return k*A;
}

double Vector::operator[](int i)
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
