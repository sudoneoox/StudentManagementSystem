
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
    Class(string name, string classID);
    Class(const Class& otherClass);

    // destructor
    ~Class();

    // setters
    void setName(string className);
    void setClassID(string classID);
    void setTeacher(Teacher* teacher);
    void setStudentList(map<string, Student*> studentList);
    void setExams(map<string, Exam*>& exams);
    void setAssignments(map<string, Assignment*>& assignments);


    // methods for managing students
    void addStudent(Student* Student);
    void removeStudent(Student* Student);


    // methods for managing assignments and exams
    void addAssignment(Assignment* assignment);
    void addExam(Exam* exam);
    void setStudentGradeForAssignment(string& studentID, string& assignmentID, double grade);
    void setStudentGradeForExam(string& studentID, string& examID, double grade);
    void assignGradeToStudent(Student* student, Assignment* assignment, double grade);
    void assignGradeToStudent(Student* student, Exam* exam, double grade);

    // getters
    string getName();
    string getClassID();
    Teacher* getTeacher();
    string getID();
    map<string, Student*> getStudents();
    Exam* getExam(string examID);
    Assignment* getAssignment(string assignmentID);
    double getExamGrade(string studentID, string examID);
    double getAssignmentGrade(string studentID, string assignmentID);
    map<string, Exam*>& getExams();
    map<string, Assignment*>& getAssignments();
    double calculateTotalGrade(string studentID);





};

#endif // !CLASS_H
