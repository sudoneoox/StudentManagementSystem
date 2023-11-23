#ifndef STUDENT_H
#define STUDENT_H

#include "./people.h"
#include "./class.h"
#include "./assignment.h"
#include "./exam.h"

#include <chrono> // date manipulation library
#include <string>
#include <map>
#include <iostream>


using namespace std;
class Class;
class Student : public People // inherits from people class
{
private:
    map<string, Class*> classSchedule; // classID, class pointer
    map<string, string> attendanceRecord; // date, status

    map<string, double> assignmentGrades; // assignmentID, grade
    map<string, double> examGrades;       // examID, grade


public:
    // constructors and destructors
    Student();
    Student(string name, string email, string id);
    ~Student();

    // getters 
    map<string, string> GetAllAttendanceRecords(); // returns all attendance records
    string GetAttendanceRecordRange(string startDate, string endDate); // returns attendance records between two dates
    double getGradeForAssignment(string classID, string assignmentID); // returns grade for assignment
    double getGradeForExam(string classID, string examID); // returns grade for exam
    map<string, double> getGradesForAssignment(); // returns all grades for assignments
    map<string, double> getGradesForExam(); // returns all grades for exams
    map<string, Class*>& getClassSchedule(); // returns class schedule

    //setters
    void setGradeForAssignment(string assignmentID, double grade); // sets grade for assignment
    void setGradeForExam(string examID, double grade); // sets grade for exam
    void setAttendanceRecord(map<string, string> attendanceRecord); // sets attendance record

    // other functions / helper functions / methods
    void MarkAttendance(string date, string status); // marks attendance for a student
    void enrollInClass(Class* newClass); // enrolls student in a class
    void enrollInClasses(map<string, Class*> newClasses); // enrolls student in multiple classes
    void dropClass(Class* classToDrop); //drops a class
    bool isEnrolledInClass(string classID); // checks if student is enrolled in a class
    void printClassSchedule(); // prints class schedule

    // operator overloading
    friend istream& operator>>(istream& IN, Student& RHS);  // input student class schedule and grades
    friend ostream& operator<<(ostream& OUT, Student& RHS); // output current student class schedule and grades
};

#endif // !STUDENT_H