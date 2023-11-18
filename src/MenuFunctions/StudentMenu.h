#ifndef STUDENTMENU_H
#define STUDENTMENU_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "../../include/ClassDeclarations/student.h"
#include "../../include/filemanipulation.h"
#include "../../include/Menu.h"

string currentDate();

void studentMenu(Student& student);
bool validationCheck(vector<Student> students, int& idx);

void enrollStudentToClass(Student& student);
void updateStudentInfo(Student& student);

void markPresent(Student& student);

extern map<string, Student*> allStudents;
extern map<string, Class*> allClasses;
extern map<string, Class*>::iterator classIter;


void studentMenu(Student& student) {
    char input;
    string name = student.getName();
    while (cin >> input && input != '7') {
        if (input == '1') {
            cout << "Showing Information For " << student.getName() << endl;
            cout << student << endl;
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '2') {
            markPresent(student);
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '3') {
            enrollStudentToClass(student);
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '4') {
            cout << "Schedule For " << student.getName() << endl;
            student.printClassSchedule();
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '5') {
            cout << "still need to implement this\n";
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '6') {
            updateStudentInfo(student);
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '7') {
            cout << "Exiting Student Menu\n";
            PrintMenuOption("Main Menu", "mainMenuOptions");
            break;
        }
    }
}


void markPresent(Student& student) {
    cout << "You will now be marked present for today's date "
        << currentDate() << '\n';
    student.MarkAttendance(currentDate(), "PRESENT");
    addDataToJsonFile("../Data/students.json", student);
}


void updateStudentInfo(Student& student) { //! FIXME Stuck here either completely take out this or find a way to also update the class json
    cout << "What would you like to update?\n";
    cout << "1. Email\n";
    cout << "2. Name\n";
    cout << "3. Both\n";
    cout << "0. Go Back\n";
    char option;
    cin >> option;
    if (option == '1') {
        cout << "Enter new email: ";
        string email;
        cin >> email;
        student.setEmail(email);
        addDataToJsonFile("../Data/students.json", student);
    }
    else if (option == '2') {
        cout << "Enter new name: ";
        string name;
        cin >> name;
        student.setName(name);
    }
    else if (option == '3') {
        cout << "Enter new name: ";
        string name;
        cin >> name;
        student.setName(name);
        cout << "Enter new email: ";
        string email;
        cin >> email;
        student.setEmail(email);
    }
    else if (option == '0') {
        return;
    }
    else {
        cout << "Invalid Option\n";
    }
    if (option == '1' || option == '2' || option == '3') {
        addDataToJsonFile("../Data/students.json", student);
        for (auto iter = student.getClassSchedule().begin(); iter != student.getClassSchedule().end(); iter++) {
            addDataToJsonFileFromClass("../Data/class.json", *iter->second);
        }
        cout << "Successfully Updated Student Info\n";
    }
}


void enrollStudentToClass(Student& student) {
    cout << "Displaying Available Classes\n";
    for (classIter = allClasses.begin(); classIter != allClasses.end(); classIter++) {
        cout << classIter->second->getID() << " " << classIter->second->getName() << endl;
    }
    cout << "Enter the class ID you would like to enroll in: ";
    string classID;
    cin >> classID;
    if (allClasses.find(classID) == allClasses.end()) {
        cout << "Invalid Class ID\n";
        return;
    }
    else if (student.isEnrolledInClass(classID)) {
        cout << "You are already enrolled in this class\n";
        return;
    }
    student.enrollInClass(allClasses [classID]);
    allClasses [classID]->addStudent(&student);
    cout << "Successfully Enrolled in " << allClasses [classID]->getName() << endl;
    addDataToJsonFile("../Data/students.json", student);
    addDataToJsonFileFromClass("../Data/class.json", *allClasses [classID]);
}

/* This function is used to get the current date and return it as a string credit: stack overflow*/
string currentDate() {
    auto now = chrono::system_clock::now();

    time_t now_c = chrono::system_clock::to_time_t(now); // convert to c time

    tm now_tm = *localtime(&now_c); // convert to tm struct for formatting

    ostringstream dateStream;
    dateStream << put_time(&now_tm, "%m/%d/%Y"); // format month/day/year
    return dateStream.str();
}


/* This function is used to validate the user input for the student ID
It will return true if the ID is valid and false if the ID is invalid
 It will also return the index of the student in the vector*/
bool validationCheck(map<string, Student*> students, int& idx) {
    string ID;
    map<string, Student*>::iterator iter;

    // Loop until the user enters a valid ID or 0 to go back
    while (true) {
        cout << "Enter your StudentID or 0 to go back: ";
        cin >> ID;
        if (ID == "0") {
            return false; // Return false if user enters 0, this will take them back to the main menu
        }

        // iterate through map of students to find the student with the matching ID
        iter = students.find(ID);
        if (iter != students.end()) {
            idx = stoi(ID);
            return true; // Return true if the ID is valid
        }

        cout << "Invalid ID Try Again or Enter 0 to go back to the portal\n";
    }
}

#endif // !STUDENTMENU_H