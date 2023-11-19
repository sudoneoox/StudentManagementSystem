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
            break;
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

    Student* student1 = new Student("Diego Coronado", "drcorona@cougarnet.uh.edu", "2303693"); // name, email, ID
    Student* student2 = new Student("Cassandra Franco", "francocm@edu.com", "2303694");
    Student* student3 = new Student("John Wick", "johnwick@edu.com", "2303695");
    Teacher* teacher1 = new Teacher("Carlos Rincon", "rincon@edu.com", "2000"); // name, email, ID
    Teacher* teacher2 = new Teacher("Melahut Almus", "melahutalmus@edu.com", "2001");
    Class* mathClass = new Class("Math 101", "C001"); // name, ID
    cout << "in init function " << mathClass->getName() << " pointer: " << mathClass;
    Class* scienceClass = new Class("Science 102", "C002");

    student1->setAttendanceRecord(currentDateAttendance);

    teacher1->addSubject(mathClass);
    teacher2->addSubject(scienceClass);

    // Add all students and teacher and class ID, and pointers to their global maps holding all their data;
    allStudents = { {"1000", student1},{"1001", student2},{"1002", student3}, };
    allTeachers = { {"2000", teacher1},{"2001", teacher2} };
    allClasses = { {"C001", mathClass}, {"C002", scienceClass} };

    // Add teacher to class and add students to class
    allClasses ["C001"]->setTeacher(allTeachers ["2000"]);
    allClasses ["C002"]->setTeacher(allTeachers ["2001"]);

    allClasses ["C001"]->addStudent(allStudents ["1000"]);
    allClasses ["C001"]->addStudent(allStudents ["1001"]);
    allClasses ["C002"]->addStudent(allStudents ["1002"]);
    allClasses ["C002"]->addStudent(allStudents ["1001"]);

    // Add class to student this links them with each other through pointers
    allStudents ["1000"]->enrollInClass(allClasses ["C001"]);
    allStudents ["1001"]->enrollInClass(allClasses ["C001"]);
    allStudents ["1002"]->enrollInClass(allClasses ["C002"]);
    allStudents ["1001"]->enrollInClass(allClasses ["C002"]);
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