#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "../../include/Menu.h"
#include "../../include/ClassDeclarations/student.h"
#include "../../include/ClassDeclarations/class.h"
#include "../../include/filemanipulation.h"

using namespace std;
extern map<string, Teacher*> allTeachers; // map of all the teachers in the program
extern map<string, Student*> allStudents; // map of all the students in the program
extern map<string, Class*> allClasses; // map of all the classes in the program 


void addStudent();
void addClass();
bool adminValidationCheck();

void AdminMenu() {
    string input;
    while (true) {
        cin >> input;
        if (input == "1") {
            addStudent();
            PrintMenuOption("Admin Menu", "adminMenuOptions");
        }
        else if (input == "2") {
            addClass();
            PrintMenuOption("Admin Menu", "adminMenuOptions");
        }
        else if (input == "3") {
            cout << "Leaving Admin Menu\n";
            break;
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
}

void addStudent() {
    Student* student = new Student(); // create new student object
    while (true) {
        string name, id, email;
        cout << "Enter 0 to go back to the admin menu at any time\n";
        cout << "Enter the name of the student: ";
        if (cin.peek() == '\n') cin.ignore(); // this is to fix the bug where the cin >> input skips the first input
        getline(cin, name);
        if (name == "0") {
            delete student; // delete the student object if the user wants to go back to the admin menu
            break;
        }
        cout << "Enter the id of the student: ";
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, id);
        if (id == "0") {
            delete student;
            break;
        }
        cout << "Enter the email of the student: ";
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, email);
        if (email == "0") {
            delete student;
            break;
        }
        student->setName(name); // set the name of the student
        student->setID(id);   // set the id of the student
        student->setEmail(email); // set the email of the student
        allStudents.insert(pair<string, Student*>(id, student)); // insert the student into the map of all students
        addDataToJsonFile("../Data/students.json", *student); // add the student to the json file
        cout << "Student added successfully" << endl;
        break;
    }
    return;
}

void addClass() {
    Class* classPtr = new Class(); // create new class object
    while (true) {
        string name, id, teacherID;
        cout << "Enter 0 to go back to the admin menu at any time\n";
        cout << "Enter the name of the class: ";
        if (cin.peek() == '\n') cin.ignore(); // this is to fix the bug where the cin >> input skips the first input
        getline(cin, name);
        if (name == "0") {
            delete classPtr; // delete the class object if the user wants to go back to the admin menu
            break;
        }
        cout << "Enter the id of the class: ";
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, id);
        if (id == "0") {
            delete classPtr;
            break;
        }
        cout << "Enter the teacher ID who teaches this class: ";
        for (auto& [id, teacher] : allTeachers) { // print all the teachers in the program
            cout << id << ": " << teacher->getName() << endl;
        }
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, teacherID);
        if (teacherID == "0") {
            delete classPtr;
            break;
        }
        classPtr->setTeacher(allTeachers [teacherID]); // set the teacher of the class
        classPtr->setName(name); // set the name of the class
        classPtr->setClassID(id); // set the id of the class
        allClasses.insert(pair<string, Class*>(id, classPtr)); // insert the class into the map of all classes
        allTeachers [teacherID]->addSubject(allClasses [id]); // add the class to the teacher's list of subjects
        addDataToJsonFileFromClass("../Data/class.json", *classPtr); // add the class to the json file
        addDataToJsonFile("../Data/teachers.json", *allTeachers [teacherID]); // add the teacher to the json file
        cout << "Class added successfully" << endl;
        break;
    }
    return;
}

// this function checks if the user is the admin by testing if the password is correct
bool adminValidationCheck() {
    while (true) {
        cout << "enter the admin password (0: exit): ";
        string password;
        cin >> password;
        if (password == "admin" || password == "Admin") {
            return true;
        }
        else if (password == "0") {
            return false;
        }
        else {
            cout << "Invalid password Try again" << endl;
        }
    }
    return false;
}


#endif // !ADMIN_H