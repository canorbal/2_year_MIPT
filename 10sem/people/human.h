#ifndef HUMAN_H_
#define HUMAN_H_

#include <iostream>
#include "string.h"
using namespace std;

class Human
{
    public:
        Human();
        Human(string name);
        Human(string name, string surname);
        Human(string name, string surname, int age);
        virtual void set_name(string name) = 0;
        virtual void set_surname(string surname) = 0;
        virtual string get_name() = 0;
        virtual string get_surname() = 0;
        // virtual ~Human() = 0;
    protected:
        string name;
        string surname;
        int age;
};


class Student: public Human
{
    public:
        Student();
        Student(string name);
        Student(string name, string surname);
        Student(string name, string surname, int age);
        Student(string name, string surname, int age, double mark);
        
        void set_name(string name);
        void set_surname(string surname);
        string get_name();
        string get_surname();
    
    private:
        double mark;
};

#endif
