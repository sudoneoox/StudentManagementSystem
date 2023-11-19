#ifndef TEACHER_H
#define TEACHER_H

// #include <vector>
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
private:
    map<string, Class*> subjectsTaught; // classID, class pointer

public:
    Teacher();
    Teacher(string name, string email, string id);
    Teacher(const Teacher& other);
    ~Teacher();
    map<string, Class*> GetSubjectsTaught() const;
    void printSubjectsTaught();
    void setSubjectsTaught(map<string, Class*> subjectsTaught);
    void addSubject(Class* subject);
    void UpdateSubjects(map<string, Class*> newSubjects);
    void EnterGrade(Assignment* assignment, Student* student, double grade);
    map<Student*, string> GenerateAttendance(string startDate, string endDate);
    Teacher& operator=(const Teacher& RHS);

    friend istream& operator>>(istream& IN, Teacher& teacher);

    friend ostream& operator<<(ostream& OUT, Teacher& teacher);

};

#endif // !TEACHER_H