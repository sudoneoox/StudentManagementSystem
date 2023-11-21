#include "../include/ClassDeclarations/class.h"
#include <iostream>

using namespace std;

Class::Class() {
    this->className = "";
    this->classID = "";
    this->teacher = nullptr;
}

// destructor
Class::~Class() {
    delete teacher;
    for (auto& student : studentList) {
        delete student.second;
    }
    for (auto& exam : exams) {
        delete exam.second;
    }
    for (auto& assignment : assignments) {
        delete assignment.second;
    }
}

Class::Class(string name, string classID) {
    this->className = name;
    this->classID = classID;
    this->teacher = nullptr;
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
void Class::removeStudent(Student* student) {
    studentList.erase(student->getID());
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

void Class::addAssignment(Assignment* assignment) {
    if (assignments.find(assignment->getID()) == assignments.end()) {
        assignments.insert(pair<string, Assignment*>(assignment->getID(), assignment));
    }
}
void Class::addExam(Exam* exam) {
    if (exams.find(exam->getID()) == exams.end()) {
        exams.insert(pair<string, Exam*>(exam->getID(), exam));
    }
}

void Class::addAssignment(map<string, Assignment*> assignments) {
    for (auto& assignment : assignments) {
        if (this->assignments.find(assignment.first) == this->assignments.end()) {
            this->assignments.insert(pair<string, Assignment*>(assignment.first, assignment.second));
        }
    }
}

void Class::addExam(map<string, Exam*> exams) {
    for (auto& exam : exams) {
        if (this->exams.find(exam.first) == this->exams.end()) {
            this->exams.insert(pair<string, Exam*>(exam.first, exam.second));
        }
    }
}

void Class::assignGradeToStudent(Student* student, Assignment* assignment, double grade) {
    if (assignments.find(assignment->getID()) != assignments.end()) {
        assignments [assignment->getID()]->setGrade(student->getID(), grade);
        student->setGradeForAssignment(assignment->getID(), grade);
    }
}

void Class::assignGradeToStudent(Student* student, Exam* exam, double grade) {
    if (exams.find(exam->getID()) != exams.end()) {
        exams [exam->getID()]->setGrade(student->getID(), grade);
        student->setGradeForExam(exam->getID(), grade);
    }
}


void Class::setStudentGradeForAssignment(string studentID, string assignmentID, double grade) {
    if (assignments.find(assignmentID) != assignments.end()) {
        assignments [assignmentID]->setGrade(studentID, grade);
    }
}

void Class::setStudentGradeForExam(string studentID, string examID, double grade) {
    if (exams.find(examID) != exams.end()) {
        exams [examID]->setGrade(studentID, grade);
    }
}

double Class::getAssignmentGrade(string studentID, string assignmentID) {
    if (assignments.find(assignmentID) != assignments.end()) {
        return assignments [assignmentID]->getGrade(studentID);
    }
    return -1;
}

double Class::getExamGrade(string studentID, string examID) {
    if (exams.find(examID) != exams.end()) {
        return exams [examID]->getGrade(studentID);
    }
    return -1;
}

map<string, Assignment*> Class::getAssignmentGrades() {
    return this->assignments;
}

map<string, Exam*> Class::getExamGrades() {
    return this->exams;
}

double  Class::calculateGrade(Student* student) {
    double totalGrade = 0;
    int totalAssignments = 0;
    int totalExams = 0;
    for (auto& assignment : assignments) {
        totalGrade += assignment.second->getGrade(student->getID());
        totalAssignments++;
    }
    for (auto& exam : exams) {
        totalGrade += exam.second->getGrade(student->getID());
        totalExams++;
    }
    return totalGrade / (totalAssignments + totalExams);
}