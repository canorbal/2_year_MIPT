#pragma once

#include <iostream>

class Vector
{
    double x,y,z; 
    public:
        double get_x();
        double get_y();
        double get_z();
        void set_x(double x);
        void set_y(double y);
        void set_z(double z);
        Vector plus(Vector A);
        Vector(double x, double y, double z);
        double operator[](int i);
        friend Vector operator + (Vector A, Vector B);
        friend Vector operator - (Vector A, Vector B);
        friend Vector operator * (double k, Vector A);
        friend Vector operator * (Vector A, double k);
        friend double operator * (Vector A, Vector B);
        friend std::ostream & operator << (std::ostream & os, Vector A);
    private:

};


