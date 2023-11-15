#ifndef CLASSMENU_H
#define CLASSMENU_H

#include <iostream>
#include <string>
#include <map>

#include "../../include/ClassDeclarations/class.h"
#include "../../include/filemanipulation.h"
#include "../../include/Menu.h"

using namespace std;

void displayAllClasses(map<string, Class *> &allClasses);

void ClassMenu(map<string, Class *> &allClasses)
{
    char input;
    while (cin >> input && input != '5')
    {
        if (input == '1')
        {
            cout << "Creating a new class\n";
            string className;
            string classID;
            cout << "Enter the name of the class: ";
            cin >> className;
            cout << "Enter the class ID: ";
            cin >> classID;
            allClasses.insert(pair<string, Class *>(classID, new Class(className, classID)));
            addDataToJsonFileFromClass("../Data/class.json", allClasses[classID]);
            PrintMenuOption("Class Menu", "classMenuOptions");
        }

        else if (input == '2')
        {
            cout << "For which class would you like to show the attendance record of? \n";
            displayAllClasses(allClasses);
            cout << "Enter the class ID: ";
            string classID;
            cin >> classID;
            PrintMenuOption("Class Menu", "classMenuOptions");
        }
        else if (input == '3')
        {
            cout << "For which class would you like to show the Cumulative GPA of? \n";
            displayAllClasses(allClasses);
            cout << "Enter the class ID: ";
            string classID;
            cin >> classID;
            PrintMenuOption("Class Menu", "classMenuOptions");
        }
        else if (input == '4')
        {
            cout << "Adding student to class showing available classes\n";
            displayAllClasses(allClasses);
            string classID, studentID;
            cout << "Enter the class ID: ";
            cin >> classID;
            cout << "Enter the student ID: ";
            cin >> studentID;
        }
        else if (input == '5')
        {
            cout << "Exiting Class Menu\n";
            PrintMenuOption("Main Menu", "mainMenuOptions");
            break;
        }
    }
}

void displayAllClasses(map<string, Class *> &allClasses)
{
    for (auto &c : allClasses)
    {
        cout << c.second->getClassID() << ": " << c.second->getName() << endl; // this is the class object
    }
}

#endif // !CLASSMENU_H