
#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "./teacher.h"
#include "./student.h"

class Teacher;
class Student;

class Class
{
private:
    string className;
    string classID;
    Teacher *teacher;
    vector<Student *> studentList;
    map<Student *, double> finalGrades;

public:
    // constructor
    Class();

    // destructor
    ~Class();

    Class(string name, string classID);
    Class(const Class &otherClass);
    void setName(string className);
    void setClassID(string classID);
    void setTeacher(Teacher *teacher);
    void addStudent(Student *Student);
    string getName();
    string getClassID();
    Teacher getTeacher();
    string getID();
    vector<Student *> getStudents();
    double GetFinalGrade(Student *student);
    map<Student *, double> GetAllFinalGrades();
};

#endif // !CLASS_H
