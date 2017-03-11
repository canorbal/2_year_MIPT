#include "student.h"
Student::Student(std::string name) : Person(name)
{
    this->mark = 0;
}

Student::Student(std::string name, std::string surname) : Person(name, surname)
{
    this->mark = 0;
}

Student::Student(std::string name, std::string surname, int age) : Person(name, surname, age)
{
    this->mark = 0;
}

Student::Student(std::string name, std::string surname, int age, double mark) : Person(name, surname, age)
{
   this->mark = mark;
}

