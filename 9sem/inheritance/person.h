#ifndef PERSON_H_
#define PERSON_H_


#include <iostream>
#include <string>

class Person
{
    public:
        Person();
        Person(std::string name);
        Person(std::string name, std::string surname);
        Person(std::string name, std::string surname, int age);
    
    protected:
        std::string name, surname;
        int age;
};

#endif
