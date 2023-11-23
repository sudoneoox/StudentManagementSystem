#include "../include/ClassDeclarations/student.h"
#include "../include/ClassDeclarations/class.h"
#include <cstring>

using namespace std;
/*
Mini code description for student methods are in student.h
*/

Student::Student() {
    this->name = "";
    this->email = "";
    this->ID = "";
    map<string, Class*> classSchedule(); // classID, Class*
    map<string, string> attendanceRecord(); // date, status
    map<string, double> assignmentGrades(); // assignmentID, grade
    map<string, double> examGrades(); // examID, grade

}

Student::Student(string name, string email, string id) {
    this->name = name;
    this->email = email;
    this->ID = id;
    map<string, Class*> classSchedule();
    map<string, string> attendanceRecord();
    map<string, double> assignmentGrades();
    map<string, double> examGrades();
}

Student::~Student() {
    map<string, Class*>::iterator iter;
    for (iter = classSchedule.begin(); iter != classSchedule.end(); iter++) {
        delete iter->second; // delete the class object
    }

}

map<string, string> Student::GetAllAttendanceRecords() {
    return attendanceRecord;
}

string Student::GetAttendanceRecordRange(string startDate, string endDate) {
    string attendanceRecordRange;
    bool started = false;
    for (const auto& record : this->attendanceRecord) {
        if (record.first == startDate) {
            started = true;
        }
        if (started) {
            attendanceRecordRange += record.first + ": " + record.second + "\n";
        }
        if (record.first == endDate) {
            break;
        }
    }
    if (!started) {
        // If the loop never started, then the start date was not found
        attendanceRecordRange = "No data for date range " + startDate + " to " + endDate;
    }
    return attendanceRecordRange;
}



void Student::printClassSchedule() {
    for (auto iter = classSchedule.begin(); iter != classSchedule.end(); iter++) {
        cout << iter->second->getName() << endl;
    }
}

void Student::MarkAttendance(string date, string status) {
    auto iter = attendanceRecord.find(date);

    // Check if the attendance record for the date exists and the status is "present"
    if (iter != attendanceRecord.end() && iter->second == "PRESENT") {
        cout << "\nAttendance already marked as present for Date: " << date << endl;
    }
    else {
        // Add or update the attendance record for the date
        attendanceRecord [date] = status;
    }
}



void Student::enrollInClass(Class* newClass) {
    classSchedule [newClass->getClassID()] = newClass;
}

void Student::enrollInClasses(map<string, Class*> newClasses) {
    for (auto iter = newClasses.begin(); iter != newClasses.end(); iter++) {
        classSchedule [iter->first] = iter->second;
    }
}

void Student::dropClass(Class* classToDrop) {
    auto iter = classSchedule.find(classToDrop->getClassID());
    if (iter != classSchedule.end()) {
        classSchedule.erase(iter);
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

void Student::setAttendanceRecord(map<string, string> attendanceRecord) {
    this->attendanceRecord = attendanceRecord;
}

double Student::getGradeForAssignment(string classID, string assignmentID) {
    if (classSchedule.find(classID) != classSchedule.end()) {
        return classSchedule [classID]->getAssignmentGrade(this->getID(), assignmentID);
    }
    return -1;
}

double Student::getGradeForExam(string classID, string examID) {
    if (classSchedule.find(classID) != classSchedule.end()) {
        return classSchedule [classID]->getExamGrade(this->getID(), examID);
    }
    return -1;
}

void Student::setGradeForAssignment(string assignmentID, double grade) {
    assignmentGrades [assignmentID] = grade; // assignmentID, grade
}

void Student::setGradeForExam(string examID, double grade) {
    examGrades [examID] = grade; // examID, grade
}

map<string, double> Student::getGradesForAssignment() {
    return assignmentGrades;
}

map<string, double> Student::getGradesForExam() {
    return examGrades;
}

