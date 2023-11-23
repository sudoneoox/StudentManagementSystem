#ifndef STUDENT_H
#define STUDENT_H

#include "./people.h"
#include "./class.h"
#include "./assignment.h"
#include "./exam.h"

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
    map<string, Class*> classSchedule; // classID, class pointer
    map<string, string> attendanceRecord;

    map<string, double> assignmentGrades; // assignmentID, grade
    map<string, double> examGrades;       // examID, grade

    // classID to know which class it came from and, assig nment pointer

public:
    Student();                                     // default constructor
    Student(string name, string email, string id); // overloaded constructor
    ~Student();                                    // destructor for dynamic vectors
    map<string, string> GetAllAttendanceRecords(); // returns priv attr. attendance record
    string GetAttendanceRecordRange(string startDate, string endDate);       // returns priv attr. attendance record for a specific date
    void MarkAttendance(string date, string status);
    void enrollInClass(Class* newClass);
    void enrollInClasses(map<string, Class*> newClasses);
    void dropClass(Class* classToDrop);
    void dropClasses(vector<Class*> classesToDrop);
    bool isEnrolledInClass(string classID);
    void printClassSchedule();

    double getGradeForAssignment(string classID, string assignmentID);
    double getGradeForExam(string classID, string examID);

    map<string, double> getGradesForAssignment();
    map<string, double> getGradesForExam();

    void setGradeForAssignment(string assignmentID, double grade);
    void setGradeForExam(string examID, double grade);


    void setAttendanceRecord(map<string, string> attendanceRecord);
    map<string, Class*>& getClassSchedule();

    // operator overloading
    Student& operator=(const Student& RHS);
    friend istream& operator>>(istream& IN, Student& RHS);  // input student class schedule and grades
    friend ostream& operator<<(ostream& OUT, Student& RHS); // output current student class schedule and grades
};

#endif // !STUDENT_H