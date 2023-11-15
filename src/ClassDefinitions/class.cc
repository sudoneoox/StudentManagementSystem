#include "../include/ClassDeclarations/class.h"
#include <iostream>

using namespace std;

Class::Class()
{
    this->className = "";
    this->classID = "";
    this->teacher = new Teacher();
    this->studentList;
}

// destructor
Class::~Class()
{
    delete teacher;
    for (int i = 0; i < studentList.size(); i++)
    {
        delete studentList.at(i);
    }
}

Class::Class(string name, string classID)
{
    this->className = name;
    this->classID = classID;
    this->teacher = teacher;
    this->studentList = studentList;
}
Class::Class(const Class &otherClass) {}
void Class::setName(string className) { this->className = className; }
void Class::setClassID(string classID) { this->classID = classID; }
void Class::setTeacher(Teacher *teacher)
{
    delete teacher;
    this->teacher = teacher;
}
void Class::setStudentList(vector<Student *> studentList)
{
    for (int i = 0; i < studentList.size(); i++)
    {
        delete studentList.at(i);
        this->studentList.push_back(studentList.at(i));
    }
}
void Class::addStudent(Student *studentList)
{
    this->studentList.push_back(studentList);
}
string Class::getID()
{
    return classID;
}
string Class::getName()
{
    return className;
}
string Class::getClassID()
{
    return classID;
}
Teacher Class::getTeacher()
{
    return *teacher;
}
vector<Student *> Class::getStudents()
{
    return studentList;
}
double Class::GetFinalGrade(Student *student) {}
map<Student *, double> Class::GetAllFinalGrades() {}
