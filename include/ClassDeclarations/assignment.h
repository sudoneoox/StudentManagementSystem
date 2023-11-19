#ifndef ASSIGNMNENT_H
#define ASSIGNMNENT_H

#include <string>
#include <map>

using namespace std;

struct Assignment {
    double grade;
    bool isExam;
    Assignment(double grade, bool isExam = false) {
        this->grade = grade;
        this->isExam = isExam;
    }
};

#endif // !ASSIGNMENT_H