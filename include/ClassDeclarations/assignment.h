#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include "./grades.h"

using namespace std;

class Assignment : public Grade // Assignment class inherits from Grade class
{
public:
    Assignment() : Grade() {};
    Assignment(string name, string id) : Grade(name, id) {};
};



#endif // !ASSIGNMENT_H