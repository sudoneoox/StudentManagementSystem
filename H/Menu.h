#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

void PrintMenuOption(string name, string menu)
{
    vector<string> options;
    if (menu == "studentMenuOptions")
    {
        options = {
            "Get Info",
            "Mark Attendance",
            "Add To Schedule",
            "View Schedule",
            "Get Class Grades",
            "Update Information",
        };
    }
    else if (menu == "teacherMenuOptions")
    {
        options = {
            "Add Teacher",
            "Display Teacher",
            "Update Teacher Info",
            "Get Attendance"};
    }
    else if (menu == "classMenuOptions")
    {
        options = {"Add Class", "Generate Attendance Report", "Show Class GPA", "Add Student To Class"};
    }
    else if (menu == "mainMenuOptions")
    {
        options = {"Student Menu", "Teacher Menu", "Class Menu"};
    }

    int width = 53;
    int namePadding = (width - 2 - name.length()) / 2;
    cout << setfill('-') << setw(width) << "-" << endl; // top border
    cout << "|" << setfill(' ') << setw(namePadding) << " " << name << setw(namePadding) << " "
         << "|" << endl;                                // menu title
    cout << setfill('-') << setw(width) << "-" << endl; // bottom border
    for (int i = 0; i < options.size(); i++)
    {
        string optionLine = "| " + to_string(i + 1) + ". " + options.at(i);
        int optionPadding = width - 4 - options.at(i).length() - to_string(i + 1).length();
        cout << optionLine << setfill(' ') << setw(optionPadding) << " |" << endl;
    }
    string exitOption = "| " + to_string(options.size() + 1) + ". Exit";
    int exitPadding = width - 4 - 4 - to_string(options.size() + 1).length();
    cout << exitOption << setfill(' ') << setw(exitPadding) << " |" << endl; // exit option

    cout << setfill('-') << setw(width) << "-" << endl; // bottom border
}
#endif // !MENU_H