#include "human.h"

Human::Human()
{
    this->name = "";
    this->surname = "";
    this->age = 0;
}

Human::Human(string name)
{
    this->name = name;
    this->surname = "";
    this->age = 0;
}

Human::Human(string name, string surname)
{
    this->name = name;
    this->surname = surname;
    this->age = 0;
}


Human::Human(string name, string surname, int age)
{
    this->name = name;
    this->surname = surname;
    this->age = age;
}


Student::Student() : Human()
{
    this->mark = 0;
}

Student::Student(string name) : Human(name)
{
    this->mark = 0;
}

Student::Student(string name, string surname) : Human(name, surname)
{
    this->mark = 0;
}

Student::Student(string name, string surname, int age) : Human(name, surname, age)
{
    this->mark = 0;
}

Student::Student(string name, string surname, int age, double mark) : Human(name, surname, age)
{
    this->mark = mark;
}


void Student::set_name(string name)
{
    this->name = name;
}


void Student::set_surname(string surname)
{
    this->surname = surname;
}

string Student::get_name()
{
    return this->name;
}


string Student::get_surname()
{
    return this->surname;
}
