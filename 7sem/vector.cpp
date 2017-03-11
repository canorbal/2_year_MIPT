#include "vector.h"

Vector::Vector(double x_param, double y_param, double z_param)
{
    x = x_param;
    y = y_param;
    z = z_param;
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

Vector Vector::operator + (Vector A)
{
    return Vector(x+A.get_x(), y+A.get_y(), z+A.get_z());
}

Vector Vector::operator - (Vector A)
{
    return Vector(x-A.get_x(), y-A.get_y(), z-A.get_z());
}
