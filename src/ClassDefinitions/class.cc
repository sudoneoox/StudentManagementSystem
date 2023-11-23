#include "../include/ClassDeclarations/class.h"
#include <iostream>

using namespace std;


/*
Mini method descriptions for class methods are in class.h

*/

Class::Class() {
    this->className = "";
    this->classID = "";
    this->teacher = nullptr;
    this->assignments = map<string, Assignment*>();
    this->exams = map<string, Exam*>();
}

// destructor
Class::~Class() {
    delete teacher; // delete the teacher object
    for (auto& student : studentList) {
        delete student.second; // delete the student object
    }
    for (auto& exam : exams) {
        delete exam.second; // delete the exam object
    }
    for (auto& assignment : assignments) {
        delete assignment.second; // delete the assignment object
    }
}

Class::Class(string name, string classID) {
    this->className = name;
    this->classID = classID;
    this->teacher = nullptr;
    this->assignments = map<string, Assignment*>();
    this->exams = map<string, Exam*>();
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

void Class::setName(string className) {
    this->className = className;
}
void Class::setClassID(string classID) {
    this->classID = classID;
}
void Class::setTeacher(Teacher* teacher) {
    this->teacher = teacher;
}
void Class::setExams(map<string, Exam*>& exams) {
    this->exams = exams;
}
void Class::setAssignments(map<string, Assignment*>& assignments) {
    this->assignments = assignments;
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
    if (assignment) {
        assignments [assignment->getID()] = assignment;
    }
}

void Class::addExam(Exam* exam) {
    if (exam) { // if exam is not null
        exams [exam->getID()] = exam;
    }
}

// sets grade for assignment
void Class::setStudentGradeForAssignment(string& studentID, string& assignmentID, double grade) {
    if (assignments.find(assignmentID) != assignments.end()) {
        assignments [assignmentID]->setGrade(studentID, assignmentID, grade);
    }
}

// sets grade for exam
void Class::setStudentGradeForExam(string& studentID, string& examID, double grade) {
    if (exams.find(examID) != exams.end()) {
        exams [examID]->setGrade(studentID, examID, grade);
    }
}

double Class::getAssignmentGrade(string studentID, string assignmentID) {
    if (assignments.find(assignmentID) != assignments.end()) {
        return assignments [assignmentID]->getGrade(studentID, assignmentID);
    }
    return -1; //grade not found return
}

double Class::getExamGrade(string studentID, string examID) {
    if (exams.find(examID) != exams.end()) {
        return exams [examID]->getGrade(studentID, examID);
    }
    return -1; // grade not found return
}

Assignment* Class::getAssignment(string assignmentID) {
    if (assignments.find(assignmentID) != assignments.end()) {
        return assignments [assignmentID];
    }
    return nullptr;
}

Exam* Class::getExam(string examID) {
    if (exams.find(examID) != exams.end()) {
        return exams [examID];
    }
    return nullptr;
}

map<string, Exam*>& Class::getExams() {
    return exams;
}

map<string, Assignment*>& Class::getAssignments() {
    return assignments;
}

double Class::calculateTotalGrade(string studentID) {
    double totalAssignmentGrade = 0;
    double totalExamGrade = 0;

    for (auto& [id, assignment] : assignments) {
        totalAssignmentGrade += assignment->getGrade(studentID, id);
    }

    for (auto& [id, exam] : exams) {
        totalExamGrade += exam->getGrade(studentID, id);
    }

    double weightOfAssignments = 0.6; // 60% weightage for assignments
    double weightOfExams = 0.4;       // 40% weightage for exams

    return (totalAssignmentGrade * weightOfAssignments + totalExamGrade * weightOfExams) / (assignments.size() * weightOfAssignments + exams.size() * weightOfExams); // returns the total grade
}