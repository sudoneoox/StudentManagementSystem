#ifndef TEACHERMENU_H
#define TEACHERMENU_H

using namespace std;
#include <iostream>

#include "../include/ClassDeclarations/teacher.h"
#include "../include/filemanipulation.h"
#include "../../include/Menu.h"
#include "../../src/MenuFunctions/ClassMenu.h"

extern map<string, Class*>::iterator classIter; // iterator for the class map

void markStudentAttendance(Teacher& teacher); // this allows the teacher to mark the attendance of a student
void updateTeacherInfo(Teacher& teacher); // this allows the teacher to update their information
void enteringClassMenu(Teacher& teacher); // this allows the teacher access to enter a class menu that they teach


// takes in a teacher object and displays the menu for the teacher
void TeacherMenu(Teacher& teacher) {
    string input;
    string name = teacher.getName();
    while (cin >> input) {
        if (input == "1") {
            cout << "Showing Information For " << name << endl;
            cout << teacher << endl;
            PrintMenuOption("Teacher Menu | " + name, "teacherMenuOptions");
        }
        else if (input == "2") {
            markStudentAttendance(teacher);
            PrintMenuOption("Teacher Menu | " + name, "teacherMenuOptions");
        }
        else if (input == "3") {
            updateTeacherInfo(teacher);
            name = teacher.getName();
            PrintMenuOption("Teacher Menu | " + name, "teacherMenuOptions");
        }
        else if (input == "4") {
            enteringClassMenu(teacher);
            PrintMenuOption("Teacher Menu | " + name, "teacherMenuOptions");
        }
        else if (input == "5") {
            cout << "Leaving Teacher Menu\n";
            break;
        }
        else {
            cout << "Invalid Input\n";
            PrintMenuOption("Teacher Menu | " + name, "teacherMenuOptions");
        }
    }
}


// this allows the teacher access to enter a class menu that they teach
void enteringClassMenu(Teacher& teacher) {
    cout << "Enter 0 to go back to the teacher menu at any time\n";
    auto subjectsTaught = teacher.GetSubjectsTaught(); // gets the map of subjects taught by the teacher
    if (subjectsTaught.empty()) {
        cout << "No classes to enter.\n";
        return;
    }
    while (true) {
        for (const auto& [classID, classPtr] : teacher.GetSubjectsTaught()) { // iterates through the map of subjects taught
            if (classPtr != nullptr) {
                cout << classID << ": " << classPtr->getName() << endl;
            }
            else {
                cout << "class with a null pointer in enteringClassMenu\n";
            }
        }
        string classID;
        cout << "Input Class ID: ";
        cin >> classID;
        if (classID == "0") {
            return;
        }
        auto classIter = subjectsTaught.find(classID); // finds the class with the matching ID
        if (classIter == subjectsTaught.end()) {
            cout << "Class ID not found. Please try again.\n";
            continue;
        }
        ClassMenu(*classIter->second); // enters the class menu with a ponter to the class 
        break;
    }
}

// this allows the teacher to update their information
void updateTeacherInfo(Teacher& teacher) {
    cout << "Enter 0 to go back to the teacher menu at any time\n";
    string input;
    string newData;
    while (true) {
        cout << "What would you like to update?\n";
        cout << "1. Name\n";
        cout << "2. Email\n";
        cin >> input;
        if (input == "0") return;
        else if (input == "1") {
            cout << "Enter new name: ";
            cin >> newData;
            teacher.setName(newData); // sets the new name
            break;
        }
        else if (input == "2") {
            cout << "Enter new email: ";
            cin >> newData;
            teacher.setEmail(newData); // sets the new email
            break;
        }
        else {
            cout << "Invalid input. Please try again.\n";
        }

    }
    cout << "\nSuccessfully updated teacher info.\n";
    cout << teacher << endl;
    addDataToJsonFile("../Data/teachers.json", teacher); // adds the updated teacher to the json file
    for (auto& [classID, classPtr] : teacher.GetSubjectsTaught()) {
        addDataToJsonFileFromClass("../Data/class.json", *classPtr); // adds the updated teacher to the json file for the class they teach
    }
}

// this allows the teacher to mark the attendance of a student
void markStudentAttendance(Teacher& teacher) {
    cout << "Enter 0 to go back to the teacher menu at any time\n";

    auto subjectsTaught = teacher.GetSubjectsTaught(); // gets the map of subjects taught by the teacher
    if (subjectsTaught.empty()) {
        cout << "No classes to mark attendance for.\n";
        return;
    }

    while (true) {
        cout << "Which class would you like to mark the attendance for? Enter the Class ID:\n";
        for (const auto& [classID, classPtr] : subjectsTaught) { // iterates through the map of subjects taught
            if (classPtr != nullptr) {
                cout << classID << ": " << classPtr->getName() << endl;
            }
            else {
                cout << "class with a null pointer in markStudentForAttendance\n";
            }
        }

        string classID;
        cout << "Input Class ID: ";
        cin >> classID;
        if (classID == "0") {
            return;
        }

        auto classIter = subjectsTaught.find(classID); // finds the class with the matching ID
        if (classIter == subjectsTaught.end()) {
            cout << "Class ID not found. Please try again.\n";
            continue;
        }

        map<string, Student*> students = classIter->second->getStudents(); // gets the map of students in the class
        if (students.empty()) {
            cout << "No students enrolled in this class.\n";
            continue;
        }

        cout << "Enter the ID of the student you would like to mark:\n";
        for (const auto& [studentID, studentPtr] : students) {
            cout << studentID << ": " << studentPtr->getName() << endl; // iterates through the map of students in the class
        }

        string studentID;
        cout << "Input Student ID: ";
        cin >> studentID;
        if (studentID == "0") {
            return;
        }

        auto studentIter = students.find(studentID); // finds the student with the matching ID
        if (studentIter == students.end()) {
            cout << "Student ID not found. Please try again.\n";
            continue;
        }

        string date, status;
        cout << "Enter the Date you would like to mark (MM/DD/YYYY): ";
        cin >> date;
        cout << "PRESENT / ABSENT / TARDY?: ";
        cin >> status;
        markAttendance(*studentIter->second, date, status); // marks the attendance of the student with the given date and status
        break;
    }
}

// this function checks if the ID entered by the user is valid if its valid it returns true and sets the idx to the index of the teacher in the map
bool validationCheck(map<string, Teacher*> teachers, int& idx) {
    string ID;
    map<string, Teacher*>::iterator iter;

    // Loop until the user enters a valid ID or 0 to go back
    while (true) {
        cout << "Enter your teacherID or 0 to go back: ";
        cin >> ID;
        if (ID == "0") {
            return false; // Return false if user enters 0, this will take them back to the main menu
        }

        // iterate through map of students to find the student with the matching ID
        iter = teachers.find(ID);
        if (iter != teachers.end()) {
            idx = stoi(ID);
            return true; // Return true if the ID is valid
        }

        cout << "Invalid ID Try Again or Enter 0 to go back to the portal\n";
    }
}

#endif // !TEACHERMENU_H