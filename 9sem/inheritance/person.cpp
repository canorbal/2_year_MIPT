#include "person.h"
#include "string"
#include <iostream>

Person::Person()
{
    this->name = "";
    this->surname = "";
    this->age = 0;
}

Person::Person(std::string name)
{
    this->name = name;
    this->surname = "";
    this->age =0;
}

Person::Person(std::string name, std::string surname)
{
    this->name = name;
    this->surname = surname;
    this->age = 0;
}

Person::Person(std::string name, std::string surname, int age)
{
    this->name = name;
    this->surname = surname;
    this->age = age;
}

