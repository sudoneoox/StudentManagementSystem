#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include "./grades.h"

using namespace std;

class Assignment : public Grade
{
    Assignment() : Grade() {};
};

#endif // !ASSIGNMENT_H