#ifndef EXAM_H
#define EXAM_H
#include <string>
#include "./grades.h"

using namespace std;
class Exam : public Grade
{
    Exam() : Grade() {};
};
#endif // !EXAM_H