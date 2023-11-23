#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>
using namespace std;

class People // abstract class for student and teacher
{

protected:
    string ID;
    string name;
    string email;

public:
    People() : name(""), email(""), ID("") {};
    People(string name, string email, string ID) : name(name), email(email), ID(ID) {};
    ~People() {};

    //getters
    string getName() { return name; }
    string getEmail() { return email; }
    string getID() { return ID; }

    //setters
    void setName(string name) { this->name = name; };
    void setEmail(string email) { this->email = email; }
    void setID(string ID) { this->ID = ID; }
};

#endif // !PEOPLE_H