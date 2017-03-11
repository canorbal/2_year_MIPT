#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include <iostream>
#include "frac.h"

using namespace std;

template <typename Type>

class Vector
{
    private:
        Type x,y,z; 

    public:
        Vector(Type x, Type y, Type z)
        {
            this->x = x;
            this->y =y;
            this->z = z;
        }

        Type get_x()
        {
            return x;
        }

        Type get_y()
        {
            return y;
        }

        Type get_z()
        {
            return z;
        }

        void set_x(Type x)
        {
            this->x = x;
        }

        void set_y(Type y)
        {
            this->y = y;
        }

        void set_z(Type z)
        {
            this->z = z;
        }

        Vector<Type> plus(Vector<Type> A)
        {
            return Vector<Type>(x+A.get_x(), y+A.get_y(), z+A.get_z());   
        }

        Type operator[](int i)
        {
            if (i==0)
                return x;
            if (i==1)
                return y;
            if (i==2)
                return z;
        }

        friend Vector<Type> operator + (Vector<Type> A, Vector<Type> B)
        {
            return A.plus(B);
        }
        
        friend Vector<Type> operator - (Vector A, Vector B)
        {
            return Vector<Type>(A.x-B.x, A.y-B.y, A.z-B.z);
        }   
        friend Vector<Type> operator * (Type k, Vector<Type> A)
        {
            return Vector<Type>(k*A.x, k*A.y, k*A.z);
        }

        friend Vector<Type> operator * (Vector<Type> A, Type k)
        {
            return k*A;
        }

        friend Type operator * (Vector<Type> A, Vector<Type> B)
        {
            return A.x*B.x + A.y*B.y + A.z*B.z;
        }

        friend std::ostream & operator << (std::ostream & os, Vector<Type> A)
        {
            os << "( " << A.x << " " << A.y << " " << A.z << ")\n";
            return os;
        }
};

#endif
