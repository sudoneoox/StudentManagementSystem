#ifndef TEACHER_H
#define TEACHER_H

#include <vector>
#include <string>
#include <map>

#include "./class.h"
#include "./people.h"
#include "./assignment.h"
#include "./student.h"

using namespace std;

class Class;
class Student;

class Teacher : public People
{
public:
    Teacher();
    Teacher(string name, string email, string id);
    Teacher(const Teacher &other);
    vector<Class *> GetSubjectsTaught() const;
    void UpdateSubjects(vector<Class *> newSubjects);
    void EnterGrade(Assignment *assignment, Student *student, double grade);
    map<Student *, string> GenerateAttendance(string startDate, string endDate);
    Teacher &operator=(const Teacher &RHS);
    friend istream &operator>>(istream &IN, Teacher &teacher);

private:
    vector<Class *> subjectsTaught;
};

#endif // !TEACHER_H