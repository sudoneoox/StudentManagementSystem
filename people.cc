#include "./H/people.h"
using namespace std;
#include <iostream>
#include <string>

People::People()
{
    this->name = "";
    this->email = "";
    this->ID = "";
}

People::~People() {}

People::People(string name, string email, string ID)
{
    this->name = name;
    this->email = email;
    this->ID = ID;
}

void People::setName(string name)
{
    this->name = name;
}
void People::setEmail(string email)
{
    this->email = email;
}

string People::getName()
{
    return this->name;
}
string People::getEmail()
{
    return this->email;
}
string People::getID()
{
    return this->ID;
}
void People::setID(string ID)
{
    this->ID = ID;
}