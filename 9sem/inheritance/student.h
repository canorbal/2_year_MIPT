#ifndef STUDENT_H_
#define STUDENT_H_

#include "person.h"
#include <string>
#include <iostream>

class Student : public  Person
{
    public:
        Student();
        Student(std::string name);
        Student(std::string name, std::string surname);
        Student(std::string name, std::string surname, int age);
        Student(std::string name, std::string surname, double mark); 
        Student(std::string name, std::string surname, int age, double mark);
    
    private:
        double mark;
};

#endif
