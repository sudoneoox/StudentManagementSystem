#ifndef CLASSMENU_H
#define CLASSMENU_H
#include <iostream>
#include <string>
#include <map>
#include "../H/class.h"
#include "../H/filemanipulation.h"

using namespace std;
void addDataToJsonFile(string &filename, Class *c);

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
            addDataToJsonFileFromClass("./Data/class.json", allClasses[classID]);
            PrintMenuOption("Class Menu", "classMenuOptions");
        }

        else if (input == '2')
        {
            cout << "Displaying all classes\n";
            for (auto &c : allClasses)
            {
                cout << "Class Name: " << c.second->getName() << endl;
            }
            PrintMenuOption("Class Menu", "classMenuOptions");
        }
        else if (input == '5')
        {
            cout << "Exiting Class Menu\n";
            PrintMenuOption("Main Menu", "mainMenuOptions");
            break;
        }
    }
}

#endif // !CLASSMENU_H