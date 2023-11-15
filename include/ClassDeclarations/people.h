#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>
using namespace std;

class People
{

protected:
    string ID;
    string name;
    string email;

public:
    People();
    People(string name, string email, string ID);
    ~People();

    string getName();
    string getEmail();
    string getID();
    void setName(string name);
    void setEmail(string email);
    void setID(string ID);
};

#endif // !PEOPLE_H