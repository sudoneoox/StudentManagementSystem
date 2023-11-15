#include "../include/ClassDeclarations/student.h"

using namespace std;

// TODO update methods after working on ASSIGNMENT CLASS
//  CLASS Class

Student::Student()
{
    this->name = "";
    this->email = "";
    this->ID = "";
    vector<Class *> classSchedule;
    map<string, string> attendanceRecord;
    map<Assignment *, double> assignmentGrades;
}

Student::Student(string name, string email, string id)
{
    this->name = name;
    this->email = email;
    this->ID = id;
    vector<Class *> classSchedule;
    map<string, string> attendanceRecord;
    map<Assignment *, double> assignmentGrades;
}

Student::~Student()
{
    map<Assignment *, double>::iterator iter;
    for (iter = assignmentGrades.begin(); iter != assignmentGrades.end(); iter++)
    {
        delete iter->first;
    }
    for (int i = 0; i < classSchedule.size(); i++)
    {
        delete classSchedule.at(i);
    }
}

map<string, string> Student::GetAllAttendanceRecords()
{
    return attendanceRecord;
}

void Student::MarkAttendance(string date, string status)
{
    map<string, string>::iterator iter;
    iter = this->attendanceRecord.find(date);
    if (iter == attendanceRecord.end())
    {
        attendanceRecord[date] = status;
    }
    else
    {
        cout << "Attendance already inputed for Date: " << endl;
    }
}

double Student::getGradeForAssignment(Assignment *assignment)
{
    // return assignment->getGrade();
    return 3.3;
}

void Student::enrollInClass(Class *newClass)
{
    classSchedule.push_back(newClass); // add class to student
    newClass->addStudent(this);        // add student to class
}

ostream &operator<<(ostream &OUT, Student &RHS)
{
    OUT << "Student Name: " << RHS.name << endl;
    OUT << "Student Email: " << RHS.email << endl;
    OUT << "Student ID: " << RHS.ID << endl;
    OUT << "Student Class Schedule: " << endl;
    for (int i = 0; i < RHS.classSchedule.size(); i++)
    {
        OUT << RHS.classSchedule.at(i)->getName() << endl;
    }

    return OUT;
}

istream &operator>>(istream &IN, Student &RHS)
{
    cout << "Enter Student Name: ";
    IN >> RHS.name;
    cout << "Enter Student Email: ";
    IN >> RHS.email;
    cout << "Enter Student ID: ";
    IN >> RHS.ID;
    return IN;
}

vector<Class *> &Student::getClassSchedule()
{
    return classSchedule;
}

Student &Student::operator=(const Student &RHS)
{
    this->name = RHS.name;
    this->email = RHS.email;
    this->ID = RHS.ID;
    this->classSchedule = RHS.classSchedule;
    this->attendanceRecord = RHS.attendanceRecord;
    // this->assignmentGrades = RHS.assignmentGrades;
    return *this;
}

void Student::setAttendanceRecord(map<string, string> attendanceRecord)
{
    this->attendanceRecord = attendanceRecord;
}