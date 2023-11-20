#include "../include/ClassDeclarations/assignment.h"
#include "../include/ClassDeclarations/class.h"
#include "../include/ClassDeclarations/people.h"
#include "../include/ClassDeclarations/student.h"
#include "../include/ClassDeclarations/teacher.h"
#include "../include/filemanipulation.h"
#include "../include/Menu.h"

#include "./MenuFunctions/StudentMenu.h"
#include "./MenuFunctions/TeacherMenu.h"
#include "./MenuFunctions/ClassMenu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json; // exteral library for json manipulation documentation: https://github.com/nlohmann/json

// global variables a bunch of functions use these and I didnt want to pass them as reference to every function it would make them 
// unreadable and hard to follow
map<string, Teacher*> allTeachers;
map<string, Student*> allStudents;
map<string, Class*> allClasses;


// iter for global variables
map<string, Class*>::iterator classIter;
map<string, Student*>::iterator studentIter;
map<string, Teacher*>::iterator teacherIter;

void initClasses();
void deleteInitData();


int main() {
    initClasses(); // creates initial data for testing purposes jump to function for documentation
    preloadDataJsonFile("student", "../Data/students.json"); // loads data from json files jump to function for documentation 
    preloadDataJsonFile("teacher", "../Data/teachers.json");
    preloadDataJsonFile("class", "../Data/class.json");

    char input;
    PrintMenuOption("Student Management System", "mainMenuOptions");
    while (cin >> input) {
        if (input == '1') {
            int idx;
            bool correctID = validationCheck(allStudents, idx);
            if (correctID) {
                string name = allStudents [to_string(idx)]->getName();
                PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
                studentMenu(*(allStudents [to_string(idx)]));
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
            else if (!correctID) {
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
        }
        else if (input == '2') {
            int idx;
            bool correctID = validationCheck(allTeachers, idx);
            if (correctID) {
                string name = allTeachers [to_string(idx)]->getName();
                PrintMenuOption("Teacher Menu | " + name, "teacherMenuOptions");
                TeacherMenu(*(allTeachers [to_string(idx)]));
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
            else if (!correctID) {
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
        }
        else if (input == '3') {
            cout << "Exiting Program\n";
        }

        else {
            cout << "Invalid option Please Try Again\n ";
            PrintMenuOption("Student Management System", "mainMenuOptions");
        }
    }
    deleteInitData();
    return 0;
}


/*
Im essentially creating data for the program to use for testing purposes im linking all the data together
with pointers this is how the program will work when it is fully implemented since the Class class is composed of a teacher and students etc.
this is also to initiliaze data so that there is data for the preload Data function to Use

this function isnt necessary or integral for the program to work
but shows an example of how the json is going to hold the object data
You can go to the Data/json files to see for yourself

whenever the program ends it will delete all the data that was created in this function
and whenever the program starts it will load the data from the json files to create the objects again and any objects you added through the menu
*/

void initClasses() {

    map<string, string> currentDateAttendance = { {currentDate(), "ABSENT"} }; // {date, status} gets current date in format "MM/DD/YYYY"

    // students
    Student* student1 = new Student("Diego Coronado", "drcorona@cougarnet.uh.edu", "2303693");
    Student* student2 = new Student("Cassandra Franco", "francocm@edu.com", "2303694");
    Student* student3 = new Student("John Wick", "johnwick@edu.com", "2303695");
    Student* student4 = new Student("Bob Frank", "bobfrank@edu.com", "2303696");
    Student* student5 = new Student("Sally Sue", "sallysue@edu.com", "2303697");
    Student* student6 = new Student("John Doe", "johndoe@edu.com", "2303698");

    // teachers
    Teacher* teacher1 = new Teacher("Carlos Rincon", "rincon@edu.com", "2000");
    Teacher* teacher2 = new Teacher("Melahut Almus", "melahutalmus@edu.com", "2001");
    Teacher* teacher3 = new Teacher("Holly Smith", "hsmith@edu.com", "2002");
    Teacher* teacher4 = new Teacher("Jakavitch", "jaka@edu.com", "2003");

    // classes
    Class* mathClass = new Class("Math 2413", "C001"); // name, id
    Class* scienceClass = new Class("Biology 1302", "C002");
    Class* englishClass = new Class("English 1301", "C003");
    Class* computerScienceClass = new Class("Computer Science 1301", "C004");

    // Create assignments and exams for each class
    Assignment* mathAssignment = new Assignment("Derivatives", "M101"); // name, id
    Assignment* scienceAssignment = new Assignment("Biology", "S101");
    Assignment* englishAssignment = new Assignment("Writing", "E101");
    Assignment* CSassignment = new Assignment("Data Structure", "CS101");

    Exam* mathExam = new Exam("Calculus Exam", "ME101");
    Exam* scienceExam = new Exam("Biology Exam", "SE101");
    Exam* englishExam = new Exam("Literature Exam", "EE101");
    Exam* CSexam = new Exam("Programming Exam", "CSE101");

    // Linking assignments and exams to classes
    mathClass->addAssignment(mathAssignment);
    scienceClass->addAssignment(scienceAssignment);
    englishClass->addAssignment(englishAssignment);
    computerScienceClass->addAssignment(CSassignment);

    mathClass->addExam(mathExam);
    scienceClass->addExam(scienceExam);
    englishClass->addExam(englishExam);
    computerScienceClass->addExam(CSexam);

    //TODO implement student->setGrade?
    // Assign grades to students in each class for assignments and exams
    mathClass->assignGradeToStudent(student1, mathAssignment, 80); // student, assignment, grade
    mathClass->assignGradeToStudent(student2, mathAssignment, 85);

    scienceClass->assignGradeToStudent(student3, scienceAssignment, 90);
    scienceClass->assignGradeToStudent(student4, scienceAssignment, 88);

    englishClass->assignGradeToStudent(student5, englishAssignment, 92);
    englishClass->assignGradeToStudent(student6, englishAssignment, 87);

    computerScienceClass->assignGradeToStudent(student1, CSassignment, 75);
    computerScienceClass->assignGradeToStudent(student2, CSassignment, 80);

    mathClass->assignGradeToStudent(student1, mathExam, 75); // student, exam, grade
    scienceClass->assignGradeToStudent(student2, scienceExam, 85);
    englishClass->assignGradeToStudent(student3, englishExam, 90);
    computerScienceClass->assignGradeToStudent(student4, CSexam, 95);

    //setting the attendance of the current students to absent this is just to preload the json data
    student1->setAttendanceRecord(currentDateAttendance);
    student2->setAttendanceRecord(currentDateAttendance);
    student3->setAttendanceRecord(currentDateAttendance);
    student4->setAttendanceRecord(currentDateAttendance);
    student5->setAttendanceRecord(currentDateAttendance);
    student6->setAttendanceRecord(currentDateAttendance);

    // setting the classes to their respective teacher to link them together addsubject takes the pointer to the class
    teacher1->addSubject(mathClass);
    teacher2->addSubject(scienceClass);
    teacher3->addSubject(englishClass);
    teacher4->addSubject(computerScienceClass);

    // Add all students and teacher and class ID, and pointers to their global maps holding all their data;
    allStudents = { {"2303693", student1}, {"2303694", student2}, {"2303695", student3}, {"2303696", student4}, {"2303697", student5}, {"2303698", student6} };
    allTeachers = { {"2000", teacher1}, {"2001", teacher2}, {"2002", teacher3}, {"2003", teacher4} };
    allClasses = { {"C001", mathClass}, {"C002", scienceClass}, {"C003", englishClass}, {"C004", computerScienceClass} };

    // Add teacher to class and add students to class
    allClasses ["C001"]->setTeacher(allTeachers ["2000"]);
    allClasses ["C002"]->setTeacher(allTeachers ["2001"]);
    allClasses ["C003"]->setTeacher(allTeachers ["2002"]);
    allClasses ["C004"]->setTeacher(allTeachers ["2003"]);

    allClasses ["C001"]->addStudent(allStudents ["2303693"]);
    allClasses ["C001"]->addStudent(allStudents ["2303694"]);
    allClasses ["C001"]->addStudent(allStudents ["2303695"]);

    allClasses ["C002"]->addStudent(allStudents ["2303695"]);
    allClasses ["C002"]->addStudent(allStudents ["2303694"]);
    allClasses ["C002"]->addStudent(allStudents ["2303693"]);

    allClasses ["C003"]->addStudent(allStudents ["2303697"]);
    allClasses ["C003"]->addStudent(allStudents ["2303696"]);

    allClasses ["C004"]->addStudent(allStudents ["2303698"]);
    allClasses ["C004"]->addStudent(allStudents ["2303697"]);

    // Add class to student this links them with each other through pointers
    allStudents ["2303693"]->enrollInClass(allClasses ["C001"]);
    allStudents ["2303694"]->enrollInClass(allClasses ["C001"]);
    allStudents ["2303695"]->enrollInClass(allClasses ["C001"]);


    allStudents ["2303695"]->enrollInClass(allClasses ["C002"]);
    allStudents ["2303694"]->enrollInClass(allClasses ["C002"]);
    allStudents ["2303693"]->enrollInClass(allClasses ["C002"]);

    allStudents ["2303697"]->enrollInClass(allClasses ["C003"]);
    allStudents ["2303696"]->enrollInClass(allClasses ["C003"]);

    allStudents ["2303698"]->enrollInClass(allClasses ["C004"]);
    allStudents ["2303697"]->enrollInClass(allClasses ["C004"]);

}

/*
Deletes all the data pointers that was created in the initClasses function when the program ends
each object has a destructor that deletes all the pointers that it holds so
this function is just to delete the pointers that are in the global maps
*/
void deleteInitData() {
    for (auto& student : allStudents) {
        delete student.second;
    }
    for (auto& teacher : allTeachers) {
        delete teacher.second;
    }
    for (auto& class_ : allClasses) {
        delete class_.second;
    }
}