#ifndef STUDENT_H
#define STUDENT_H

#include "./people.h"
#include "./class.h"
#include "./assignment.h"

#include <chrono> // date manipulation library
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
class Class;

// TODO Include class and assignment headers when done and do operator overloading

class Student : public People
{
private:
    vector<Class *> classSchedule; // didnt use list<T> because of the better effiency vector provide when traversing elements sequentially
    map<string, string> attendanceRecord;
    map<Assignment *, double> assignmentGrades;

public:
    Student();                                     // default constructor
    Student(string name, string email, string id); // overloaded constructor
    ~Student();                                    // destructor for dynamic vectors
    map<string, string> GetAllAttendanceRecords(); // returns priv attr. attendance record
    double getGradeForAssignment(Assignment *assignment);
    void MarkAttendance(string date, string status);
    void enrollInClass(Class *newClass);

    void setAttendanceRecord(map<string, string> attendanceRecord);
    vector<Class *> &getClassSchedule();

    // operator overloading
    Student &operator=(const Student &RHS);
    friend istream &operator>>(istream &IN, Student &RHS);  // input student class schedule and grades
    friend ostream &operator<<(ostream &OUT, Student &RHS); // output current student class schedule and grades
};

#endif // !STUDENT_H