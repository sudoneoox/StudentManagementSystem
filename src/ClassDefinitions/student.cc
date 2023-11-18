#include "../include/ClassDeclarations/student.h"

using namespace std;

// TODO update methods after working on ASSIGNMENT CLASS
//  CLASS Class

Student::Student() {
    this->name = "";
    this->email = "";
    this->ID = "";
    map<string, Class*> classSchedule;
    map<string, string> attendanceRecord;
    map<Assignment*, double> assignmentGrades;
}

Student::Student(string name, string email, string id) {
    this->name = name;
    this->email = email;
    this->ID = id;
    map<string, Class*> classSchedule;
    map<string, string> attendanceRecord;
    map<Assignment*, double> assignmentGrades;
}

Student::~Student() {
    map<Assignment*, double>::iterator iter;
    map<string, Class*>::iterator iter2;
    for (iter = assignmentGrades.begin(); iter != assignmentGrades.end(); iter++) {
        delete iter->first;
    }
    for (iter2 = classSchedule.begin(); iter2 != classSchedule.end(); iter2++) {
        delete iter2->second;
    }
}

map<string, string> Student::GetAllAttendanceRecords() {
    return attendanceRecord;
}
void Student::printClassSchedule() {
    cout << "Class Schedule: " << endl;
    for (auto iter = classSchedule.begin(); iter != classSchedule.end(); iter++) {
        cout << iter->second->getName() << endl;
    }
}

void Student::MarkAttendance(string date, string status) {
    auto iter = attendanceRecord.find(date);

    // Check if the attendance record for the date exists and the status is "present"
    if (iter != attendanceRecord.end() && iter->second == "PRESENT") {
        cout << "Attendance already marked as present for Date: " << date << endl;
    }
    else {
        // Add or update the attendance record
        cout << "updated \n";
        attendanceRecord [date] = status;
    }
}

double Student::getGradeForAssignment(Assignment* assignment) {
    // return assignment->getGrade();
    return 3.3;
}

void Student::enrollInClass(Class* newClass) {
    classSchedule [newClass->getClassID()] = newClass;
}
void Student::enrollInClasses(map<string, Class*> newClasses) {
    for (auto iter = newClasses.begin(); iter != newClasses.end(); iter++) {
        classSchedule [iter->first] = iter->second;
    }
}
bool Student::isEnrolledInClass(string classID) {
    auto iter = classSchedule.find(classID);
    if (iter != classSchedule.end()) {
        return true;
    }
    else {
        return false;
    }
}
ostream& operator<<(ostream& OUT, Student& RHS) {
    OUT << "Student Name: " << RHS.name << endl;
    OUT << "Student Email: " << RHS.email << endl;
    OUT << "Student ID: " << RHS.ID << endl;
    OUT << "Student Class Schedule: " << endl;
    for (auto iter = RHS.classSchedule.begin(); iter != RHS.classSchedule.end(); iter++) {
        OUT << iter->second->getName() << endl;
    }
    return OUT;
}

istream& operator>>(istream& IN, Student& RHS) {
    cout << "Enter Student Name: ";
    IN >> RHS.name;
    cout << "Enter Student Email: ";
    IN >> RHS.email;
    cout << "Enter Student ID: ";
    IN >> RHS.ID;
    return IN;
}

map<string, Class*>& Student::getClassSchedule() {
    return classSchedule;
}

Student& Student::operator=(const Student& RHS) {
    this->name = RHS.name;
    this->email = RHS.email;
    this->ID = RHS.ID;
    this->classSchedule = RHS.classSchedule;
    this->attendanceRecord = RHS.attendanceRecord;
    // this->assignmentGrades = RHS.assignmentGrades;
    return *this;
}

void Student::setAttendanceRecord(map<string, string> attendanceRecord) {
    this->attendanceRecord = attendanceRecord;
}