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
    People(string name, string email, string ID) : name(name), email(email), ID(ID) {}; // constructor
    ~People() {};

    //getters
    string getName() { return name; } // returns name
    string getEmail() { return email; } // returns email
    string getID() { return ID; } // returns ID

    //setters
    void setName(string name) { this->name = name; }; // sets name
    void setEmail(string email) { this->email = email; } // sets email
    void setID(string ID) { this->ID = ID; } // sets ID
};

#endif // !PEOPLE_H