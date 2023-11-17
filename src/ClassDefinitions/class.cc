#include "../include/ClassDeclarations/class.h"
#include <iostream>

using namespace std;

Class::Class() {
    this->className = "";
    this->classID = "";
    this->teacher = new Teacher();
    this->studentList = studentList;
}

// destructor
Class::~Class() {
    delete teacher;
}

Class::Class(string name, string classID) {
    this->className = name;
    this->classID = classID;
    this->teacher = teacher;
    this->studentList = studentList;
}
Class::Class(const Class& otherClass) {}
void Class::setName(string className) { this->className = className; }
void Class::setClassID(string classID) { this->classID = classID; }
void Class::setTeacher(Teacher* teacher) {
    this->teacher = teacher;
}

void Class::addStudent(Student* student) {
    studentList.insert(pair<string, Student*>(student->getID(), student));
}
void Class::setStudentList(map<string, Student*> studentList) {
    this->studentList = studentList;
}



string Class::getID() {
    return classID;
}
string Class::getName() {
    return className;
}
string Class::getClassID() {
    return classID;
}
Teacher* Class::getTeacher() {
    return teacher;
}
map<string, Student*> Class::getStudents() {
    return studentList;
}
double Class::GetFinalGrade(Student* student) {}
map<Student*, double> Class::GetAllFinalGrades() {}
