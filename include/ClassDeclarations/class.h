
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
    Teacher* teacher;

    map<string, Student*> studentList; // studentID, student pointer
    map<string, Exam*>  exams; // assignmentID, studentID, grade    
    map<string, Assignment*> assignments; // assignmentID, studentID, grade

public:
    // constructor
    Class();


    // destructor
    ~Class();

    Class(string name, string classID);
    Class(const Class& otherClass);
    void setName(string className);
    void setClassID(string classID);
    void setTeacher(Teacher* teacher);
    void setStudentList(map<string, Student*> studentList);
    void addStudent(Student* Student);
    void removeStudent(Student* Student);

    void addAssignment(Assignment* assignment);
    void addAssignment(map<string, Assignment*> assignments);
    void addExam(map<string, Exam*> exams);
    void addExam(Exam* exam);
    void setStudentGradeForAssignment(string studentID, string assignmentID, double grade);
    void setStudentGradeForExam(string studentID, string examID, double grade);

    void assignGradeToStudent(Student* student, Assignment* assignment, double grade);
    void assignGradeToStudent(Student* student, Exam* exam, double grade);
    double calculateGrade(Student* student);

    double getAssignmentGrade(string studentID, string assignmentID);
    map<string, Assignment*> getAssignmentGrades();
    map<string, Exam*> getExamGrades();
    double getExamGrade(string studentID, string examID);



    string getName();
    string getClassID();
    Teacher* getTeacher();
    string getID();
    map<string, Student*> getStudents();


};

#endif // !CLASS_H
