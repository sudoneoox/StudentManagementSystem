#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;


/*
This function creates the ascii menu for the program
@param name: the name of the menu
@param menu: the menu options to be displayed
Its used extensively throughout the program and uses iomanip to format the menu

*/
void PrintMenuOption(string name, string menu) {
    vector<string> options;
    if (menu == "studentMenuOptions") {
        options = {
            "Get Info",
            "Update Schedule",
            "View Schedule",
            "Calculate Class Grade",
            "Submit Assignment"
        };
    }
    else if (menu == "teacherMenuOptions") {
        options = {
            "Get Info",
            "Mark Student Attendance",
            "Update Teacher Info",
            "Class Menu"
        };
    }
    else if (menu == "classMenuOptions") {
        options = { "Update Class Info", "Get Attendance Report", "Enter Exam Grades", "Get Overall Class GPA" };
    }
    else if (menu == "mainMenuOptions") {
        options = { "Student Menu", "Teacher Menu" };
    }

    int width = 53; // width of the menu
    int namePadding = (width - 2 - name.length()) / 2;   // padding for the name of the menu
    cout << setfill('-') << setw(width) << "-" << endl;     // top border
    cout << "|" << setfill(' ') << setw(namePadding) << " " << name << setw(namePadding) << " " << "|" << endl; // menu title
    cout << setfill('-') << setw(width) << "-" << endl; // bottom border

    for (int i = 0; i < options.size(); i++) {
        string optionLine = "| " + to_string(i + 1) + ". " + options.at(i);
        int optionPadding = width - 4 - options.at(i).length() - to_string(i + 1).length();
        cout << optionLine << setfill(' ') << setw(optionPadding) << " |" << endl;
    }
    string exitOption = "| " + to_string(options.size() + 1) + ". Exit"; // adds an exit option to all the menus its number is set to the size of the options vector + 1
    int exitPadding = width - 4 - 4 - to_string(options.size() + 1).length();
    cout << exitOption << setfill(' ') << setw(exitPadding) << " |" << endl; // exit option

    cout << setfill('-') << setw(width) << "-" << endl; // bottom border
}
#endif // !MENU_H