#ifndef CLASSMENU_H
#define CLASSMENU_H

#include <iostream>
#include <string>
#include <map>

#include "../../include/ClassDeclarations/class.h"
#include "../../include/filemanipulation.h"
#include "../../include/Menu.h"
#include "../../include/ClassDeclarations/teacher.h"

using namespace std;


void updateClassInfo(Class& c);
void generateAttendanceReport(Class& c);

void ClassMenu(Class& c) {
    string className = c.getName();
    string teacherName = c.getTeacher()->getName();
    PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
    string input;
    while (true || cin >> input) {
        cout << "Enter 0 to go back to the teacher menu at any time\n";
        cin >> input;
        if (input == "0") {
            return;
        }
        else if (input == "1") {
            updateClassInfo(c);
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }
        else if (input == "2") {
            generateAttendanceReport(c);
        }
        else if (input == "2") {

        }

    }

}

void generateAttendanceReport(Class& c) {
    cout << "Would you like to generate an attendance report for this class? (y/n)\n";
    string input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (input == "y" || input == "Y") {
        cout << "Enter the Start Data (MM/DD/YYYY): ";
        string startDate;
        getline(cin, startDate);
        cout << "\nEnter the End Data (MM/DD/YYYY): ";
        string endDate;
        getline(cin, endDate);
        cout << "\nAttendance Report for " << c.getName() << " from " << startDate << " to " << endDate << endl;

        for (auto& [studentID, studentPtr] : c.getStudents()) {
            // cout << studentPtr->getName() << " " << studentPtr->getAttendanceReport(startDate, endDate) << endl;
        }
    }
    else {
        cout << "Not generating an attendance report\n";
        return;
    }
}

void updateClassInfo(Class& c) {
    cout << "Would you like to change the name of this class? (y/n)\n";
    string input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (input == "y" || input == "Y") {
        cout << "Enter the new name of the class: ";
        string newName;
        getline(cin, newName);
        c.setName(newName);
        addDataToJsonFileFromClass("../Data/class.json", c);
        addDataToJsonFile("../Data/teachers.json", *c.getTeacher());
        for (auto s = c.getStudents().begin(); s != c.getStudents().end(); s++) {
            addDataToJsonFile("../Data/students.json", *s->second);
        }
    }
    else {
        cout << "Not changing the name of the class\n";
        return;
    }
}

// void ClassMenu(map<string, Class*>& allClasses) {
    // char input;
    // while (cin >> input && input != '5')
    // {
    //     if (input == '1')
    //     {
    //         addClassAndData(allClasses);
    //     }

    //     else if (input == '2')
    //     {
    //         cout << "For which class would you like to show the attendance record of? \n";
    //         displayAllClasses(allClasses);
    //         cout << "Enter the class ID: ";
    //         string classID;
    //         cin >> classID;
    //         PrintMenuOption("Class Menu", "classMenuOptions");
    //     }
    //     else if (input == '3')
    //     {
    //         cout << "For which class would you like to show the Cumulative GPA of? \n";
    //         displayAllClasses(allClasses);
    //         cout << "Enter the class ID: ";
    //         string classID;
    //         cin >> classID;
    //         PrintMenuOption("Class Menu", "classMenuOptions");
    //     }
    //     else if (input == '4')
    //     {
    //         cout << "Adding student to class showing available classes\n";
    //         displayAllClasses(allClasses);
    //         string classID, studentID;
    //         cout << "Enter the class ID: ";
    //         cin >> classID;
    //         cout << "Enter the student ID: ";
    //         cin >> studentID;
    //         Student* studentptr = findStudentByID(allStudents, studentID);
    //         allClasses[classID]->addStudent(studentptr);
    //         studentptr->enrollInClass(allClasses[classID]);

    //         addDataToJsonFileFromClass("../Data/class.json", allClasses[classID]);
    //         cout << "works till here\n";
    //         cout << "Added Student\n";
    //         PrintMenuOption("Class Menu", "classMenuOptions");
    //     }
    //     else if (input == '5')
    //     {
    //         cout << "Exiting Class Menu\n";
    //         PrintMenuOption("Main Menu", "mainMenuOptions");
    //         break;
    //     }
    // }
// }

// void createTeacher(map<string, Class*>& allClasses) {
//     string name, email, id;
//     cout << "Enter the name of the teacher: ";
//     cin >> name;
//     cout << "Enter the email of the teacher:";
//     cin >> email;
//     cout << "Enter the ID of the teacher: ";
//     cin >> id;
//     Teacher* t = new Teacher(name, email, id);
//     cout << "Added Teacher";
//     string classID;
//     cin >> classID;
//     allClasses[classID]->setTeacher(t);
//     addDataToJsonFileFromClass("../Data/class.json", allClasses[classID]);
// }

// void displayAllClasses(map<string, Class*>& allClasses) {
//     for (auto& c : allClasses)
//     {
//         cout << c.second->getClassID() << ": " << c.second->getName() << endl; // this is the class object
//     }
// }

// void addClassAndData(map<string, Class*>& allClasses) {
//     string className, classID;
//     cout << "Creating a new class\n";
//     cout << "Enter the name of the class: ";
//     cin >> className;
//     cout << "Enter the class ID: ";
//     cin >> classID;
//     // cout << "Create a Teacher for the class\n";
//     // createTeacher(allClasses);
//     allClasses.insert(pair<string, Class*>(classID, new Class(className, classID)));
//     addDataToJsonFileFromClass("../Data/class.json", allClasses[classID]);
//     PrintMenuOption("Class Menu", "classMenuOptions");
// }

#endif // !CLASSMENU_H