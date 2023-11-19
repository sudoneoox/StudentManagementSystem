#ifndef TEACHERMENU_H
#define TEACHERMENU_H

using namespace std;
#include <iostream>

#include "../include/ClassDeclarations/teacher.h"
#include "../include/filemanipulation.h"
#include "../../include/Menu.h"
#include "../../src/MenuFunctions/ClassMenu.h"

extern map<string, Class*>::iterator classIter;

void markStudentAttendance(Teacher& teacher);
void updateTeacherInfo(Teacher& teacher);
void enteringClassMenu(Teacher& teacher);

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

void enteringClassMenu(Teacher& teacher) {
    cout << "Enter 0 to go back to the teacher menu at any time\n";
    auto subjectsTaught = teacher.GetSubjectsTaught();
    if (subjectsTaught.empty()) {
        cout << "No classes to enter.\n";
        return;
    }
    while (true) {
        for (const auto& [classID, classPtr] : teacher.GetSubjectsTaught()) {
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
        auto classIter = subjectsTaught.find(classID);
        if (classIter == subjectsTaught.end()) {
            cout << "Class ID not found. Please try again.\n";
            continue;
        }
        ClassMenu(*classIter->second);
        break;
    }
}

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
            teacher.setName(newData);
            break;
        }
        else if (input == "2") {
            cout << "Enter new email: ";
            cin >> newData;
            teacher.setEmail(newData);
            break;
        }
        else {
            cout << "Invalid input. Please try again.\n";
        }

    }
    cout << "\nSuccessfully updated teacher info.\n";
    cout << teacher << endl;
    addDataToJsonFile("../Data/teachers.json", teacher);
    for (auto& [classID, classPtr] : teacher.GetSubjectsTaught()) {
        addDataToJsonFileFromClass("../Data/class.json", *classPtr);
    }
}


void markStudentAttendance(Teacher& teacher) {
    cout << "Enter 0 to go back to the teacher menu at any time\n";

    auto subjectsTaught = teacher.GetSubjectsTaught();
    if (subjectsTaught.empty()) {
        cout << "No classes to mark attendance for.\n";
        return;
    }

    while (true) {
        cout << "Which class would you like to mark the attendance for? Enter the Class ID:\n";
        for (const auto& [classID, classPtr] : subjectsTaught) {
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

        auto classIter = subjectsTaught.find(classID);
        if (classIter == subjectsTaught.end()) {
            cout << "Class ID not found. Please try again.\n";
            continue;
        }

        map<string, Student*> students = classIter->second->getStudents();
        if (students.empty()) {
            cout << "No students enrolled in this class.\n";
            continue;
        }

        cout << "Enter the ID of the student you would like to mark:\n";
        for (const auto& [studentID, studentPtr] : students) {
            cout << studentID << ": " << studentPtr->getName() << endl;
        }

        string studentID;
        cout << "Input Student ID: ";
        cin >> studentID;
        if (studentID == "0") {
            return;
        }

        auto studentIter = students.find(studentID);
        if (studentIter == students.end()) {
            cout << "Student ID not found. Please try again.\n";
            continue;
        }

        string date, status;
        cout << "Enter the Date you would like to mark (MM/DD/YYYY): ";
        cin >> date;
        cout << "PRESENT / ABSENT / TARDY?: ";
        cin >> status;
        markAttendance(*studentIter->second, date, status);
        break;
    }
}

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