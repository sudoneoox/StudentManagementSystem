#ifndef STUDENTMENU_H
#define STUDENTMENU_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "../../include/ClassDeclarations/student.h"
#include "../../include/ClassDeclarations/class.h"
#include "../../include/filemanipulation.h"
#include "../../include/Menu.h"

string currentDate();

void studentMenu(Student& student);
bool validationCheck(map<string, Student*> students, int& idx);

// void enrollStudentToClass(Student& student);
void enrollStudentToClass(Student& student, bool& continueLoop);
void removeStudentFromClass(Student& student, bool& continueLoop);
void updateSchedule(Student& student);
void calculateClassGrade(Student& student);
void submitAssignment(Student& student);


void markAttendance(Student& student, string date, string status);

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
            // markPresent(student);
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '3') {
            updateSchedule(student);
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '4') {
            cout << "Class Schedule For " << student.getName() << endl;
            student.printClassSchedule();
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '5') {
            calculateClassGrade(student);
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }

        else if (input == '6') {
            submitAssignment(student);
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
        else if (input == '7') {
            cout << "Exiting Program\n";
            break;
        }
        else {
            cout << "Invalid Option Try again.";
            PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
        }
    }
}



void submitAssignment(Student& student) {
    while (true) {
        cout << "\nDisplaying Your Current Classes:\n";
        auto classSchedule = student.getClassSchedule();
        if (classSchedule.empty()) {
            cout << "You are not enrolled in any classes.\n";
            return;
        }

        for (const auto& [classID, clsPtr] : classSchedule) {
            cout << classID << ": " << clsPtr->getName() << endl;
        }

        cout << "Enter the class ID you would like to update an assignment grade for, or 0 to go back: ";
        string classID;
        cin >> classID;
        if (classID == "0") {
            break;
        }

        auto clsPtr = findClassByID(allClasses, classID);
        if (clsPtr == nullptr) {
            cout << "\nInvalid Class ID.\n";
            continue;
        }

        auto assignments = clsPtr->getAssignments();
        if (assignments.empty()) {
            cout << "There are no assignments for this class.\n";
            continue;
        }

        cout << "Displaying Assignments for " << clsPtr->getName() << ":\n";
        for (const auto& [assignmentID, assignmentPtr] : assignments) {
            cout << assignmentID << ": " << assignmentPtr->getName() << endl;
        }

        cout << "Enter the assignment ID you would like to update your grade for, or 0 to go back: ";
        string assignmentID;
        cin >> assignmentID;
        if (assignmentID == "0") {
            continue;
        }

        if (assignments.find(assignmentID) == assignments.end()) {
            cout << "\nInvalid Assignment ID.\n";
            continue;
        }

        cout << "Enter your grade for " << assignments [assignmentID]->getName() << ": ";
        double grade;
        cin >> grade;
        string studentID = student.getID();
        // Update the grade in the class and student records
        clsPtr->setStudentGradeForAssignment(studentID, assignmentID, grade);
        student.setGradeForAssignment(assignmentID, grade);

        // Update JSON files
        addDataToJsonFile("../Data/students.json", student);
        addDataToJsonFileFromClass("../Data/class.json", *clsPtr);

        cout << "Updated assignment grade.\n";
        break;
    }
}

void calculateClassGrade(Student& student) {
    while (true) {
        cout << "\nDisplaying Your Current Classes:\n";
        auto classSchedule = student.getClassSchedule();
        if (classSchedule.empty()) {
            cout << "You are not enrolled in any classes\n";
            return;
        }
        for (const auto& [classID, clsPtr] : classSchedule) {
            cout << classID << ": " << clsPtr->getName() << endl;
        }
        cout << "Enter the class ID you would like to calculate your grade for or 0 to go back: ";
        string classID;
        cin >> classID;
        if (classID == "0") {
            break;
        }
        auto clsPtr = findClassByID(allClasses, classID);
        if (clsPtr == nullptr) {
            cout << "\nInvalid Class ID\n";
            continue;
        }
        double grade = clsPtr->calculateTotalGrade(student.getID());
        cout << "Your grade in " << clsPtr->getName() << " is " << grade << endl;
    }
    return;
}

void markAttendance(Student& student, string date, string status) {
    cout << "\nAttendance has been marked for " << student.getName() << " on " << date << endl;
    student.MarkAttendance(date, status);
    addDataToJsonFile("../Data/students.json", student);
}


void updateSchedule(Student& student) {
    bool continueLoop = true;
    while (continueLoop) {
        char option;
        cout << "Would you like to" << endl;
        cout << "1. Drop a Class? " << endl;
        cout << "2. Enroll in a Class? " << endl;
        cout << "0. Go back to Student Menu" << endl;
        cin >> option;
        if (option == '0') {
            return;
        }
        else if (option == '1') {
            removeStudentFromClass((student), continueLoop);
            continueLoop = false;
        }
        else if (option == '2') {
            enrollStudentToClass((student), continueLoop);
            continueLoop = false;
        }
        else {
            cout << "Invalid Option Try again.";
        }
    }
    return;
}

void removeStudentFromClass(Student& student, bool& continueLoop) {
    while (continueLoop) {
        cout << "\nDisplaying Your Current Classes:\n";
        map<string, Class*> classSchedule = student.getClassSchedule();
        if (classSchedule.size() == 0) {
            cout << "You are not enrolled in any classes\n";
            return;
        }
        for (classIter = classSchedule.begin(); classIter != classSchedule.end(); classIter++) {
            cout << classIter->second->getID() << ": " << classIter->second->getName() << endl;
        }
        cout << "Enter the class ID you would like to drop or 0 to go back: ";
        string classID;
        cin >> classID;
        if (classID == "0") {
            return;
        }
        Class* clsPtr = findClassByID(allClasses, classID);
        if (clsPtr == nullptr) {
            cout << "\nInvalid Class ID\n";
            continueLoop = true;
        }
        else if (!student.isEnrolledInClass(classID)) {
            cout << "\nYou are not enrolled in this class\n";
            continueLoop = true;
        }
        else {
            student.dropClass(clsPtr);
            clsPtr->removeStudent(&student);
            cout << "Successfully Dropped " << clsPtr->getName() << endl;
            addDataToJsonFile("../Data/students.json", student);
            addDataToJsonFileFromClass("../Data/class.json", *clsPtr);
            return;
        }
    }
}


void enrollStudentToClass(Student& student, bool& continueLoop) {
    while (continueLoop) {
        cout << "\nDisplaying Available Classes\n";
        for (classIter = allClasses.begin(); classIter != allClasses.end(); classIter++) {
            cout << classIter->second->getID() << ": " << classIter->second->getName() << endl;
        }
        if (allClasses.size() == 0) {
            cout << "There are no classes available to enroll in\n";
            return;
        }
        cout << "Enter the class ID you would like to enroll in or 0 to return: ";
        string classID;
        cin >> classID;
        if (classID == "0") {
            return;
        }
        if (allClasses.find(classID) == allClasses.end()) {
            cout << "\nInvalid Class ID\n";
            continueLoop = true;
        }
        else if (student.isEnrolledInClass(classID)) {

            cout << "\nYou are already enrolled in this class\n";
            continueLoop = true;
        }
        else {
            student.enrollInClass(allClasses [classID]);
            allClasses [classID]->addStudent(&student);
            cout << "Successfully Enrolled in " << allClasses [classID]->getName() << endl;
            addDataToJsonFile("../Data/students.json", student);
            addDataToJsonFileFromClass("../Data/class.json", *allClasses [classID]);
            return;
        }
    }
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