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
using json = nlohmann::json;


map<string, Teacher*> allTeachers;
map<string, Student*> allStudents;
map<string, Class*> allClasses;

void initClasses();
void deleteInitData();


int main() {
    initClasses();
    preloadDataJsonFile("student", "../Data/students.json");
    preloadDataJsonFile("teacher", "../Data/teachers.json");
    preloadDataJsonFile("class", "../Data/class.json");

    char input;
    PrintMenuOption("Student Management System", "mainMenuOptions");
    while (cin >> input)
    {
        if (input == '1')
        {
            int idx;
            bool correctID = validationCheck(allStudents, idx);
            if (correctID)
            {
                string name = allStudents[to_string(idx)]->getName();
                PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
                studentMenu(*(allStudents[to_string(idx)]));
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
            else if (!correctID)
            {
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
        }
        else if (input == '2')
        {
            PrintMenuOption("Teacher Menu", "teacherMenuOptions");
            TeacherMenu();
        }
        else if (input == '3')
        {
            PrintMenuOption("Class Menu", "classMenuOptions");
            ClassMenu(allClasses);
        }
        else if (input == '4')
        {
            cout << "Exiting program\n";
            break;
        }
        else
        {
            cout << "Invalid option Please Try Again\n ";
            PrintMenuOption("Student Management System", "mainMenuOptions");
        }
    }
    deleteInitData();
    return 0;
}


void initClasses() {
    map<string, string> currentDateAttendance = { {currentDate(), "PRESENT"} }; // {date, status} gets current date in format "MM/DD/YYYY"

    Student* student1 = new Student("Diego Coronado", "drcorona@cougarnet.uh.edu", "2303693"); // name, email, ID
    Student* student2 = new Student("Cassandra Franco", "francocm@edu.com", "2303694");
    Student* student3 = new Student("John Wick", "johnwick@edu.com", "2303695");
    Teacher* teacher1 = new Teacher("Carlos Rincon", "rincon@edu.com", "2000"); // name, email, ID
    Teacher* teacher2 = new Teacher("Melahut Almus", "melahutalmus@edu.com", "2001");
    Class* mathClass = new Class("Math 101", "C001"); // name, ID
    Class* scienceClass = new Class("Science 102", "C002");

    student1->setAttendanceRecord(currentDateAttendance);

    teacher1->addSubject(mathClass);
    teacher2->addSubject(scienceClass);

    // Add all students and teacher and class ID, and pointers to their global maps holding all their data;
    allStudents = { {"1000", student1},{"1001", student2},{"1002", student3}, };
    allTeachers = { {"2000", teacher1},{"2001", teacher2} };
    allClasses = { {"C001", mathClass}, {"C002", scienceClass} };

    // Add teacher to class and add students to class
    allClasses["C001"]->setTeacher(allTeachers["2000"]);
    allClasses["C002"]->setTeacher(allTeachers["2001"]);

    allClasses["C001"]->addStudent(allStudents["1000"]);
    allClasses["C001"]->addStudent(allStudents["1001"]);
    allClasses["C002"]->addStudent(allStudents["1002"]);
    allClasses["C002"]->addStudent(allStudents["1001"]);

    // Add class to student this links them with each other through pointers
    allStudents["1000"]->enrollInClass(allClasses["C001"]);
    allStudents["1001"]->enrollInClass(allClasses["C001"]);
    allStudents["1002"]->enrollInClass(allClasses["C002"]);
    allStudents["1001"]->enrollInClass(allClasses["C002"]);

}

// Deletes all the data pointers that was created in the initClasses function memory management
void deleteInitData() {
    for (auto& student : allStudents)
    {
        delete student.second;
    }
    for (auto& teacher : allTeachers)
    {
        delete teacher.second;
    }
    for (auto& class_ : allClasses)
    {
        delete class_.second;
    }
}