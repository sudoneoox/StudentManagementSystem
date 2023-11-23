
#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "./teacher.h"
#include "./student.h"
#include "./exam.h"

class Teacher;
class Student;

class Class
{
private:
    string className;
    string classID;
    Teacher* teacher; // teacher pointer

    map<string, Student*> studentList; // studentID, student pointer
    map<string, Exam*>  exams;  // assignmentID, studentID, grade    
    map<string, Assignment*> assignments; // assignmentID, studentID, grade

public:
    // constructor
    Class();
    Class(string name, string classID);

    // destructor
    ~Class();

    // setters
    void setName(string className);  // sets class name
    void setClassID(string classID); // sets class ID
    void setTeacher(Teacher* teacher); // sets teacher
    void setStudentList(map<string, Student*> studentList); // sets student list
    void setExams(map<string, Exam*>& exams); // sets exams
    void setAssignments(map<string, Assignment*>& assignments); // sets assignments


    // methods for managing students 
    void addStudent(Student* Student); // adds student to class
    void removeStudent(Student* Student); // removes student from class


    // methods for managing assignments and exams
    void addAssignment(Assignment* assignment); // adds assignment to class
    void addExam(Exam* exam); // adds exam to class
    void setStudentGradeForAssignment(string& studentID, string& assignmentID, double grade); // sets grade for assignment
    void setStudentGradeForExam(string& studentID, string& examID, double grade); // sets grade for exam

    // getters
    string getName();
    string getClassID();
    Teacher* getTeacher(); // returns teacher pointer
    string getID(); // returns class ID used by helper functions within map class I didnt want to confuse it with classID in outside functions
    map<string, Student*> getStudents(); // returns student list
    Exam* getExam(string examID); // returns exam pointer
    Assignment* getAssignment(string assignmentID); // returns assignment pointer
    double getExamGrade(string studentID, string examID); // returns exam grade
    double getAssignmentGrade(string studentID, string assignmentID); // returns assignment grade
    map<string, Exam*>& getExams(); // returns exams
    map<string, Assignment*>& getAssignments(); // returns assignments
    double calculateTotalGrade(string studentID); // calculates total grade for student
};

#endif // !CLASS_H
