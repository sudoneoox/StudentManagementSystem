#ifndef EXAM_H
#define EXAM_H
#include <string>
#include "./grades.h"

using namespace std;
class Exam : public Grade
{
public:
    Exam() : Grade() {};
    Exam(string name, string ID) : Grade(name, ID) {};

};
#endif // !EXAM_H